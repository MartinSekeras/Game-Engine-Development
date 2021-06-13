/** \file renderer3D.h */
#pragma once
#include "renderer/rendererCommons.h"

namespace Engine
{
	/** \struct TextureTypeStruct
	*	\brief Struct that holds variety of different textures for the Material class
	*/
	struct TextureTypeStruct
	{
		std::shared_ptr<Textures> diffuseTexture	= nullptr;
		std::shared_ptr<Textures> specularTexture	= nullptr;
		std::shared_ptr<Textures> reflectionTexture = nullptr;
		std::shared_ptr<Textures> emmisiveTexture	= nullptr;
		std::shared_ptr<Textures> normalTexture		= nullptr;
		std::shared_ptr<Textures> defaultTexture	= nullptr;
	};

	/* \class Material
	*  \brief Holds a shader and all the uniform data that is associated with specific shader.
	*/
	class Material
	{
	public:
		Material(const std::shared_ptr<Shaders>& shader, const TextureTypeStruct& texture, const glm::vec4& tint) :
			m_shader(shader)
		{
			if (texture.diffuseTexture) setDiffuseTexture(texture.diffuseTexture);
			if (texture.specularTexture) setSpecularTexture(texture.specularTexture);
			if (texture.reflectionTexture) setReflectionTexture(texture.reflectionTexture);
			if (texture.emmisiveTexture) setEmmisiveTexture(texture.emmisiveTexture);
			if (texture.normalTexture) setNormalTexture(texture.normalTexture);
			if (texture.defaultTexture) setDefaultTexture(texture.defaultTexture);

			if (m_flags == 0)
			{ 
				setTint(tint);
			}
		}			//!< constructor will all the variables within the params, all initialised within the initialiser list, flag for texture and tint set within function.
		
		Material(const std::shared_ptr<Shaders>& shader, const TextureTypeStruct& texture) :
			m_shader(shader),
			m_tint(0.0f)
		{
			if (texture.diffuseTexture) setDiffuseTexture(texture.diffuseTexture);
			if (texture.specularTexture) setSpecularTexture(texture.specularTexture);
			if (texture.reflectionTexture) setReflectionTexture(texture.reflectionTexture);
			if (texture.emmisiveTexture) setEmmisiveTexture(texture.emmisiveTexture);
			if (texture.normalTexture) setNormalTexture(texture.normalTexture);
			if (texture.defaultTexture) setDefaultTexture(texture.defaultTexture);
		}			//!< constructor taking shader and texture within within the params, initialised within the initialiser list, flag for texture set within function.

		inline std::shared_ptr<Shaders> getShader() const { return m_shader; }		//!< accessor function for getting the shader.
		inline std::shared_ptr<Textures> getTexture(uint32_t textureFlag) const;	//!< accessor function for getting the texture.
		inline glm::vec4 getTint() const { return m_tint; }		//!< accessor function to get the tint.

		void setDiffuseTexture(const std::shared_ptr<Textures>& diffuse_texture)
		{
			m_texture[0] = diffuse_texture;
			setFlag(flag_diffuseTexture);
		}	//!< set the diffuse_texture in the m_textures array and its corresponding flag.

		void setSpecularTexture(const std::shared_ptr<Textures>& specular_texture)
		{
			m_texture[1] = specular_texture;
			setFlag(flag_specularTexture);
		}	//!< set the specular_texture in the m_textures array and its corresponding flag.

		void setReflectionTexture(const std::shared_ptr<Textures>& reflection_texture)
		{
			m_texture[2] = reflection_texture;
			setFlag(flag_reflectionTexture);
		}	//!< set the reflection_texture in the m_textures array and its corresponding flag.

		void setEmmisiveTexture(const std::shared_ptr<Textures>& emmisive_texture)
		{
			m_texture[3] = emmisive_texture;
			setFlag(flag_emmisiveTexture);
		}	//!< set the diffuse emmisive_texture in the m_textures array and its corresponding flag.

		void setNormalTexture(const std::shared_ptr<Textures>& normal_texture)
		{
			m_texture[4] = normal_texture;
			setFlag(flag_normalTexture);
		}	//!< set the normal_texture in the m_textures array and its corresponding flag.

		void setDefaultTexture(const std::shared_ptr<Textures>& default_texture)
		{
			m_texture[5] = default_texture;
			setFlag(flag_defaultTexture);
		}	//!< set the no_texture its corresponding flag.

		void setTint(const glm::vec4 tint) 
		{
			m_tint = tint; 
			setFlag(flag_tint);
		}		//!< function to set the tint colour.

		bool isFlagSet(uint32_t flag) const { return m_flags & flag; }	//!< function to check whether the flag has been set. If either return anything than 0, flag is set.

		constexpr static uint32_t flag_diffuseTexture = 1 << 0;		//!< 00000001
		constexpr static uint32_t flag_specularTexture = 1 << 1;	//!< 00000010
		constexpr static uint32_t flag_reflectionTexture = 1 << 2;	//!< 00000100
		constexpr static uint32_t flag_emmisiveTexture = 1 << 3;	//!< 00001000
		constexpr static uint32_t flag_normalTexture = 1 << 4;		//!< 00010000
		constexpr static uint32_t flag_defaultTexture = 1 << 5;		//!< 00100000
		constexpr static uint32_t flag_tint = 1 << 6;				//!< 01000000

	private:
		uint32_t m_flags = 0;						//!< bitfield representation of the shader settings.
		std::shared_ptr<Shaders> m_shader;			//!< the shader.
		std::array<std::shared_ptr<Textures>, 5> m_texture;			//!< the texture for the material.
		glm::vec4 m_tint;							//!< coloured tint to be applied to the geometry.
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; }	//!< function to set the flag.
	};

	/* \class Renderer3D
	*  \brief A renderer renders 3D geometry instantly (not batched), that uses OpenGL.
	*/
	class Renderer3D
	{
	public:
		static void init();												//!< initiate the renderer.
		static void begin(const SceneWideUniforms& sceneWideUniforms);	//!< begin a new 3D scene.
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material> material, const glm::mat4& model);		//!< submit a new piece of geometry to be rendered.
		static void end();												//!< end of the current 3D scene.
		static void attachShader(std::shared_ptr<Shaders> shader);		//!< attach the shader.
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms;		//!< replace with UBO in the future.
			std::shared_ptr<Textures> defaultTexture;	//!< empty white texture.
			glm::vec4 defaultTint;						//!< default white tint.
			std::shared_ptr<VertexArray> VAO;			//!< the vertex array.
			std::shared_ptr<UniformBuffer> cameraUBO;	//!< UBO for the camera.
			std::shared_ptr<UniformBuffer> lightingUBO;	//!< UBO for the lighting.
		};												//!< to be used as PURE data.
		static std::shared_ptr<InternalData> s_data;	//!< data internal to the renderer.
	};
}