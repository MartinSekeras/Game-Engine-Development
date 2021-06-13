/** \file GLFWInputPoller.h */
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/*	\class GLFWInputPoller
	*	\brief OpenGL specific input poller to get current mouse and/or keyboard state.
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keycode);			//!< is key pressed?
		static bool isMouseButtonPressed(int32_t button);	//!< is mouse button pressed?
		static glm::vec2 getMousePosition();				//!< get current mouse position.
		static void setCurrentWindow(GLFWwindow* window) { s_window = window; }	//!< set the current window we are in.
	private:
		static GLFWwindow* s_window;		//!< current GLFW window.
	};
}