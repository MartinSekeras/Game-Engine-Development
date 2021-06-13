/** \file renderer2D.cpp */


#include "engine_pch.h"
#include "renderer/renderer2D.h"
#include <glad/glad.h>


namespace Engine
{
	//initialise static variables.
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;


	void Renderer2D::init()
	{
		s_data.reset(new InternalData);


		unsigned char whitePixel[4] = { 255, 255, 255, 255 };		//a white pixel to be used in texture..
		s_data->defaultTexture.reset(Textures::create(1, 1, 4, whitePixel));	//set the texture.


		s_data->defaultTint = { 1.0f, 1.0f, 1.0f, 1.0f };		//set the tint.
		s_data->model = glm::mat4(1.0f);						//set the model.


		s_data->shader.reset(Shaders::create("./assets/shaders/quad1.glsl"));		//pass the shader used.
		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f
		};		//the four vertices of a quad; -0.5 to 0.5 (rather that -1.0 to 1.0) for scaling.


		uint32_t indices[4] = { 0, 1, 2, 3 };				//set the indices.

		//create a local VBO & IBO.
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		s_data->VAO.reset(VertexArray::create());			//create a new vertex array.
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));		//set the VBO with vertices array, its size and a vertexbufferlayout of two float2s.
		IBO.reset(IndexBuffer::create(indices, 4));			//set the IBO wih indices array and its count (4).

		//add the VBO & IBO to the VAO.
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		//set the dimensions of the glyph buffer.
		s_data->glyphBufferDimensions = { 256, 256 };
		s_data->glyphBufferSize = s_data->glyphBufferDimensions.x * s_data->glyphBufferDimensions.y * 4 * sizeof(unsigned char);
		s_data->glyphBuffer.reset(static_cast<unsigned char*>(malloc(s_data->glyphBufferSize)));

		//initalise freetype.
		if (FT_Init_FreeType(&s_data->ft))
			Log::error("ERROR: FreeType could not be successfully initialised");

		//create filepath to font and load that font.
		const char* filePath = "./assets/fonts/arial.ttf";
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->fontFace))
			Log::error("ERROR: font could NOT be loaded: {0}", filePath);


		//create a character size and set it.
		int32_t characterSize = 24;
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, characterSize))
			Log::error("ERROR: font size NOT set: {0}", characterSize);


		//initialise the font texture.
		s_data->fontTexture.reset(Textures::create(s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, 4, nullptr));


		//fill the glyph buffer (using old c function memset as they're fast).
		memset(s_data->glyphBuffer.get(), 60, s_data->glyphBufferSize);


		//send glyph buffer to the texture on GPU.
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get());
	}


	void Renderer2D::begin(const SceneWideUniforms& swu)
	{
		//first bind the shader.
		glUseProgram(s_data->shader->getID());


		//apply scene wide uniforms to the shader. 
		// This needs changing to UBO
		for (auto& dataPair : swu)
		{
			const char* uniformName = dataPair.first;
			ShaderDataType sdt = dataPair.second.first;
			void* addressValue = dataPair.second.second;


			switch (sdt)
			{
			case ShaderDataType::Int:
				s_data->shader->uploadInt(uniformName, *(int*)addressValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(uniformName, *(glm::vec3*)addressValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat4(uniformName, *(glm::vec4*)addressValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(uniformName, *(glm::mat4*)addressValue);
				break;
			}
		}


		//bind geometry (VAO & IBO).
		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getID());
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture)
	{
		//first bind the default texture.
		glBindTexture(GL_TEXTURE_2D, texture->getID());


		//now create the model by translating and scaling the model.
		s_data->model = glm::scale(glm::translate(glm::mat4(1.0f), quad.m_translate), quad.m_scale);


		//upload any per-draw-uniforms.
		s_data->shader->uploadInt("u_texData", 0);				//the texture data.
		s_data->shader->uploadFloat4("u_tint", tint);			//the tint data.
		s_data->shader->uploadMat4("u_model", s_data->model);	//the transform of the model.


		//bind geometry (VAO & IBO).
		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getID());


		//now draw it; remember using QUADS, not TRIANGLES.
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}


	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture);
	}


	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<Textures>& texture)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Textures>& texture, float angle, bool degrees)
	{
		//check whether bool degrees tue, is so change angle to radians.
		if (degrees)
		{
			angle = glm::radians(angle);
		}


		//first bind the default texture.
		glBindTexture(GL_TEXTURE_2D, texture->getID());


		//now create the model by translating & scaling the model, plus the rotation.
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), quad.m_translate), angle, { 0.0f, 0.0f, 1.0f }), quad.m_scale);


		//upload any per-draw-uniforms.
		s_data->shader->uploadInt("u_texData", 0);				//the texture data.
		s_data->shader->uploadFloat4("u_tint", tint);			//the tint data.
		s_data->shader->uploadMat4("u_model", s_data->model);	//the transform of the model.


		//bind geometry (VAO & IBO).
		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getID());


		//now draw it; remember using QUADS, not TRIANGLES.
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}


	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees)
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}


	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<Textures>& texture, float angle, bool degrees)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint)
	{
		if (FT_Load_Char(s_data->fontFace, ch, FT_LOAD_RENDER))
		{
			Log::error("Error: Freetype could NOT load the glyph for {0}", ch);
		}
		else
		{
			//get the glyph data.
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width;
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows;
			glm::vec2 glyphSize(glyphWidth, glyphHeight);
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top);


			//calculate the advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6);


			//calculate quad for glyph.
			glm::vec2 glyphHalfExtents(s_data->fontTexture->getWidthF() * 0.5f, s_data->fontTexture->getHeightF() * 0.5f);
			glm::vec2 glyphCentre = (position + glyphBearing) + glyphHalfExtents;
			Quad quad = Quad::createCentreHalfExtents(glyphCentre, glyphHalfExtents);


			//create a RGBA buffer for glyph.
			RtoRGBA(s_data->fontFace->glyph->bitmap.buffer, glyphWidth, glyphHeight);
			//send to GPU.
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get());


			//submit quad
			submit(quad, tint, s_data->fontTexture);
		}
	}


	void Renderer2D::submit(const char* text, const glm::vec2& position, const glm::vec4& tint)
	{
		//calculate the length of the string using strlen
		uint32_t len = strlen(text);


		float advance = 0.0f;
		float x = position.x;


		for (int32_t i = 0; i < len; i++)
		{
			submit(text[i], { x, position.y }, advance, tint);
			x += advance;
		}
	}

	void Renderer2D::end()
	{


	}


	glm::ivec2 Renderer2D::getTextSize(const char* text)
	{
		glm::ivec2 result(0);
		uint32_t len = strlen(text);
		float advance = 0.f;


		for (int32_t i = 0; i < len; i++)
		{
			FT_Load_Char(s_data->fontFace, text[i], FT_LOAD_RENDER);
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows;


			//calculate the advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6);


			result.x += advance;
			result.y = std::max(result.y, static_cast<int>(glyphHeight));

		}
		return result;
	}


	void Renderer2D::RtoRGBA(unsigned char* rBuffer, uint32_t width, uint32_t height)
	{
		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize);


		//ptr walker pointing towards the result.
		unsigned char* pWalker = s_data->glyphBuffer.get();


		for (int32_t i = 0; i < height; i++)
		{
			for (int32_t j = 0; j < width; j++)
			{
				*pWalker = 255; pWalker++;	//R
				*pWalker = 255; pWalker++;	//B
				*pWalker = 255; pWalker++;	//G
				*pWalker = *rBuffer;		//set the alpha channel.
				pWalker++;		//go to R of the next pixel.
				rBuffer++;		//go to next monochrome pixel.
			}
			pWalker += (s_data->glyphBufferDimensions.x - width) * 4;		//times 4 as 4 channels.
		}
	}


	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result;


		result.m_translate = glm::vec3(centre, 0.0f);
		result.m_scale = glm::vec3(halfExtents * 2.0f, 1.0f);


		return result;
	}


	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, float halfExtents)
	{
		Quad result;


		result.m_translate = glm::vec3(centre, 0.0f);
		result.m_scale = glm::vec3(halfExtents * 2.0f, halfExtents * 2.0f, 1.0f);


		return result;
	}


	Quad Quad::createCreateTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size)
	{
		Quad result;


		result.m_translate = glm::vec3(topLeft + size * 0.5f, 0.0f);
		result.m_scale = glm::vec3(size /* 0.5f*/, 1.0f);


		return result;
	}


	Quad Quad::createCreateTopLeftSize(const glm::vec2& topLeft, float size)
	{
		Quad result;


		result.m_translate = glm::vec3(topLeft + size * 0.5f, 0.0f);
		result.m_scale = glm::vec3(size, size, 1.0f);


		return result;
	}


	Quad Quad::createCreateTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight)
	{
		Quad result;


		result.m_translate = glm::vec3(topLeft, 0.0f);
		result.m_scale = glm::vec3((bottomRight.x - topLeft.x), (bottomRight.y - topLeft.y), 1.0f);


		return result;
	}
}