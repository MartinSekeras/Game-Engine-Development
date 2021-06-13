/** \file OpenGLVertexBuffer.h */
#pragma once

#include "rendering/vertexBuffer.h"

namespace Engine
{
	/** \class OpenGLVertexBuffer.
	*	\brief OpenGL specific class for vertex buffers.
	*/
	class OpenGLVertexBuffer : public VertexBuffer	
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); 		//!< constructor - void* for vertices as currently unsure what type they'll be.
		virtual ~OpenGLVertexBuffer();			//!< destructor.
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) override;		//!< edit function, to edit the vertex buffer; same params as constructor. Don't need a BufferLayout as that will be set, will need a uint32_t offset to place the buffer.
		virtual inline uint32_t getID() const override { return m_OpenGL_ID; }	//!< gets and returns the renderer ID.
		virtual inline VertexBufferLayout& const getLayout() override { return m_layout; }	//!< gets and returns the buffer layout

	private:
		uint32_t m_OpenGL_ID;		//!< OpenGL render identifier 
		VertexBufferLayout m_layout;		//!< buffer layout
	};
}
