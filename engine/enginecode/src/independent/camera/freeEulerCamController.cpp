/** \file freeEulerCamController.cpp */
#include "engine_pch.h"
#include "camera/freeEulerCamController.h"

namespace Engine
{
	FreeEulerCamController::FreeEulerCamController(FreeEulerParams& params) :
		m_params(params),
		m_aspectRatio(params.width / params.height)
	{
		m_lastMousePosition = InputPoller::getMousePosition();

		m_camera.projection = glm::perspective(m_params.fovY, m_aspectRatio, m_params.nearClip, m_params.farClip);

		rotX = glm::rotate(glm::mat4(1.f), m_params.rotationX, glm::vec3(1.0f, 0.f, 0.f));
		rotY = glm::rotate(glm::mat4(1.f), m_params.rotationY, glm::vec3(0.0f, 1.f, 0.f));
		rotZ = glm::rotate(glm::mat4(1.f), m_params.rotationZ, glm::vec3(0.0f, 0.f, 1.f));

		m_params.position = m_params.topDownCameraOffset;
		rotY = glm::rotate(glm::mat4(1.f), m_params.topDownCameraRotation, glm::vec3(0.0f, 1.0f, 0.f));
		m_params.rotationX = m_params.topDownCameraRotation;

		m_orientation = rotX * rotY * rotZ;
		m_transform = glm::translate(glm::mat4(1.0f), m_params.position) * m_orientation;

		m_camera.view = inverse(m_transform);
	}


	void FreeEulerCamController::onUpdate(float time)
	{
		if (m_params.layer->isFocused())
		{			//getting and setting the rotation of the camera.
			rotX = glm::rotate(glm::mat4(1.0f), m_params.rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			rotY = glm::rotate(glm::mat4(1.0f), m_params.rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			rotZ = glm::rotate(glm::mat4(1.0f), m_params.rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
	
			//set the transform and set to the camera view.
			m_orientation = rotX * rotY * rotZ;
			m_transform = glm::translate(glm::mat4(1.0f), m_params.position) * m_orientation;
			m_camera.view = glm::inverse(m_transform);
		}
	}
	
	
	void FreeEulerCamController::onUpdate(float time, TransformComponent transformToFollow)
	{
		if (m_params.layer->isFocused())
		{
			//get current position and rotation.
			glm::vec3 currentPosition = m_params.position;
			float currentRotY = m_params.rotationY;
			 
			//get target following position and rotations.
			glm::vec3 followPosition = transformToFollow.getTranslation();
			//float followRotX = transformToFollow.getRotationX();
			//float followRotY = transformToFollow.getRotationY();
			//float followRotZ = transformToFollow.getRotationZ();

			//set position (+ offsets) and rotations for camera to be same as object following.
			m_params.position = followPosition + m_params.playerFollowCameraOffset;
			m_params.rotationX = -0.7875f;
			m_params.rotationY = 0.0f;
			m_params.rotationZ = 0.0f;

			//getting and setting the rotation of the camera.
			rotX = glm::rotate(glm::mat4(1.0f), m_params.rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			rotY = glm::rotate(glm::mat4(1.0f), m_params.rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			rotZ = glm::rotate(glm::mat4(1.0f), m_params.rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));

			//set the transform and set to the camera view.
			m_orientation = rotX * rotY * rotZ;
			m_transform = glm::translate(glm::mat4(1.0f), m_params.position) * m_orientation;
			m_camera.view = glm::inverse(m_transform);
		}
	}
	
	void FreeEulerCamController::onEvent(Event & event)
	{

	}

	void FreeEulerCamController::onResize(WindowResizeEvent& event)
	{
		m_params.width = event.getWidth();
		m_params.height = event.getHeight();

		m_aspectRatio = m_params.width / m_params.height;
		m_camera.projection = glm::perspective(m_params.fovY, m_aspectRatio, m_params.nearClip, m_params.farClip);
		m_lastMousePosition = GLFWInputPoller::getMousePosition();
	}
}