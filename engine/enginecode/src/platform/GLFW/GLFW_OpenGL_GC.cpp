/** \file GLFW_OpenGL_GC.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "systems/log.h"

namespace Engine
{
	GLFW_OpenGL_GC::~GLFW_OpenGL_GC()
	{
		//ImGuiHelper::shutdown();
	}
	void GLFW_OpenGL_GC::init()
	{
		glfwMakeContextCurrent(m_window);

		//now load openGL... <glad/glad.h> will help.
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		//check that it has loaded, error if not.
		if (!result)
		{
			Log::error("Could not create OpenGL context for this current GFLW window: {0}", result);
		}

		//enable OpenGL debugging using a callback
		glEnable(GL_DEBUG_OUTPUT);
		//create this using a lambda to create the function, using the following params taken from kronos.org/../OpenGL-Refpages.
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,		//key one
				GLsizei length,
				const GLchar *message,	//key one
				const void *userParam
				)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				Log::error(message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Log::warn(message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				Log::info(message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				//Log::trace(message);
				break;
			}
		}
		, nullptr);
	}

	void GLFW_OpenGL_GC::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void GLFW_OpenGL_GC::updateViewport(int32_t width, int32_t height)
	{
		glViewport(0, 0, width, height);
	}
}