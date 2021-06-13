#include "engine_pch.h"
#include "components/player.h"
#include "events/codes.h"
#include "core/inputPoller.h"
#include "components/physics.h"
// Pass in as a parameter
// Move the function - 
// O
namespace Engine
{
	
	void Player::onUpdate(float time)
	{
		if (InputPoller::isKeyPressed(NG_KEY_U))
		{
			float desiredVel = 2.0;
			rp3d::Vector3 vel = m_body->getLinearVelocity();
			float velChange = desiredVel - vel.length();
			// f = m * v/t
			float forceScalar = m_body->getMass() * velChange / time;

			// Calculate forward direction
			rp3d::Vector3 direction;
			rp3d::Transform transform = m_body->getTransform();
			rp3d::Quaternion q = transform.getOrientation();

			direction.x = -2.f * (q.x * q.z - q.w * q.y);
			direction.y = 2.f * (q.y * q.z + q.w * q.x);
			direction.z = 1 - 2.f * (q.x * q.x + q.y * q.y);

			rp3d::Vector3 force(direction.x * forceScalar, direction.y * forceScalar, direction.z * forceScalar);

			// Apply the force to the body
			m_body->applyForceToCenterOfMass(-force);



		}

		if (InputPoller::isKeyPressed(NG_KEY_J))
		{
			float desiredVel = 2.0;
			rp3d::Vector3 vel = m_body->getLinearVelocity();
			float velChange = desiredVel - vel.length();
			// f = m * v/t
			float forceScalar = m_body->getMass() * velChange / time;

			// Calculate forward direction
			rp3d::Vector3 direction;
			rp3d::Transform transform = m_body->getTransform();
			rp3d::Quaternion q = transform.getOrientation();

			direction.x = -2.f * (q.x * q.z - q.w * q.y);
			direction.y = 2.f * (q.y * q.z + q.w * q.x);
			direction.z = 1 - 2.f * (q.x * q.x + q.y * q.y);

			rp3d::Vector3 force(direction.x * forceScalar, direction.y * forceScalar, direction.z * forceScalar);

			// Apply the force to the body
			m_body->applyForceToCenterOfMass(force);


		}

		if (InputPoller::isKeyPressed(NG_KEY_H))
		{
			float desiredVel = 2.0;
			rp3d::Vector3 vel = m_body->getLinearVelocity();
			float velChange = desiredVel - vel.length();
			// f = m * v/t
			float forceScalar = m_body->getMass() * velChange / time;

			// Calculate forward direction
			rp3d::Vector3 direction;
			rp3d::Transform transform = m_body->getTransform();
			rp3d::Quaternion q = transform.getOrientation();

			direction.x = -2.f * (q.x * q.z - q.w * q.y);
			direction.y = 2.f * (q.y * q.z + q.w * q.x);
			direction.x = 1 - 2.f * (q.x * q.x + q.y * q.y);

			rp3d::Vector3 force(direction.x * forceScalar, direction.y * forceScalar, direction.z * forceScalar);

			// Apply the force to the body
			m_body->applyForceToCenterOfMass(-force);

		}
		if (InputPoller::isKeyPressed(NG_KEY_K))
		{
			float desiredVel = 2.0;
			rp3d::Vector3 vel = m_body->getLinearVelocity();
			float velChange = desiredVel - vel.length();
			// f = m * v/t
			float forceScalar = m_body->getMass() * velChange / time;

			// Calculate forward direction
			rp3d::Vector3 direction;
			rp3d::Transform transform = m_body->getTransform();
			rp3d::Quaternion q = transform.getOrientation();

			direction.x = -2.f * (q.x * q.z - q.w * q.y);
			direction.y = 2.f * (q.y * q.z + q.w * q.x);
			direction.x = 1 - 2.f * (q.x * q.x + q.y * q.y);

			rp3d::Vector3 force(direction.x * forceScalar, direction.y * forceScalar, direction.z * forceScalar);

			// Apply the force to the body
			m_body->applyForceToCenterOfMass(force);
		}

		if (InputPoller::isKeyPressed(NG_KEY_SPACE))
		{
			m_body->applyForceToCenterOfMass(rp3d::Vector3(0, 100, 0));
		}
	}

	Player::Player(rp3d::RigidBody * body)
	{
		m_body = body;
		auto& material = m_body->getCollider(0)->getMaterial();
		material.setBounciness(0.0f);
		m_body->getCollider(0)->setMaterial(material);
	}
}
