/** \file textUnitManager.cpp */
#include "engine_pch.h"
#include "rendering/textureUnitManager.h"

namespace Engine
{
	void TextureUnitManager::clear()
	{
		m_head = 0;
		m_tail = 0;
		m_capacityFull = false;
		std::fill(m_buffer.begin(), m_buffer.end(), 0xFFFFFFFF);
	}

	bool TextureUnitManager::getUnit(uint32_t textureID, uint32_t & textureUnit)
	{
		//is texture already bound?
		for (int i = m_tail; i < m_head; i++)
		{
			//check at i in the buffer if that element is equal to texture ID.
			if (m_buffer.at(i) == textureID)
			{
				//it is, so set texture unit to i as that's where it is in the buffer.
				textureUnit = i;
				//it's here, doesn't need to bound, so return false.
				return false;
			}
		}

		//from here texture unit is not bound, have to bind it.
		//first off, is there space?
		if (m_capacityFull == true)
		{
			//it is full, no space, so clear it.
			clear();
		}
		//position at the head of the buffer, if cleared is 0, otherwise next thing to be filled.
		m_buffer.at(m_head) = textureID;				//putting the texture ID into the ring buffer.
		textureUnit = m_head;							//texture unit will be same place as just added ID, so need to store it.
		
		//increment head and mod by the capacity.
		m_head = (++m_head) % m_capacity;				
		
		//then check and update whether buffer is full.
		if (m_head == m_tail)
		{
			m_capacityFull = true;
		}

		return true;
	}
}