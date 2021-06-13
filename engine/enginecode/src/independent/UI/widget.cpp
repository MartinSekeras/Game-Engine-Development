/* \file widget.cpp */

#include "engine_pch.h"
#include "UI/widget.h"
#include "UI/containers.h"
#include "UI/modalWindow.h"


namespace Engine
{
	void Widget::updatePosition(glm::ivec2& relativePosition)
	{
		m_position = relativePosition;
	}

	void Widget::updateSize()
	{
		//Update parent
		m_parent->updateSize();
	}

	Spacer::Spacer(glm::ivec2 size)
	{
		m_size = size;
		m_position = { 0,0 };
	}

	Spacer::Spacer(int32_t sizeX, int32_t sizeY)
	{
		m_size = glm::ivec2(sizeX, sizeY);
		m_position = { 0,0 };
	}

	void Spacer::onRender() const
	{
		Renderer2D::submit(Quad::createCreateTopLeftSize(m_position, m_size), m_colourScheme->background);
	}

	Label::Label(glm::ivec2 size, const char* labelText) : m_text(labelText)
	{
		m_size = size;
		m_position = { 0,0 };
	}

	Label::Label(int32_t sizeX, int32_t sizeY, const char* labelText) : m_text(labelText)
	{
		m_size = glm::ivec2(sizeX, sizeY);
		m_position = { 0,0 };
		m_textPosition = { 0,0 };
	}

	void Label::onRender() const
	{
		Renderer2D::submit(Quad::createCreateTopLeftSize(m_position, m_size),m_colourScheme->background);
		Renderer2D::submit(m_text, m_textPosition, m_colourScheme->foreground);
	}

	void Label::updatePosition(glm::ivec2& relativePosition)
	{
		m_position = relativePosition;
		glm::ivec2 textsize = Renderer2D::getTextSize(m_text);
		glm::ivec2 centre = m_position + m_size / 2;
		m_textPosition.x = centre.x - textsize.x / 2;
		m_textPosition.y = centre.y + textsize.y / 2;
	}

	void Button::onRender() const
	{
		Renderer2D::submit(Quad::createCreateTopLeftSize(m_position, m_size), m_colourScheme->highlight);
		Renderer2D::submit(m_text, m_textPosition, glm::vec4(1.f));
	}

	void Button::onMousePress(glm::ivec2& mousePosition, int32_t button)
	{
		if (button == NG_MOUSE_BUTTON_1)
		{
			// Straight forward SAT test
			bool clickedOn =
				m_position.x <= mousePosition.x && mousePosition.x <= m_position.x + m_size.x &&
				m_position.y <= mousePosition.y && mousePosition.y <= m_position.y + m_size.y;

			if (clickedOn) 
				m_callback();
		}
	}

	Slider::Slider(int32_t width, float low, float high, const char* lowText, const char* highText, const char* middleText) :
		m_lowText(lowText),
		m_upperText(highText),
		m_middleText(middleText),
		m_lowerBound(low),
		m_upperBound(high),
		m_sliderWidth(width)
	{
		m_currentValue = (m_lowerBound + m_upperBound) / 2;
		sprintf_s(m_valueText, 12, "%.2f", m_currentValue);

		auto lowTextSize = Renderer2D::getTextSize(m_lowText);
		auto highTextSize = Renderer2D::getTextSize(m_upperText);
		auto middleTextSize = Renderer2D::getTextSize(m_middleText);
		auto valueTextSize = Renderer2D::getTextSize(m_valueText);

		m_size.x = lowTextSize.x / 2 + m_sliderWidth + highTextSize.x / 2;

		m_size.y = valueTextSize.x + ModalWindow::padding + m_sliderHeight / 2 + ModalWindow::padding + std::max(lowTextSize.y, highTextSize.y);
	}

