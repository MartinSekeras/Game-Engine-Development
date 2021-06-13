/** \file window.cpp */

#include "engine_pch.h"
#include "core/window.h"
#include "platform/GLFW/GLFWWindowImplement.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	/*
	Window* Window::createWindow(const WindowProperties& properties)
	{
		//everytime we create a window, create a new win32 window.
		return new Win32Window(properties);
	}
#else
*/
	Window* Window::createWindow(const WindowProperties& properties)
	{
		//everytime we create a window, create a new GLFW Window.
		return new GLFWWindowImplement(properties);
	}
#endif

}