/* \file RenderComponent.h */

#pragma once

#include "renderer/renderer3D.h"
#include "systems/log.h"
#include "rendering/shaders.h"
#include "rendering/geometry.h"
#include "renderer/renderer3DVertex.h"
#include "renderer/rendererCommons.h"


namespace Engine
{
	class RenderComponent
	{
	public:

		// Renderer3DVertex 
		RenderComponent(std::vector<TPVertexNormalised>& vertices, std::vector<uint32_t>& indices, std::shared_ptr<Material> pMaterial) : material(pMaterial)
		{
			std::shared_ptr<VertexBuffer> tmpVBO;
			std::shared_ptr<IndexBuffer> tmpIBO;
			//create/reset the VAO, VBO & IBO.
			geometry.reset(VertexArray::create());
			tmpVBO.reset(VertexBuffer::create(vertices.data(), sizeof(TPVertexNormalised) * vertices.size(), TPVertexNormalised::getBufferLayout()));
			tmpIBO.reset(IndexBuffer::create(indices.data(), indices.size()));

			//set the vertex and index buffers.
			geometry->addVertexBuffer(tmpVBO);
			geometry->setIndexBuffer(tmpIBO);
		}
		
		std::shared_ptr<VertexArray> geometry;
		std::shared_ptr<Material> material;

	};
}
