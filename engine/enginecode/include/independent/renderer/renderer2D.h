/** \file renderer2d.h */
#pragma once
#include "renderer/rendererCommons.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{
	/* \class Quad
	*  \brief Class to create Quads for 2D rendering.
	*/
	class Quad
	{
	public:
		Quad() = default;			//!< default constructor.
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);			//!< create a quad with from centre, half extents as a vec2.
		static Quad createCentreHalfExtents(const glm::vec2& centre, float halfExtents);					//!< create a quad with from centre, half extents as a single float.
		static Quad createCreateTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size);				//!< create a quad with from top left, half extents as a vec2.
		static Quad createCreateTopLeftSize(const glm::vec2& topLeft, float size);							//!< create a quad with from top left, half extents as a single float.
		static Quad createCreateTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight);	//!< create a quad with from top left, this with a vec2 as the bottom right.
	private:
		glm::vec3 m_translate = glm::vec3(0.0f);	//!< translation vector.
		glm::vec3 m_scale = glm::vec3(1.0f);		//!< scale vector.
		friend class Renderer2D;					//!< linking as 'friend' with Renderer2D class, this is because Quad shouldn't be happening without Renderer2D, they are absolutely linked, exist together.
	};

	/* \class Renderer2D
	*  \brief A renderer rendering simple 2D primitives.
	*/
	class Renderer2D
	{
	public:
		static void init();					//!< initiate the internal data of the renderer.
		static void	begin(const SceneWideUniforms& swu);								//!< begin a 2D scene.
		static void submit(const Quad& quad, const glm::vec4& tint);					//!< render a tinted (coloured) quad.
		static void submit(const Quad& quad, const std::shared_ptr<Textures>& texture);	//!< render a textured quad.
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture);	//!< render a tinted & textured quad.
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false);			//!< render a tinted & rotated quad.
		static void submit(const Quad& quad, const std::shared_ptr<Textures>& texture, float angle, bool degrees = false);		//!< render a textured & rotated quad.
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture, float angle, bool degrees = false);		//!< render a tinted, textured & rotated quad.

		static void submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint);	//!< render a single character, with tint.
		static void submit(const char* text, const glm::vec2& position, const glm::vec4& tint);			//!< render a string, with tint.

		static void end();					//!< end of the current 2D scene.
		static glm::ivec2 getTextSize(const char* text);
	private:
		struct InternalData
		{
			std::shared_ptr<Textures> defaultTexture;	 //!< empty white texture.
			std::shared_ptr<Shaders> shader;			 //!< the shader used.
			std::shared_ptr<VertexArray> VAO;			 //!< prototypical quad for submitting (don't use geometry/VAO in 2d)
			glm::vec4 defaultTint;						 //!< default white tint.
			glm::mat4 model;							 //!< transform the the model.
														 
			FT_Library ft;								 //!< the freetype library.
			FT_Face fontFace;							 //!< the font face.
			std::shared_ptr<Textures> fontTexture;		 //!< texture for the font.
			glm::ivec2 glyphBufferDimensions;			 //!< dimensions for the buffer size for the glyphs.
			uint32_t glyphBufferSize;					 //!< the size of the glyph.
			std::shared_ptr<unsigned char> glyphBuffer;	 //!< the buffer for glyphs.
		};
		static std::shared_ptr<InternalData> s_data;	//!< data internal to the renderer.
		static void RtoRGBA(unsigned char * rBuffer, uint32_t width, uint32_t height);		//!< method to set memory block and fill with glyph(rbuffer) data.
	};
}