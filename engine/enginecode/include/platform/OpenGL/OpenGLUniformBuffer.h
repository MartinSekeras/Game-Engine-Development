/** \file OpenGLUniformBuffer.h */
#pragma once

#include "rendering/uniformBuffer.h"

namespace Engine
{
	/* \class OpenGLUniformBuffer
	*  \brief OpenGL specific class to create, set and attah the appropriate uniform buffer; inheriting from UniformBuffer.
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout);						//!< constructor.
		~OpenGLUniformBuffer();														//!< destructor.
		inline uint32_t getID() override { return m_OpenGL_ID; }					//!< accessor for openGL ID.
		inline UniformBufferLayout getLayout() override { return m_BufferLayout; }	//!< accessor for the uniform buffer layout.
		void attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char* blockName) override;	//!< send data to the block.
		void uploadDataToBlock(const char* uniformName, void * data) override;		//!< create function, a little like a constructor. Please note, function declared in renderAPI.cpp
	private:
		uint32_t m_OpenGL_ID;					//!< OpenGL ID.
		static uint32_t s_blockNumber;			//!< a global block number.
	};
}