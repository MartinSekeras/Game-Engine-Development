/** \file indexBuffer.h */
#pragma once
#include <cstdint>

namespace Engine
{
	/** \class IndexBuffer
	*	\brief A class for an API agnostic index buffer.
	*/
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;					//!< virtual destructor.
		virtual inline uint32_t getID() const = 0;			//!< virtual function to get and return the renderer ID.
		virtual inline uint32_t getCount() const = 0;		//!< virtual function to get and return the count.
		static IndexBuffer* create(uint32_t* indices, uint32_t count);		//!< please note, function declared in renderAPI.cpp
	};
}