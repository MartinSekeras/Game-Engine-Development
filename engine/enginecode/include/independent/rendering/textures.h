/** \file textures.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>


namespace Engine
{
	/** \class Textures
	*	\brief A class for an API agnostic textures.
	*/
	class Textures
	{
	public:
		virtual ~Textures() = default;					//!< deconstructor.
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) = 0;	//!< edit the texture 

		virtual inline uint32_t getID() = 0;			//!< accessor to get openGL handle.
		virtual inline uint32_t getWidth() = 0;			//!< accessor to get the texture width.		
		virtual inline uint32_t getHeight() = 0;		//!< accessor to get the texture height.
		virtual inline uint32_t getChannel() = 0;		//!< accessor to get the texture channel.
		virtual inline uint32_t getWidthF() = 0;			//!< accessor to get the floating point texture width.
		virtual inline uint32_t getHeightF() = 0;			//!< accessor to get the floating point texture height.

		static Textures* create(const char* filepath);	//!< constructor, takes the filepaths for texture; declared renderAPI.cpp.
		static Textures* create(uint32_t width, uint32_t height, uint32_t channel, unsigned char * data);	//!< constructor; width, height and channel plus data in bytes (what unsigned char is); declared renderAPI.cpp.

	private:

	};
}
