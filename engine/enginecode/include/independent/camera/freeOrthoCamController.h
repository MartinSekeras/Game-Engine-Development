/** \file freeOthroCamController.h*/
#pragma once
#include "camera/camera.h"
#include "platform/GLFW/GLFWInputPoller.h"
#include <glm/gtc/matrix_transform.hpp>
#include "events/codes.h"
#include "core/layer.h"
#include "components/transform.h"

namespace Engine
{
	struct Fixed2DParams
	{
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
		float rotation = 0.f;
		float left = 0.f;
		float right = 0.f;
		float bottom = 0.f;
		float top = 0.f;
		float fovY = 45.f;
		float width = 4.f;
		float height = 3.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
		std::shared_ptr<Layer> layer = nullptr;
		float speed = 2.5f;
		float sensitivity = 45.f;

		
	};

	/** \class FreeOthroCamController
	*	\brief Class for controlling a free moving orthographic camera (2D).
	*/
	class FreeOthroCamController : public CameraController
	{	
	public:
		/*
		FreeOthroCamController(glm::vec3 pos, float rot, float left, float right, float bottom, float top) :
			m_position(pos),
			m_rotation(rot)
		{
			m_camera.projection = glm::ortho(left, right, bottom, top);
			m_camera.view = glm::inverse(glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), { 0.0f, 0.0f, 1.0f }));
		}	//!< constructor with its position and rotation; then left, right, bottom and top to set with the window in application.cpp
		*/
		
		FreeOthroCamController(Fixed2DParams& params);

		virtual inline Camera& getCamera() override { return m_camera; }	//!< get the camera.
		virtual void onUpdate(float time) override;							//!< on update function.
		virtual void onUpdate(float time, TransformComponent transformToFollow) override;
		virtual void onEvent(Event& event) override;						//!< on event function.	//TO-DO: change to do just resizing - will need to change projectionmatrix.	
		virtual void onResize(WindowResizeEvent& event) override;
	private:
		Fixed2DParams m_params;
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };						//!< vec3 to take position of camera.
		glm::mat4 m_transform;
		//const float m_zoom = 1.0f;											//!< rate of the zoom.
		//float m_rotation = 0.0f;											//!< the rotation (in degrees) of camera.
		//float m_CamMovementSpeed = 150.0f;									//!< speed of translation in scene.
		//float m_CamRotationSpeed = 25.0f;									//!< speed of rotation in scene.

		glm::vec2 m_lastMousePosition;
		float m_aspectRatio;
	};
}