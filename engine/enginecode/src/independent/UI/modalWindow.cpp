/* \file modalWindow.cpp */


#include "engine_pch.h"
#include "UI/modalWindow.h"
#include "UI/containers.h"


namespace Engine
{
	int32_t ModalWindow::padding = 6;


	ModalWindow::ModalWindow()
	{


		glm::ivec2 winSize = { Application::getInstance().getWindow()->getWidth(), Application::getInstance().getWindow()->getHeight() };
		m_position = (winSize / 2);
		m_size = (glm::ivec2(0.f));
		m_windowColourScheme = (UIColourScheme());
		m_colourScheme = &m_windowColourScheme;
		m_container = RootContainer(this);
		m_container.updatePosition(m_position + glm::ivec2(ModalWindow::padding, ModalWindow::padding));
	}


	void ModalWindow::onRender() const
	{
		if (m_active)
		{
			glm::ivec2 winSize = { Application::getInstance().getWindow()->getWidth(),Application::getInstance().getWindow()->getHeight() };
			glm::vec4 bgCover = m_windowColourScheme.background;
			bgCover.a = 0.5f;
			Renderer2D::submit(Quad::createCreateTopLeftSize({ 0.f,0.f }, winSize), bgCover);


			//Renderer2D::submit(Quad::createCreateTopLeftSize(m_position, m_size), m_windowColourScheme.background);
			Renderer2D::submit(Quad::createCreateTopLeftSize(m_position, m_size), m_windowColourScheme.background);

			m_container.onRender();


		}
	}


	void ModalWindow::addContainer(HorizontalContainer& container)
	{
		m_container.addContainer(container);
	}




	void ModalWindow::updateSize()
	{
		glm::ivec2 childSize = m_container.getSize();


		m_size.x = std::max(childSize.x + (padding * 2), m_size.x);
		m_size.y = std::max(childSize.y + (padding * 2), m_size.y);


		updatePosition(glm::ivec2(0));
		m_container.updatePosition(m_position);


	}


	void ModalWindow::updatePosition(glm::ivec2& relativePosition)
	{
		glm::ivec2 winSize = { Application::getInstance().getWindow()->getWidth(), Application::getInstance().getWindow()->getHeight() };
		auto screenCentre = (winSize / 2);
		m_position = screenCentre - glm::ivec2(m_size.x / 2, m_size.y / 2);
	}


	void ModalWindow::onMousePress(glm::ivec2& mousePosition, int32_t button)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& widget : hzContainer)
			{
				widget->onMousePress(mousePosition, button);
			}
		}
	}

	void ModalWindow::onMouseRelease(glm::ivec2& mousePosition, int32_t button)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& widget : hzContainer)
			{
				widget->onMouseRelease(mousePosition, button);
			}
		}
	}

	void ModalWindow::onMouseMove(glm::ivec2& mousePosition)
	{
		for (auto& hzContainer : m_container)
		{
			for (auto& widget : hzContainer)
			{
				widget->onMouseMove(mousePosition);
			}
		}
	}






}