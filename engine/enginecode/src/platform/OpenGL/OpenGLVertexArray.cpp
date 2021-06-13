/** \file OpenGLVertexArray.cpp */

#include "engine_pch.h"
#include "glad/glad.h"
#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	namespace SDT
	{
		static GLenum toGLType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte2:  return GL_UNSIGNED_BYTE;
			case ShaderDataType::Byte4:  return GL_UNSIGNED_BYTE;
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Short:  return GL_SHORT;
			case ShaderDataType::Short2: return GL_SHORT;
			case ShaderDataType::Short3: return GL_SHORT;
			case ShaderDataType::Short4: return GL_SHORT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			default: return GL_INVALID_ENUM;
			}
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID);
		glBindVertexArray(m_OpenGL_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID);
	}

	//TO DO - need to consider Mat3 and Mat4s as they are different; they cannot be passed directly as a vertice attribute.
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_vertexBuffer.push_back(vertexBuffer);

		//need to bind first.
		glBindVertexArray(m_OpenGL_ID);
		//then bind the buffer.
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getID());

		//get layout and then iterate over it.
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			uint32_t normalised = GL_FALSE;
			if (element.m_normalised)
			{
				normalised = GL_TRUE;
			}

			//FUTURE - if loading mat4s will need changing.
			//OK for now
			glEnableVertexAttribArray(m_verArrAttributeIndex);
			glVertexAttribPointer(
				m_verArrAttributeIndex,	
				SDT::componentCount(element.m_dataType),	
				SDT::toGLType(element.m_dataType),		
				normalised,				
				layout.getStride(),		
				(void*) element.m_offset
			);
			m_verArrAttributeIndex++;
		}

	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	}

	uint32_t OpenGLVertexArray::getDrawCount()
	{
		if (m_indexBuffer)
		{
			return m_indexBuffer->getCount();
		}
		else
		{
			return 0;
		}
	}
}