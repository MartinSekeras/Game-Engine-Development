/* \file inputPoller.h */
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	/* \class InputPoller
	*  \brief API agnostic input poller to get current mouse and/or keyboard state.
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keycode);			//!< is key pressed?
		static bool isMouseButtonPressed(int32_t button);	//!< is mouse button pressed?
		static glm::vec2 getMousePosition();				//!< get current mouse position.
		static void setNativeWindow(void* nativeWin);		//!< set the native window.
		inline static float getMouseXPos() { return getMousePosition().x; }		//!< get the x of the mouse position.
		inline static float getMouseYPos() { return getMousePosition().y; }		//!< get the y of the mouse position.
	private:

	};
}
