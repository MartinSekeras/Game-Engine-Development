/** \file userEvents.cpp */

#include "engine_pch.h"
#include "events/userEvents.h"

/*
void Engine::UserEvents::bindAllEventsTypes()
{

}
*/
/*
bool Engine::UserEvents::onWindowClose(WindowCloseEvent & event)
{
	return false;
}
*/

bool Engine::UserEvents::onWindowResize(WindowResizeEvent & event)
{
	event.handleEvent(true);
	//Log::info("Window Resized Event: ({0}, {1})", event.getWindowSize().x, event.getWindowSize().y);
	return event.isEventHandled();
}

bool Engine::UserEvents::onWindowMove(WindowMoveEvent & event)
{
	event.handleEvent(true);
	//Log::info("Window Move Event: ({0}, {1})", event.getWindowPosition().x, event.getWindowPosition().y);
	return event.isEventHandled();
}

bool Engine::UserEvents::onWindowFocus(WindowFocusEvent & event)
{
	event.handleEvent(true);
	//Log::info("Window Focus Event: {0}");
	return event.isEventHandled();
}

bool Engine::UserEvents::onWindowLostFocus(WindowLostFocusEvent & event)
{
	event.handleEvent(true);
	//Log::info("Window Lost Focus Event: {0}");
	return event.isEventHandled();
}

bool Engine::UserEvents::onKeyPressed(KeyPressedEvent & event)
{
	event.handleEvent(true);
	//Log::info("Key Pressed Event: key: {0}, repeat: {1}", event.getKeycode(), event.getRepeatCount());
	if (event.getKeycode() == NG_KEY_SPACE)
	{
		Log::error("SPACEBAR PRESSED");
	}
	return event.isEventHandled();
}

bool Engine::UserEvents::onKeyReleased(KeyReleasedEvent & event)
{
	event.handleEvent(true);
	//Log::info("Key Released Event: key: {0}", event.getKeycode());
	if (event.getKeycode() == NG_KEY_UP)
	{
		Log::error("UP RELEASED");
	}
	return event.isEventHandled();
}

/*
bool Engine::UserEvents::onKeyType(KeyTypedEvent & event)
{
	return false;
}
*/

bool Engine::UserEvents::onMouseMove(MouseMovementEvent & event)
{
	event.handleEvent(true);
	//Log::info("Mouse Move Event: ({0}, {1})", event.getMousePosition().x, event.getMousePosition().y);
	return event.isEventHandled();
}

bool Engine::UserEvents::onMouseButtonPress(MouseButtonPressEvent & event)
{
	event.handleEvent(true);
	//Log::info("Mouse Button Pressed Event: {0}", event.getButtonPressed());
	return event.isEventHandled();
}

bool Engine::UserEvents::onMouseButtonRelease(MouseButtonReleaseEvent & event)
{
	event.handleEvent(true);
	//Log::info("Mouse Button Released Event: {0}", event.getButtonReleased());
	return event.isEventHandled();
}

bool Engine::UserEvents::onMouseScroll(MouseScrollEvent & event)
{
	event.handleEvent(true);
	//Log::info("Mouse Scroll Event: ({0}, {1})", static_cast<float>(event.getXMouseScroll()), static_cast<float>(event.getYMouseScroll()));
	return event.isEventHandled();;
}

/*
bool Engine::UserEvents::fullscreenCheck()
{
	return false;
}
*/