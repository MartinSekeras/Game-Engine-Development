/** renderer3D.cpp */

#include "engine_pch.h"
#include "renderer/renderer3D.h"
#include <glad/glad.h>

namespace Engine
{
	//initialise static variables.
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;

	void Renderer3D::init()
	{
		s_data.reset(new InternalData);

		unsigned char whitePixel[4] = { 255, 255, 255, 255 };		//a white pixel.
		s_data->defaultTexture.reset(Textures::create(1, 1, 4, whitePixel));
		s_data->defaultTint = { 1.0f, 1.0f, 1.0f, 1.0f };

		//set the UBOs for the camera.
		s_data->cameraUBO.reset(UniformBuffer::create(UniformBufferLayout(
			{
				{ "u_projection", ShaderDataType::Mat4 },
				{ "u_view", ShaderDataType::Mat4  }
			})));
		//set the UBOs for the lighting.
		s_data->lightingUBO.reset(UniformBuffer::create(UniformBufferLayout(
			{
				{ "u_lightPos", ShaderDataType::Float3 },
				{ "u_viewPos", ShaderDataType::Float3 },
				{ "u_lightColour", ShaderDataType::Float3 }
			})));
	}

	void Renderer3D::begin(const SceneWideUniforms& sceneWideUniforms)
	{
		//bind that buffer to the cameraUBO.
		glBindBuffer(GL_UNIFORM_BUFFER, s_data->cameraUBO->getID());
		s_data->cameraUBO->uploadDataToBlock("u_projection", sceneWideUniforms.at("u_projection").second);
		s_data->cameraUBO->uploadDataToBlock("u_view", sceneWideUniforms.at("u_view").second);

		//bind that buffer to the lightingUBO.
		glBindBuffer(GL_UNIFORM_BUFFER, s_data->lightingUBO->getID());
		s_data->lightingUBO->uploadDataToBlock("u_lightPos", sceneWideUniforms.at("u_lightPos").second);
		s_data->lightingUBO->uploadDataToBlock("u_viewPos", sceneWideUniforms.at("u_viewPos").second);
		s_data->lightingUBO->uploadDataToBlock("u_lightColour", sceneWideUniforms.at("u_lightColour").second);
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material> material, const glm::mat4 & model)
	{
		//TO DO - to make API agnostic (below isn't, using opengl function), just put the bind functions into my classes. Need a shader bind function and VAO bind function, maybe submit render function too.
		//first bind the shader.
		glUseProgram(material->getShader()->getID());
		
		//apply the material uniforms (per draw uniforms).
		material->getShader()->uploadMat4("u_model", model);		//everything will have a model applied, so do this here before checking.
		
		if (material->isFlagSet(Material::flag_defaultTexture))
			glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());
		else if (material->isFlagSet(Material::flag_diffuseTexture))
			glBindTexture(GL_TEXTURE_2D, material->getTexture(Material::flag_diffuseTexture)->getID());
		else if (material->isFlagSet(Material::flag_specularTexture))
			glBindTexture(GL_TEXTURE_2D, material->getTexture(Material::flag_specularTexture)->getID());
		else if (material->isFlagSet(Material::flag_reflectionTexture))
			glBindTexture(GL_TEXTURE_2D, material->getTexture(Material::flag_reflectionTexture)->getID());
		else if (material->isFlagSet(Material::flag_emmisiveTexture))
			glBindTexture(GL_TEXTURE_2D, material->getTexture(Material::flag_emmisiveTexture)->getID());
		else if (material->isFlagSet(Material::flag_normalTexture))
			glBindTexture(GL_TEXTURE_2D, material->getTexture(Material::flag_normalTexture)->getID());
		else glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());														
		material->getShader()->uploadInt("u_texData", 0);

		//now check whether the tint flag is set.
		if (material->isFlagSet(Material::flag_tint))				
			material->getShader()->uploadFloat4("u_tint", material->getTint());
		else
			material->getShader()->uploadFloat4("u_tint", s_data->defaultTint);

		//bind geometry (VAO & IBO).
		glBindVertexArray(geometry->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer()->getID());

		//finally, submit the draw call.
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}


	void Renderer3D::end()
	{
		s_data->sceneWideUniforms.clear();
	}

	void Renderer3D::attachShader(std::shared_ptr<Shaders> shader)
	{
		//attach them pesky shaders!
		s_data->cameraUBO->attachShaderBlock(shader, "b_camera");
		s_data->lightingUBO->attachShaderBlock(shader, "b_lights");
	}

	inline std::shared_ptr<Textures> Material::getTexture(uint32_t textureFlag) const
	{
		if (isFlagSet(textureFlag))
		{
			switch (m_flags & textureFlag)
			{	
			case flag_diffuseTexture : 
				return m_texture[0];
				break;
			case flag_specularTexture:
				return m_texture[1];
				break;
			case flag_reflectionTexture:
				return m_texture[2];
				break;
			case flag_emmisiveTexture:
				return m_texture[3];
				break;
			case flag_normalTexture:
				return m_texture[4];
				break;
			}
		}
		return nullptr;
	}
}