/* \file ComponentBasedCameras.h */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entt/entt.hpp>

namespace Engine
{
	enum class CameraTypes { FreeEuler, Follow };

	struct PerspectiveCameraParams
	{
		float fovY = 45.f;
		glm::vec2 size = { 800.f, 600.f };
		float nearClip = 0.1f;
		float farClip = 100.f;
		glm::vec3 offset = { 0.f, 0.f, 0.f };
		CameraTypes cameraType = CameraTypes::FreeEuler;
		//float smoothTime = 0.f; // Used to apply easing function, smooth start and stop juice
		//float bounceTime = 0.f; // Used to apply easing function bounce
		//float inverseJuiceTime = 1.0f / 0.25f;

	};

	class PerspectiveCameraComponent
	{
	public:
		PerspectiveCameraComponent(PerspectiveCameraParams& params, glm::mat4 transform) : settings(params)
		{
			//Need to change this when not standard camera
			view = glm::inverse(transform);
			projection = glm::perspective(settings.fovY, settings.size.x / settings.size.y, settings.nearClip, settings.farClip);
		}

		glm::mat4 view;
		glm::mat4 projection;

		PerspectiveCameraParams settings;
	};

	struct CurrentCameraComponent
	{

	};

	namespace CamraSystem
	{
		void onUpdate();

		entt::entity nextCamera();
	}
}
