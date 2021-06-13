/** \file renderAPI.cpp */

#include "engine_pch.h"
#include "systems/log.h"

#include "rendering/renderAPI.h"

#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"


namespace Engine
{
	//initalise s_API here, as static and needs doing outside of class.
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(void* vertices, uint32_t size, const VertexBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	Shaders* Shaders::create(const char* vertexFilePath, const char* fragmentFilePath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexFilePath, fragmentFilePath);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	Shaders* Shaders::create(const char* filePath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filePath);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	Textures* Textures::create(const char* filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	Textures* Textures::create(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channel, data);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}

	UniformBuffer* UniformBuffer::create(const UniformBufferLayout& layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No rendering API; not supported, SORT IT OUT!");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(layout);

		case RenderAPI::API::Direct3D:
			Log::error("DIRECT3D rendering API is not supported at this time.");
			break;
		case RenderAPI::API::Vulkan:
			Log::error("VULKAN rendering API is not supported at this time.");
			break;
		}

		//otherwise return nullptr.
		return nullptr;
	}
}