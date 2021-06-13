#include "engine_pch.h"
#include "components/componentBasedCameras.h"
#include "engine.h"


namespace Engine
{
	namespace CamraSystem
	{
		void onUpdate()
		{
			entt::registry& registry = Application::getInstance().m_registry;

			//get camera and transform from the registry
			auto currentCameraEntity = registry.view<CurrentCameraComponent>().front();
			auto&[currentCamera, cameraTransformComp] = registry.get<PerspectiveCameraComponent, TransformComponent>(currentCameraEntity);
			glm::mat4& cameraTransform = cameraTransformComp.getTransform();

			cameraTransform = cameraTransformComp.updateTransform();

			//update current camera 
			if (currentCamera.settings.cameraType == CameraTypes::FreeEuler)
			{
				currentCamera.view = glm::inverse(cameraTransform);
			}
			else if (currentCamera.settings.cameraType == CameraTypes::Follow)
			{
				glm::vec3 right = { cameraTransform[0][0], cameraTransform[0][1], cameraTransform[0][2] };
				glm::vec3 forward = { cameraTransform[2][0], cameraTransform[2][1], cameraTransform[2][2] };

				glm::vec3 up = { cameraTransform[1][0], cameraTransform[1][1], cameraTransform[1][2] };
				glm::vec3 entityPosition = { cameraTransform[3][0], cameraTransform[3][1], cameraTransform[3][2] };

				glm::vec3 posDelta(0.f);
				posDelta += forward * currentCamera.settings.offset.z;
				posDelta += right * currentCamera.settings.offset.x;
				posDelta += up * currentCamera.settings.offset.y;

				glm::vec3 camPosition = entityPosition + posDelta;
				posDelta = glm::normalize(posDelta);
				glm::vec3 camForward = posDelta;
				glm::vec3 camRight = glm::cross({ 0,1,0 }, posDelta);
				glm::vec3 camUp = glm::normalize(glm::cross(camRight, -camForward));

				camRight = glm::cross(camUp, posDelta);

				glm::mat4 camerTransformWithOffset;
				camerTransformWithOffset[0] = { camRight[0], camRight[1], camRight[2], 0.f };
				camerTransformWithOffset[1] = { camUp[0], camUp[1], camUp[2], 0.f };
				camerTransformWithOffset[2] = { camForward[0], camForward[1], camForward[2], 0.f };
				camerTransformWithOffset[3] = { camPosition[0], camPosition[1], camPosition[2], 0.f };

				currentCamera.view = inverse(camerTransformWithOffset);
			}
		}


		entt::entity nextCamera()
		{
			entt::registry& registry = Application::getInstance().m_registry;

			auto currentCameraEntity = registry.view<CurrentCameraComponent>().front();
			auto allCamerasView = registry.view<PerspectiveCameraComponent>();

			for (int i = 0; i < allCamerasView.size(); i++)
			{
				if (currentCameraEntity == allCamerasView[i])
				{
					//Remove Current camera
					registry.remove<CurrentCameraComponent>(currentCameraEntity);
					if (i < allCamerasView.size() - 1) currentCameraEntity = allCamerasView[++i];//Next Camera
					else currentCameraEntity = allCamerasView[0]; //Loop around
					//Add current camera to next camera
					registry.emplace<CurrentCameraComponent>(currentCameraEntity);
					continue;
				}
			}

			return currentCameraEntity;
		}
	}
}