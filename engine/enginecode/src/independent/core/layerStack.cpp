/* \file layerStack.cpp */


#include "engine_pch.h"
#include "core/layerStack1.h"


namespace Engine
{
	LayerStack::~LayerStack()
	{
		for (uint32_t i = m_stack.size(); i > 0; i--)pop();
	}

	void LayerStack::push(Layer* layer)
	{
		layer->onAttach();
		std::shared_ptr<Layer> tmp(layer);
		m_stack.push_back(tmp);
	}

	void LayerStack::pop()
	{
		m_stack.back()->onDetach();
		m_stack.pop_back();
	}

	void LayerStack::update(float timestep)
	{
		for (auto& layer : m_stack) 
		{ 
			if (layer->isActive())layer->onUpdate(timestep); 
		}
	}

	void LayerStack::render()
	{
		for (auto& layer : m_stack) if (layer->isDisplayed())layer->onRender();
	}

	void LayerStack::onKeyPressed(KeyPressedEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isEventHandled()) layer->onKeyPressed(e);
	}

	void LayerStack::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handleEvent(false);
	}

	void LayerStack::onMousePressed(MouseButtonPressEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isEventHandled()) layer->onMousePress(e);
	}

	void LayerStack::onMouseReleased(MouseButtonReleaseEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isEventHandled()) layer->onMouseRelease(e);
	}

	void LayerStack::onMouseWheel(MouseScrollEvent& e)
	{
		e.handleEvent(false);
	}

	void LayerStack::onMouseMoved(MouseMovementEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isEventHandled()) layer->onMouseMove(e);
	}


	void LayerStack::setActive(const char* layerName, bool activeState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setActive(activeState);
		}
	}

	void LayerStack::setDisplayed(const char* layerName, bool displayState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setDisplayed(displayState);
		}
	}

	void LayerStack::setFocused(const char* layerName, bool focusedState)
	{
		for (auto& layer : m_stack)
		{
			if (layer->getName() == layerName) layer->setFocused(focusedState);
		}
	}
}