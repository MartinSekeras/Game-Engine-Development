/** \file subTexture.cpp */

#include "engine_pch.h"
#include "rendering/subTexture.h"

namespace Engine
{

	SubTexture::SubTexture(const std::shared_ptr<OpenGLTexture>& texture, const glm::vec2 & UVStart, const glm::vec2 & UVEnd) : 
		m_texture(texture),
		m_UVStart(UVStart),
		m_UVEnd(UVEnd)
	{
		//first calcuate the size of the x & y, minus start from end and then times by size of the texture to get the pixel size.
		//size is an int so static_casting to an int.
		m_size.x = static_cast<int>(m_UVEnd.x - m_UVStart.x) * m_texture->getWidthF();
		m_size.y = static_cast<int>(m_UVEnd.x - m_UVStart.x) * m_texture->getHeightF();

	}

	float SubTexture::transformU(float U)
	{
		//get the UVWidth
		m_UVWidth = m_UVEnd.x - m_UVStart.x;
		//take start add width and times by U.
		return m_UVStart.x + (m_UVWidth * U);
	}

	float SubTexture::transformV(float V)
	{
		//get the UVHeight
		m_UVHeight = m_UVEnd.y - m_UVStart.y;
		//take start add height and times by V.
		return m_UVStart.y + (m_UVHeight * V);
	}

	glm::vec2 SubTexture::transformUV(glm::vec2 UV)
	{
		return m_UVStart + ((m_UVEnd - m_UVStart) * UV);
	}
}