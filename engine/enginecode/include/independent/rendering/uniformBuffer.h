/** \file uniformBuffer.h */
#pragma once
#include <ctype.h>
#include <memory>
#include <unordered_map>
#include "rendering/bufferLayout.h"
#include "rendering/shaders.h"

namespace Engine
{
	/* \class UniformBuffer
	*  \brief API agnostic class to create, set and attah the appropriate uniform buffer.
	*/
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;				//!< destructor.
		virtual uint32_t getID() = 0;					//!< accessor for openGL ID.
		virtual UniformBufferLayout getLayout() = 0;	//!< accessor for the uniform buffer layout.
		virtual void attachShaderBlock(const std::shared_ptr<Shaders>& shader, const char* blockName) = 0;	//!< get shader and attach to requested block.
		virtual void uploadDataToBlock(const char* uniformName, void* data) = 0;		//!< send data to the block.
		static UniformBuffer* create(const UniformBufferLayout& layout);				//!< create function, a little like a constructor. Please note, function declared in renderAPI.cpp
	protected:
		UniformBufferLayout m_BufferLayout;				//!< uniform bugger layout.
		uint32_t m_blockNumber;							//!< block number for this uniform buffer layout.
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache;			//!< stores the uniform names, including sizes and offsets.
	};
}