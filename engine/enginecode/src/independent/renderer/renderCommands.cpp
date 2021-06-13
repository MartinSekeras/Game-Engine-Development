/** \file renderCommands.cpp */

#include "engine_pch.h"
#include "renderer/renderCommands.h"
#include "rendering/renderAPI.h"
#include <glad/glad.h>

namespace Engine
{
	std::function<void(void)> RenderCommandsFactory::getClearColourAndDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []() 
			{ 
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandsFactory::getSetglEnableDepthTestCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []()
			{
				glEnable(GL_DEPTH_TEST);
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandsFactory::getSetglDisableDepthTestCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []()
			{
				glDisable(GL_DEPTH_TEST);
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandsFactory::getSetglEnableBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []()
			{
				glEnable(GL_BLEND);
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandsFactory::getSetglDisableBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []()
			{
				glDisable(GL_BLEND);
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	std::function<void(void)> RenderCommandsFactory::getSetglBlendFuncCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return []()
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}

	//function takes in arguments... therefore lambdas were used to implement it.
	std::function<void(void)> RenderCommandsFactory::getSetClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::OpenGL:
			return [r, g, b, a]()
			{ 
				glClearColor(r, g, b, a); 
			};
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
}