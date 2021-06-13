/** \file OpenGLUniformBuffer.cpp */
#include "engine_pch.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	//initialise static block number to 0.
	uint32_t OpenGLUniformBuffer::s_blockNumber = 0;

	OpenGLUniformBuffer::OpenGLUniformBuffer(const UniformBufferLayout & layout) 
	{
		m_blockNumber = s_blockNumber;		//!< set this block number to the global block number.
		s_blockNumber++;					//!< now increment the global block number.

		m_BufferLayout = layout;

		//generate, bind and set UBO.
		glGenBuffers(1, &m_OpenGL_ID);														//generate Buffer for UBO. 
		glBindBuffer(GL_UNIFORM_BUFFER, m_OpenGL_ID);										//bind buffer for UBO.
		glBufferData(GL_UNIFORM_BUFFER, layout.getStride(), nullptr, GL_DYNAMIC_DRAW);		//send data and size.
		glBindBufferRange(GL_UNIFORM_BUFFER, m_blockNumber, m_OpenGL_ID, 0, layout.getStride());	//bind the range; to UNI_BUFFER, this block, this ubo, from 0 to data siz (ie all of it).

		//populate the uniform cache.
		for (auto& element : m_BufferLayout)
		{
			m_uniformCache[element.m_name] = std::pair<uint32_t, uint32_t>(element.m_offset, element.m_size);
		}
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char * blockName)
	{
		//now attach to shader.
		uint32_t blockIndex = glGetUniformBlockIndex(shader->getID(), blockName);		//first get the block number off the shader.
		glUniformBlockBinding(shader->getID(), blockIndex, m_blockNumber);				//link to binding point.

	}

	void OpenGLUniformBuffer::uploadDataToBlock(const char * uniformName, void * data)
	{
		//TO DO - a test to make sure that it contains something.
		auto& pair = m_uniformCache[uniformName];
		glBufferSubData(GL_UNIFORM_BUFFER, pair.first, pair.second, data);
	}
}