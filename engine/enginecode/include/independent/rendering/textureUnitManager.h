/** \file textureUnitManager.h */
#pragma once
#include <vector>

namespace Engine
{
	/*	\class TextureUnitManager
	*	\brief Class to act like a ring buffer to check, bind and store textures.
	*/
	class TextureUnitManager
	{
	public:
		TextureUnitManager() {};								//!< default constructor.
		TextureUnitManager(uint32_t capacity) : 
			m_capacity(capacity),
			m_buffer(capacity, 0xFFFFFFFF)
		{}														//!< constructor taking the capacity of the ring buffer.
		~TextureUnitManager() {};								//!< destructor.
		inline bool isFull() { return m_capacityFull; };		//!< accessor for whether ring buffer is full.
		void clear();											//!< clear the ring buffer.
		bool getUnit(uint32_t textureID, uint32_t& textureUnit);//!< returns whether the texture needs to be binded to the unit; false=do not need to bind, true=we do need to bind. Texture unit always set to unit.
	private:
		uint32_t m_capacity;				//!< capacity for the ring buffer.
		std::vector<uint32_t> m_buffer;		//!< internal space within ring buffer.
		bool m_capacityFull = false;		//!< bool for whether ring buffer has reached full capacity, initialised to false.
		uint32_t m_head = 0;				//!< head (front) of ring buffer.
		uint32_t m_tail = 0;				//!< tail (end) of ring buffer.
	};
}