/** \file OpenGLTexture.cpp */

#include "engine_pch.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include <glad/glad.h>
#include "systems/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
	OpenGLTexture::OpenGLTexture(const char * filepath)
	{
		int width, height, channel;
		unsigned char *data = stbi_load(filepath, &width, &height, &channel, 0);

		init(width, height, channel, data);

		//data passed on so can take off the CPU.
		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data)
	{
		init(width, height, channel, data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_OpenGL_ID);
	}

	void OpenGLTexture::edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data)
	{
		//first bind the texture.
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID);

		//check whether there is any data.
		if (data)
		{
			if (m_channel == 3)
			{
				glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else if (m_channel == 4)
			{
				glTextureSubImage2D(m_OpenGL_ID, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
		}
	}

	void OpenGLTexture::init(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data)
	{
		//generate and bind the texture.
		glGenTextures(1, &m_OpenGL_ID);
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID);

		//tell it how to wrap, here is clamp to the edge.
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//min or magnify, just using linear filtering here.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//TO DO!!!
		//NEED: a channel == 1, especially for dealing with monochromatic bitmaps.

		if (channel == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (channel == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);

		//set the members of the class to the function variables of the same name.
		m_width = width;
		m_height = height;
		m_channel = channel;
	}
}