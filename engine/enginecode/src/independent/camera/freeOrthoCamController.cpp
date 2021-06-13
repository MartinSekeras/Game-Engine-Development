/** \file freeOrthoCamController.cpp */

#include "engine_pch.h"
#include "camera/freeOrthoCamController.h"
#include "core/inputPoller.h"
#include "events/codes.h"

namespace Engine
{
	FreeOthroCamController::FreeOthroCamController(Fixed2DParams& params) :
		m_params(params),
		m_aspectRatio(params.width / params.height)
	{	
		m_lastMousePosition = InputPoller::getMousePosition();
		m_transform = glm::rotate(glm::translate(glm::mat4(1.f), m_params.position), m_params.rotation, { 0,0,1 });

		m_camera.view = inverse(m_transform);
		m_camera.projection = glm::ortho(params.left, params.width, params.height, params.top);
	}


	void FreeOthroCamController::onUpdate(float time)
	{

		if (m_params.layer->isFocused())
		{
			if (GLFWInputPoller::isKeyPressed(NG_KEY_W))	//W
			{
				m_params.position.x += -sin(glm::radians(m_params.rotation)) * m_params.speed * time;
				m_params.position.y += cos(glm::radians(m_params.rotation)) * m_params.speed * time;
			}
			if (GLFWInputPoller::isKeyPressed(NG_KEY_S))	//S
			{
				m_params.position.x -= -sin(glm::radians(m_params.rotation)) * m_params.speed * time;
				m_params.position.y -= cos(glm::radians(m_params.rotation)) * m_params.speed * time;
			}
			if (GLFWInputPoller::isKeyPressed(NG_KEY_A))	//A
			{
				m_params.position.x += cos(glm::radians(m_params.rotation)) * m_params.speed * time;
				m_params.position.y += sin(glm::radians(m_params.rotation)) * m_params.speed * time;
			}
			if (GLFWInputPoller::isKeyPressed(NG_KEY_D))	//D
			{
				m_params.position.x -= cos(glm::radians(m_params.rotation)) * m_params.speed * time;
				m_params.position.y -= sin(glm::radians(m_params.rotation)) * m_params.speed * time;
			}

			if (GLFWInputPoller::isKeyPressed(NG_KEY_Q))	//Q
			{
				//to-do - shift to radians.
				m_params.rotation += time * m_params.speed;
				if (m_params.rotation > 180.0f)
					m_params.rotation -= 360.0f;
				else if (m_params.rotation <= -180.0f)
					m_params.rotation += 360.0f;
			}
			if (GLFWInputPoller::isKeyPressed(NG_KEY_E))	//E
			{
				m_params.rotation -= time * m_params.speed;
				if (m_params.rotation > 180.0f)
					m_params.rotation -= 360.0f;
				else if (m_params.rotation <= -180.0f)
					m_params.rotation += 360.0f;
			}

			//update the view matrix.
			m_transform = glm::translate(glm::mat4(1.0f), m_params.position) * m_params.rotation;
			//m_camera.view = glm::inverse(glm::translate(glm::mat4(1.0f), m_params.position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_params.rotation), { 0.0f, 0.0f, 1.0f }));
			m_camera.view = glm::inverse(m_transform);
		}




	}

	void FreeOthroCamController::onUpdate(float time, TransformComponent transformToFollow)
	{
	}

	void FreeOthroCamController::onEvent(Event & event)
	{
		//for resize of window.
	}

	void FreeOthroCamController::onResize(WindowResizeEvent& event)
	{
		m_params.width = event.getWidth();
		m_params.height = event.getHeight();

		m_aspectRatio = m_params.width / m_params.height;
		m_camera.projection = glm::perspective(m_params.fovY, m_aspectRatio, m_params.nearClip, m_params.farClip);
		m_lastMousePosition = GLFWInputPoller::getMousePosition();
	}


	
}
