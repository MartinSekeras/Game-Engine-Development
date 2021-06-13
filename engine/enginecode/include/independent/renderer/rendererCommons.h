/** \file rendererCommons.h */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glad/glad.h>

#include <unordered_map>
#include <memory>

#include "systems/log.h"

#include "rendering/textures.h"
#include "rendering/shaders.h"
#include "rendering/renderAPI.h"
#include "rendering/vertexArray.h"
#include "rendering/shaderDataType.h"
#include "rendering/uniformBuffer.h"

#include "renderer/renderCommands.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void *>>;
	/* \class RendererCommons
	*  \brief Class to take all the common vars used in both 2D & 3D renderers.
	*/
	class RendererCommons
	{
	public:
		static void actionCommand(std::shared_ptr<RenderCommands>& command) { command->m_action(); }		//!< action the desired command.
	private:

	};
}