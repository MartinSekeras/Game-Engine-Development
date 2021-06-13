/** \file GLFWSystem.h */
#pragma once

#include "systems/system.h"
#include "systems/log.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWSystem
	*	\brief GLFW System class, inheriting from System. To initiate and terminate the GLFW System.
	*/
	class GLFWSystem : public System
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...)	override	//!< starts the GLFW system, kicks an error if unable to do so.
		{
			auto errorCode = glfwInit();		
			if (!errorCode)
			{
				Log::error("Cannot initiate GLFW: {0}", errorCode);
			}
		}
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override	//!< stops the GLFW system.
		{
			glfwTerminate();
		}
	};
}