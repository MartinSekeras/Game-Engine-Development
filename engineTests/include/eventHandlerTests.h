#pragma once

#include <gtest/gtest.h>

#include "events/eventHandler.h"


class MockApplication
{
public:
	/*
	MockApplication()
	{
		m_handler.setOnWindowCloseCallback(std::bind(&MockApplication::onWindowClose, this, std::placeholders::_1));
	};		
	*/
	void setCallback()
	{
		m_handler.setOnWindowCloseCallback(std::bind(&MockApplication::onWindowClose, this, std::placeholders::_1));
	};

	Engine::EventHandler m_handler;
private:

	bool onWindowClose(Engine::WindowCloseEvent& event)
	{
		event.handleEvent(true);
		return event.isEventHandled();
	}
};