	void Slider::updatePosition(glm::ivec2& relativePosition)
	{
		m_relativePosition = relativePosition;
		auto valueTextSize = Renderer2D::getTextSize(m_valueText);
		auto lowTextSize = Renderer2D::getTextSize(m_lowText);
		auto highTextSize = Renderer2D::getTextSize(m_upperText);
		auto middleTextSize = Renderer2D::getTextSize(m_middleText);

		int32_t lerpPos = (m_upperBound - m_currentValue) / (m_upperBound - m_lowerBound) * m_sliderWidth;
		m_grabPosition.x = lowTextSize.x / 2 + lerpPos - m_sliderHeight / 4;
		m_grabPosition.y = valueTextSize.y + ModalWindow::padding;
		m_grabPosition += relativePosition;

		m_grabTextPosition.x = m_grabPosition.x - (valueTextSize.x / 2);
		m_grabTextPosition.y = relativePosition.y;

		m_sliderPosition.x = lowTextSize.x / 2;
		m_sliderPosition.y = valueTextSize.y + ModalWindow::padding + m_sliderHeight / 2;
		m_sliderPosition += relativePosition;

		m_lowTextPosition.x = relativePosition.x;
		m_lowTextPosition.y = m_sliderPosition.y + ModalWindow::padding + std::max(lowTextSize.y, highTextSize.y) + m_sliderHeight;

		m_upperTextPosition.x = m_sliderPosition.x + m_sliderWidth - highTextSize.x / 2;
		m_upperTextPosition.y = m_sliderPosition.y + ModalWindow::padding + std::max(lowTextSize.y, highTextSize.y) + m_sliderHeight;		
		
		int diff = (m_upperTextPosition.x - m_lowTextPosition.x) / 2; 
		diff = diff - 60;
		m_middleTextPosition.x = m_lowTextPosition.x + diff;
		m_middleTextPosition.y = m_sliderPosition.y + ModalWindow::padding + std::max(lowTextSize.y, highTextSize.y) + m_sliderHeight;
	}

	void Slider::onRender() const
	{
		//Check these
		Renderer2D::submit(Quad::createCreateTopLeftSize(m_sliderPosition, glm::vec2(m_sliderWidth, m_sliderHeight)), m_colourScheme->highlight);
		Renderer2D::submit(Quad::createCreateTopLeftSize(m_grabPosition, glm::vec2(m_sliderHeight / 2, m_sliderHeight * 2)), m_colourScheme->foreground);

		Renderer2D::submit(m_lowText, m_lowTextPosition, m_colourScheme->foreground);
		Renderer2D::submit(m_upperText, m_upperTextPosition, m_colourScheme->foreground);
		Renderer2D::submit(m_middleText, m_middleTextPosition, m_colourScheme->foreground);
		Renderer2D::submit(m_valueText, m_grabTextPosition, m_colourScheme->foreground);
	}

	void Slider::onMouseMove(glm::ivec2& mousePosition)
	{
		if (m_grabActive)
		{
			m_grabPosition.x = std::min(std::max(m_sliderPosition.x, mousePosition.x), m_sliderPosition.x + (int32_t)m_sliderWidth);
			float t = (float)(m_grabPosition.x - m_sliderPosition.x) / m_sliderWidth;
			m_currentValue = m_lowerBound + t * (m_upperBound - m_lowerBound);
			sprintf_s(m_valueText, 128, "%.2f", m_currentValue);
			auto valueTextSize = Renderer2D::getTextSize(m_valueText);
			m_grabTextPosition.x = m_grabPosition.x - (valueTextSize.x / 2);
			if (m_middleText == "Difficulty")
			{ }
			else
			{
				Application::getInstance().sliderValue = m_currentValue;
				Log::info(Application::getInstance().sliderValue);

			}
		}
	}

	void Slider::onMousePress(glm::ivec2& mousePosition, int32_t button)
	{
		if (button == NG_MOUSE_BUTTON_1)
		{
			m_grabActive =
				m_grabPosition.x <= mousePosition.x && mousePosition.x <= m_grabPosition.x + m_sliderHeight / 2 &&
				m_grabPosition.y <= mousePosition.y && mousePosition.y <= m_grabPosition.y + m_sliderHeight * 2;
		}
	}

	void Slider::onMouseRelease(glm::ivec2& mousePosition, int32_t button)
	{
		m_grabActive = false;
	}

}