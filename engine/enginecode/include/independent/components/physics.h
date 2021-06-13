/**\file physics.h*/
#pragma once

#include "core/application.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	enum class RigidBodyType { Static, Kinematic, Dynamic };

	/** \class RigidBodyComponent
	*	\brief Class that holds rigid body component attachable to an entity
	*/
	class RigidBodyComponent
	{
	public:
		RigidBodyComponent() // Default constructor, initialize the members of a class.
		{
			rp3d::PhysicsWorld* world = Application::getInstance().world; // Get the pointer to the rp3d physics world in which the rigidbody is created.
			rp3d::Vector3 position(0.0, 0.0, 0.0); // Default position a Vector3 set to all 0.
			rp3d::Quaternion orientation = rp3d::Quaternion::identity(); // Identity quaternion of the rigidbody component and store it in a variable for access and use in Transform information.
			rp3d::Transform transform(position, orientation); // Position and orientation in 3D space.

			m_body = world->createRigidBody(transform); // Create a m_body in world
			m_body->setType(rp3d::BodyType::DYNAMIC); // Dynamic by default

		}

		RigidBodyComponent(RigidBodyType type, uint32_t location) // Constructor with RB type and location used for ID
		{
			rp3d::PhysicsWorld* world = Application::getInstance().world;
			rp3d::Vector3 position(0.0, 0.0, 0.0);
			rp3d::Quaternion orientation = rp3d::Quaternion::identity();
			rp3d::Transform transform(position, orientation);

			m_body = world->createRigidBody(transform);
			switch (type)
			{
			case RigidBodyType::Static:
				m_body->setType(rp3d::BodyType::STATIC);
				break;
			case RigidBodyType::Kinematic:
				m_body->setType(rp3d::BodyType::KINEMATIC);
				break;
			case RigidBodyType::Dynamic:
				m_body->setType(rp3d::BodyType::DYNAMIC);
			}
			m_body->setUserData(reinterpret_cast<void*>(location));
		}


		// Location is ID for collisions
		RigidBodyComponent(RigidBodyType type, glm::mat4& transform, uint32_t location)
		{
			rp3d::PhysicsWorld* world = Application::getInstance().world;
			rp3d::Transform RPtransform;
			RPtransform.setFromOpenGL(glm::value_ptr(transform));

			auto quat = RPtransform.getOrientation();
			quat.normalize();
			RPtransform.setOrientation(quat);

			m_body = world->createRigidBody(RPtransform);

			switch (type)
			{
			case RigidBodyType::Static:
				m_body->setType(rp3d::BodyType::STATIC);
				break;
			case RigidBodyType::Kinematic:
				m_body->setType(rp3d::BodyType::KINEMATIC);
				break;
			case RigidBodyType::Dynamic:
				m_body->setType(rp3d::BodyType::DYNAMIC);
				break;
			}

			m_body->setUserData(reinterpret_cast<void*>(location));
		}

		rp3d::RigidBody* m_body;

	private:
	};

	/** \class BoxColliderComponent
	*	\brief Class that holds box collider component attachable to an entity
	*/
	class BoxColliderComponent
	{
	public:
		BoxColliderComponent(RigidBodyComponent& bodyComp, glm::vec3& halfExtents)
		{
			auto& physCommon = Application::getInstance().physCommon;
			auto& world = Application::getInstance().world;

			shape = physCommon.createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z));

			rp3d::Transform transform = rp3d::Transform::identity();

			collider = bodyComp.m_body->addCollider(shape, transform);
		}

		rp3d::BoxShape* shape;
		rp3d::Collider* collider = nullptr;

	private:
	};

	/** \class BoxTriggerComponent
	*	\brief Class box trigger component attachable to an entity
	*/
	class BoxTriggerComponent
	{
	public:
		BoxTriggerComponent(RigidBodyComponent& bodyComp, glm::vec3& halfExtents)
		{
			auto& physCommon = Application::getInstance().physCommon;
			auto& world = Application::getInstance().world;

			shape = physCommon.createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z));

			rp3d::Transform transform = rp3d::Transform::identity();

			collider = bodyComp.m_body->addCollider(shape, transform);
			collider->setIsTrigger(true);
		}

		rp3d::BoxShape* shape;
		rp3d::Collider* collider = nullptr;


	private:
	};


	// Attached to entities that are destroyed on contact such as collectable
	struct DestroyOnContactComponent
	{
		bool destroyChildren = false;
	};

	// Class that handles the entity collision through rp3d EventListener
	class enttListener : public rp3d::EventListener
	{
	public: 
		std::vector<uint32_t> toBeDestroyed;

		virtual void onContact(const CollisionCallback::CallbackData& callbackData) override
		{
			auto& registry = Application::getInstance().m_registry;
			auto& entities = Application::getInstance().m_entities;
			//auto world = Application::getInstance().getWorld();
			auto& world = Application::getInstance().world;

			// For each contact pair
			for (uint32_t p = 0; p < callbackData.getNbContactPairs(); p++)
			{
				// Get the contact pair 
				CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);

				// Index in the array of entit
				uint32_t index1 = reinterpret_cast<uint32_t>(contactPair.getBody1()->getUserData());
				uint32_t index2 = reinterpret_cast<uint32_t>(contactPair.getBody2()->getUserData());

				entt::entity entityl = entities[index1];
				entt::entity entity2 = entities[index2];

				bool destroy1 = registry.has<DestroyOnContactComponent>(entityl);
				bool destroy2 = registry.has<DestroyOnContactComponent>(entity2);

				if (destroy1) 
				{
					toBeDestroyed.push_back(index1);

				}
				if (destroy2) 
				{
					toBeDestroyed.push_back(index2);
				}

			}


		}

		virtual void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override
		{
			for (int i = 0; i < callbackData.getNbOverlappingPairs(); i++)
			{
				auto contactPair = callbackData.getOverlappingPair(i);

				uint32_t index1 = reinterpret_cast<uint32_t>(contactPair.getBody1()->getUserData());
				uint32_t index2 = reinterpret_cast<uint32_t>(contactPair.getBody2()->getUserData());
				auto et = contactPair.getEventType();
				if (et == rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart)Log::info("Start {0} {1}", index1, index2);
				if (et == rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit)Log::info("Stop {0} {1}", index1, index2);

			}
		}

		uint32_t actionDestroy()
		{
			//auto world = Application::getInstance().getWorld();
			auto& world = Application::getInstance().world;
			auto& registry = Application::getInstance().m_registry;
			auto& entities = Application::getInstance().m_entities;

			uint32_t result = toBeDestroyed.size();
			for (auto index : toBeDestroyed)
			{
				entt::entity entity = entities[index];
				auto& rigidBody = registry.get<RigidBodyComponent>(entity);
				world->destroyRigidBody(rigidBody.m_body);
				registry.destroy(entity);
			}
			toBeDestroyed.clear();
			return result;
		}

	};


	namespace NGPhysicsSystem
	{
		void updateTransform();
	};
}
