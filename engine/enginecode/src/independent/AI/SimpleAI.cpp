#include "engine_pch.h"
#include "AI/SimpleAI.h"

namespace Engine {

	namespace FSMSystem {
		

		void Update(entt::entity entity, float timestep)
		{
			
			entt::registry& registry = Application::getInstance().m_registry;
			auto&[FSMComp, transformComp, rbComp] = registry.get<SimpleAI, TransformComponent, RigidBodyComponent>(entity);
			glm::mat4& transform = transformComp.getTransform();

			glm::vec3 forward = glm::normalize(glm::vec3( -transform[2][0], -transform[2][1], -transform[2][2] ));

			float rotationSpeed = -2.0f;
			float linearSpeed = 1.0f;

			glm::vec3& targetWaypoint = FSMComp.waypoints[FSMComp.nextWaypoint];
			glm::vec3 toTarget = targetWaypoint - transformComp.translation;
			toTarget.y = 0.0f;
			glm::vec3 toTargetNormalized = glm::normalize(toTarget);
			//Log::info("to target {0} {1} {2}",toTarget.x, toTarget.y, toTarget.z);
			float angleToTarget = acos(glm::dot(glm::normalize(glm::vec3(forward.x, 0.0f,forward.z)), toTargetNormalized));

			//if(FSMComp.newWaypoint )
			FSMComp.prevDistToTarget = FSMComp.distToTarget;
			FSMComp.distToTarget = glm::length(toTarget);
			

			auto body = rbComp.m_body;

			switch (FSMComp.currentState)
			{

			case SimpleAI::State::turning:
			{
				//Log::info("Turning {0} {1} {2} {3} {4} {5}", forward.x,forward.y, forward.z, toTarget.x, toTarget.y, toTarget.z);
				float angleThresshold = glm::radians(1.0f);
				//Log::info("theta {0} thresh {1}", angleToTarget, angleThresshold);
				//Log::info("fabs(angleToTarget) {0} angleThresshold {1} angleToTarget {2}", fabs(angleToTarget), angleThresshold, angleToTarget);
				if (fabs(angleToTarget) < angleThresshold) {
					
					FSMComp.currentState = SimpleAI::State::travelling;
					break;
				}

				float x = std::max(std::min(angleToTarget / glm::radians(10.0f), -1.0f), 1.0f);
				float scalar = -(cosf(glm::pi<float>() * x) - 1.0f) / 2.0f;
				float deltaAngle = rotationSpeed * scalar * timestep;
				float desiredAngularSpeed = std::max(std::min(0.75f, angleToTarget), 0.1f);
				float currentAngularSpeed = body->getAngularVelocity().y;
				float deltaAngularVelocity = desiredAngularSpeed - currentAngularSpeed;

				// F = MA
				float torque = body->getMass() * (deltaAngularVelocity / timestep);
				
				if (deltaAngle < 0.f)
				{
					body->applyTorque(rp3d::Vector3(0.f, torque,0.f));
				}
				else
				{
					body->applyTorque(rp3d::Vector3(0.f, -torque, 0.f));
				}
			}
			break;

			case SimpleAI::State::travelling:


				/* Calculate forware firection */
				rp3d::Vector3 direction;

				rp3d::Transform transform = body->getTransform();
				rp3d::Quaternion q = transform.getOrientation();

				direction.x = -2.0f * (q.x * q.z - q.w * q.y);
				direction.y = 2.0f * (q.y * q.z + q.w * q.x);
				direction.z = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

				rp3d::Vector3 desiredVel = -direction;
				rp3d::Vector3 currentVel = body->getLinearVelocity();

				rp3d::Vector3 deltaVel = desiredVel - currentVel;
				//rp3d::Vector3 deltaVel = std::max(std::min(0.75f, distToTarget), 0.1f);

				// F = MA
				rp3d::Vector3 force = body->getMass() * (deltaVel / timestep);

				body->applyForceToCenterOfMass(force);


				
				//Log::info("DOT {6} fwd {0} {1} {2} normal {3} {4} {5}", toTarget.x, toTarget.y, toTarget.z, FSMComp.waypointNorms[FSMComp.nextWaypoint].x, FSMComp.waypointNorms[FSMComp.nextWaypoint].y, FSMComp.waypointNorms[FSMComp.nextWaypoint].z, dot);
				float distThresh = 0.1f;

				Log::info("dist to target {0}	{1} ", FSMComp.distToTarget, FSMComp.prevDistToTarget);
				if (FSMComp.distToTarget < distThresh || FSMComp.distToTarget > FSMComp.prevDistToTarget) {
					FSMComp.currentState = SimpleAI::State::turning;
					FSMComp.previousWaypoint = FSMComp.nextWaypoint;
					FSMComp.nextWaypoint = (++FSMComp.nextWaypoint) % FSMComp.waypoints.size();
					//FSMComp.newWaypoint = true;
				}

				//rp3d::Vector3 force(direction.x * forceScalar, direction.y * forceScalar, direction.z * forceScalar);

				//body->applyForceToCenterOfMass(force);
				
				/*
				float x = std::max(std::min(distToPrevTarget / 1.5f, 1.0f), 0.0f);
				float scalarIn = (1.0f - cosf((x * glm::pi<float>()) / 2.0f)) * 0.6f + 0.4f;

				x = std::max(std::min(distToPrevTarget / 1.0f, 1.0f), 0.0f);
				float scalarOut = (sinf((x * glm::pi<float>()) / 2.0f)) * 0.6f + 0.4f;
				glm::vec3 deltaPosition = forward * linearSpeed * std::min(scalarIn, scalarOut) * timestep;
				transformComp.translation += deltaPosition;
				transformComp.updateTransform();

				float dot = glm::dot(toTarget, FSMComp.waypointNorms[FSMComp.nextWaypoint]);
				Log::info("Pos {0} {1} {2} Target {3} {4} {5}", transformComp.translation.x, transformComp.translation.y, transformComp.translation.z, targetWaypoint.x, targetWaypoint.y, targetWaypoint.z);
				//Log::info("DOT {6} fwd {0} {1} {2} normal {3} {4} {5}", toTarget.x, toTarget.y, toTarget.z, FSMComp.waypointNorms[FSMComp.nextWaypoint].x, FSMComp.waypointNorms[FSMComp.nextWaypoint].y, FSMComp.waypointNorms[FSMComp.nextWaypoint].z, dot);
				if (dot < 0.0f) {
					FSMComp.currentState = SimpleAI::State::turning;
					FSMComp.previousWaypoint = FSMComp.nextWaypoint;
					FSMComp.nextWaypoint = (++FSMComp.nextWaypoint) % FSMComp.waypoints.size();
				}*/
				break;
			}
		}
	}

}