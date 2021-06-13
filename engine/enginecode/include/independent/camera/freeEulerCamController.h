/** \file freeEulerCamController.h */

#pragma once
#include "camera/camera.h"
#include "platform/GLFW/GLFWInputPoller.h"
#include "core/inputPoller.h"
#include "events/codes.h"
#include "core/layer.h"
#include "components/transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <entt/entt.hpp>

namespace Engine
{
	struct FreeEulerParams
	{
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

		float rotationX = 0.0f;
		float rotationY = 0.0f;
		float rotationZ = 0.0f;

		float fovY = 45.f;
		float width = 4.f;
		float height = 3.f;
		float nearClip = 0.1f;
		float farClip = 100.f;

		std::shared_ptr<Layer> layer = nullptr;
		float speed = 2.5f;
		float sensitivity = 45.f;

		//camera offset positions.
		glm::vec3 playerFollowCameraOffset = glm::vec3(0.0f, 2.5f, 2.5f);		//designed to follow player.
		glm::vec3 topDownCameraOffset = glm::vec3(0.0f, 20.0f, -0.5f);			//camera to look down on scene from above.

		//camera offset rotations.
		float playerFollowCameraRotation = -0.7875f;
		float topDownCameraRotation = -1.575f;

	};

	/*	\class FreeEulerCamController
	*	\brief Class for controlling a free moving euler camera (3D).
	*/
	class FreeEulerCamController : public CameraController
	{
	public:
		FreeEulerCamController(FreeEulerParams& params);	//!< constructor.
									
		virtual inline Camera& getCamera() override { return m_camera; }	//!< get the camera.
		virtual void onUpdate(float time) override;							//!< on update function.
		virtual void onUpdate(float time, TransformComponent transformToFollow) override;	//!< on update function.
		virtual void onEvent(Event& event) override;						//!< on event function.
		virtual void onResize(WindowResizeEvent& event) override;

	private:
		FreeEulerParams m_params;											//!< Camera settings
		glm::mat4 m_transform;												//!< transform to give location of camera. A mat4 to take vec3s position, forwards, sideways and upwards.
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };						//!< vec3 to take position of camera.

		glm::vec3 forward = { -m_transform[2][0], -m_transform[2][1], -m_transform[2][2] };
		glm::vec3 right = { m_transform[0][0], m_transform[0][1], m_transform[0][2] };

		glm::vec2 m_lastMousePosition;										//!< last position of the mouse.
		glm::mat4 m_orientation;											//!< mat4 for the orientation of the camera.
		//glm::mat4 m_viewProjection;										//!< mat4 to take the view/projection of the camera.
		float m_aspectRatio;												//!< Aspect ratio

		glm::mat4 rotX;
		glm::mat4 rotY;
		glm::mat4 rotZ;
	};
}
