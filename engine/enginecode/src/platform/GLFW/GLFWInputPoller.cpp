/** \file GLFWInputPoller.cpp */

#include "engine_pch.h"
#include "platform/GLFW/GLFWInputPoller.h"

namespace Engine
{
	//static, so initialising outside of the class.
	GLFWwindow* GLFWInputPoller::s_window = nullptr;

	bool GLFWInputPoller::isKeyPressed(int32_t keycode)
	{
		if (s_window)
		{
			auto answer = glfwGetKey(s_window, keycode);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;

		}
		return false;
	}

	bool GLFWInputPoller::isMouseButtonPressed(int32_t button)
	{
		if (s_window)
		{
			auto answer = glfwGetMouseButton(s_window, button);
			return answer == GLFW_PRESS;

		}
		return false;
	}

	glm::vec2 GLFWInputPoller::getMousePosition()
	{
		if (s_window)
		{
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));

		}
		return glm::vec2(-1.0f, -1.0f);
	}
}