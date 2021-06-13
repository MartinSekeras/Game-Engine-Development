#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include "engine.h"
#include "components/transform.h"
#include "components/physics.h"

namespace Engine {

	class SimpleAI {

	public:
		enum class State { turning, travelling };
		SimpleAI(uint32_t firstWayPoint, State startState, std::vector<glm::vec3>& waypoints) : 
			nextWaypoint{ firstWayPoint },
			previousWaypoint{ firstWayPoint == 0 ? (uint32_t)waypoints.size()-1 : firstWayPoint - 1 },
			currentState{ startState },
			waypoints{ waypoints }
		{
			waypointNorms.resize(waypoints.size());
			int a;
			for (a = 0; a < waypoints.size() - 1; a++) {
				int b = a + 1;
				waypointNorms[a] = glm::normalize(glm::cross(waypoints[a] - waypoints[b], glm::vec3(0.0f, 1.0f, 0.0f)));
			}
			a = waypoints.size() - 1;
			waypointNorms[a] = glm::normalize(glm::cross(waypoints[a] - waypoints[0], glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		//body = world->createRigidBody(transform);
		//body->setType(rp3d::BodyType::DYNAMIC);

		State currentState;
		std::vector<glm::vec3> waypoints;
		std::vector<glm::vec3> waypointNorms;
		uint32_t nextWaypoint;
		uint32_t previousWaypoint;
		//bool newWaypoint = false;
		float distToTarget;
		float prevDistToTarget;

	};


	namespace FSMSystem {

		void Update(entt::entity entity, float timestep);
	}
}