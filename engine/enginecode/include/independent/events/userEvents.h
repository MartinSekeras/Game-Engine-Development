/** \file userEvents.h */
#pragma once

#include "events/eventHeaders.h"
#include "systems/log.h"

namespace Engine
{
	/** \class UserEvents
	*	\brief Class to take the list of possible user events.
	*/
	class UserEvents
	{
	public:
		//void bindAllEventsTypes();						//!< func to keep all the bindings of event types together.

		//bool onWindowClose(WindowCloseEvent& event);	//!< run when the window closes.
		bool onWindowResize(WindowResizeEvent& event);	//!< run when the window resized.
		bool onWindowMove(WindowMoveEvent& event);		//!< on window move.
		bool onWindowFocus(WindowFocusEvent& event);	//!< on window focus.
		bool onWindowLostFocus(WindowLostFocusEvent& event);	//!< on window lost focus.

		bool onKeyPressed(KeyPressedEvent& event);		//!< on key press.
		bool onKeyReleased(KeyReleasedEvent& event);	//!< on key release.
		//bool onKeyType(KeyTypedEvent& event);			//!< on key type.

		bool onMouseMove(MouseMovementEvent& event);				//!< on mouse movement.
		bool onMouseButtonPress(MouseButtonPressEvent& event);		//!< on mouse button press.
		bool onMouseButtonRelease(MouseButtonReleaseEvent& event);	//!< on mouse button release.
		bool onMouseScroll(MouseScrollEvent& event);				//!< on mouse scrolling.
		//bool fullscreenCheck();						//!< to check whether in fullscreen mode of current display monitor.

	private:


	};
}
