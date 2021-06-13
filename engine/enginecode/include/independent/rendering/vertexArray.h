/** \file vertexArray.h */
#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"

namespace Engine
{
	/** \class VertexArray
	*	\brief A class for an API agnostic vertex arrays.
	*/
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;					//!< deconstructor.
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;	//!< add a vertex buffer.
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;		//!< set the index buffer.
		virtual uint32_t getDrawCount() = 0;				//!< get the draw count of index buffer.
		virtual inline uint32_t getID() const = 0;			//!< gets and returns the renderer ID.

		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const = 0;			//!< get the vertex buffers.
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;		//!< get the index buffers.

		static VertexArray* create();		//!< please note, function declared in renderAPI.cpp
	private:

	};
}
