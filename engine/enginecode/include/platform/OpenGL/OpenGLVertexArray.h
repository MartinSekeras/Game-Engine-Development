/** \file OpenGLVertexArray.h */
#pragma once

#include "rendering/vertexArray.h"

namespace Engine
{
	/** \class OpenGLVertexArray
	*	\brief OpenGL specific class for vertex arrays.
	*/
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();								//!< constructor.
		virtual ~OpenGLVertexArray();						//!< deconstructor.
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;	//!< add a vertex buffer.
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;		//!< set the index buffer.
		virtual uint32_t getDrawCount() override;													//!< get the draw count of index buffer.
		virtual inline uint32_t getID() const override { return m_OpenGL_ID; }						//!< gets and returns the renderer ID.
		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const override { return m_vertexBuffer; };	//!< get the vertex buffers.
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return m_indexBuffer; };					//!< get the index buffers.

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer;		//!< shared pointe to hold the vertex buffer.
		std::shared_ptr<IndexBuffer> m_indexBuffer;						//!< shared pointe to hold the index buffer.
		uint32_t m_OpenGL_ID;						//!< OpenGL render identifier.
		uint32_t m_verArrAttributeIndex = 0;		//!< attribute index.
	};
}
