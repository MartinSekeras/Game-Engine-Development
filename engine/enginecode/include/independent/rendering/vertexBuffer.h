/** \file vertexBuffer.h */
#pragma once

#include <cstdint>
#include "rendering/bufferLayout.h"

namespace Engine
{
	/** \class VertexBuffer
	*	\brief A class for an API agnostic vertex buffer.
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;										//!< virtual destructor.
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0;	//!< virtual to edit function, to edit the vertex buffer.
		virtual inline uint32_t getID() const = 0;								//!< virtual to gets and returns the renderer ID.
		virtual inline const VertexBufferLayout& const getLayout() = 0;			//!< virtual to gets and returns the buffer layout.

		static VertexBuffer* create(void* vertices, uint32_t size, const VertexBufferLayout& layout);	//!< please note, function declared in renderAPI.cpp

	private:
		
	};
}