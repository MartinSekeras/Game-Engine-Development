/** \file OpenGLTexture.h */
#pragma once

#include "rendering/textures.h"

namespace Engine
{
	class OpenGLTexture : public Textures
	{
		/** \class OpenGLTexture
		*	\brief OpenGL specific class to take in image files for textures.
		*/
	public:
		OpenGLTexture(const char* filepath);	//!< constructor, takes the filepaths for texture.
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data);		//!< constructor; width, height and channel plus data in bytes (what unsigned char is).
		virtual ~OpenGLTexture();				//!< deconstructor.
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) override;	//!< edit the texture.
		 
		virtual inline uint32_t getID() override { return m_OpenGL_ID; }		//!< accessor to get openGL handle.
		virtual inline uint32_t getWidth() override { return m_width; }			//!< accessor to get the texture width.		
		virtual inline uint32_t getHeight() override { return m_height; }		//!< accessor to get the texture height.
		virtual inline uint32_t getChannel() override { return m_channel; }		//!< accessor to get the texture channel.
		virtual inline uint32_t getWidthF() override { return static_cast<float>(m_width); }		//!< accessor to get the floating point texture width.
		virtual inline uint32_t getHeightF() override { return static_cast<float>(m_height); }		//!< accessor to get the floating point texture height.

	private:
		void init(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data);		//!< an initate function to be used in both of the OpenGLTexture(...) functions, does the bulk of the work for both of these.
		uint32_t m_OpenGL_ID;	//!< OpenGL handle.
		uint32_t m_width;		//!< width of texture.
		uint32_t m_height;		//!< height of texture.
		uint32_t m_channel;		//!< channel of texture.
	};	
}