/** \file eventHandler.h */
#pragma once

#include "events.h"
#include "eventHeaders.h"
#include <functional>

namespace Engine
{
	/* \class EventHander
	*  \brief Class to handling all incoming events for Windows, plus Key and Mouse user interaction.
	*/
	class EventHandler
	{
	public:
		void setOnWindowCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onWindowCloseCallback = fn; }		//!< window close accessor func - pass it bound function and it sets it.
		void setOnWindowResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onWindowResizeCallback = fn; }	//!< window resize accessor func - pass it bound function and it sets it.
		void setOnWindowFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onWindowFocusCallback = fn; }		//!< window focus accessor func - pass it bound function and it sets it.
		void setOnWindowLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onWindowLostFocusCallback = fn; }	//!< window lost focus accessor func - pass it bound function and it sets it.
		void setOnWindowMoveCallback(const std::function<bool(WindowMoveEvent&)>& fn) { m_onWindowMoveCallback = fn; }			//!< window move accessor func - pass it bound function and it sets it.
		std::function<bool(WindowCloseEvent&)>& getOnWindowCloseCallback() { return m_onWindowCloseCallback; }					//!< window close accessor func - passes a reference to bound function.
		std::function<bool(WindowResizeEvent&)>& getOnWindowResizeCallback() { return m_onWindowResizeCallback; }				//!< window resize accessor func - passes a reference to bound function.
		std::function<bool(WindowFocusEvent&)>& getOnWindowFocusCallback() { return m_onWindowFocusCallback; }					//!< window focus accessor func - passes a reference to bound function.
		std::function<bool(WindowLostFocusEvent&)>& getOnWindowLostFocusCallback() { return m_onWindowLostFocusCallback; }		//!< window lost focus accessor func - passes a reference to bound function.
		std::function<bool(WindowMoveEvent&)>& getOnWindowMoveCallback() { return m_onWindowMoveCallback; }						//!< window move accessor func - passes a reference to bound function.

		void setOnKeyPressCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressCallback = fn; }		//!< key press accessor func - pass it bound function and it sets it.
		void setOnKeyReleaseCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleaseCallback = fn; }	//!< key release accessor func - pass it bound function and it sets it.
		void setOnKeyTypeCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypeCallback = fn; }			//!< key type accessor func - pass it bound function and it sets it.
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressCallback() { return m_onKeyPressCallback; }					//!< key press accessor func - passes a reference to bound function.
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleaseCallback() { return m_onKeyReleaseCallback; }			//!< key release accessor func - passes a reference to bound function.
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypeCallback() { return m_onKeyTypeCallback; }						//!< key type accessor func - passes a reference to bound function.

		void setOnMouseMoveCallback(const std::function<bool(MouseMovementEvent&)>& fn) { m_onMouseMoveCallback = fn; }				//!< mouse move accessor func - pass it bound function and it sets it.
		void setOnMouseScrollCallback(const std::function<bool(MouseScrollEvent&)>& fn) { m_onMouseScrollCallback = fn; }			//!< mouse scrolled accessor func - pass it bound function and it sets it.
		void setOnMouseButtonPressCallback(const std::function<bool(MouseButtonPressEvent&)>& fn) { m_onMouseButtonPressCallback = fn; }		//!< mouse button press accessor func - pass it bound function and it sets it.
		void setOnMouseButtonReleaseCallback(const std::function<bool(MouseButtonReleaseEvent&)>& fn) { m_onMouseButtonReleaseCallback = fn; }	//!< mouse button release accessor func - pass it bound function and it sets it.
		std::function<bool(MouseMovementEvent&)>& getOnMouseMoveCallback() { return m_onMouseMoveCallback; }						//!< mouse move accessor func - passes a reference to bound function.
		std::function<bool(MouseScrollEvent&)>& getOnMouseScrollCallback() { return m_onMouseScrollCallback; }						//!< mouse scrolled accessor func - passes a reference to bound function.
		std::function<bool(MouseButtonPressEvent&)>& getOnMouseButtonPressCallback() { return m_onMouseButtonPressCallback; }		//!< mouse button press accessor func - passes a reference to bound function.
		std::function<bool(MouseButtonReleaseEvent&)>& getOnMouseButtonReleaseCallback() { return m_onMouseButtonReleaseCallback; }	//!< mouse button release accessor func - passes a reference to bound function.

	private:
		bool defaultOnWindowClose(WindowCloseEvent& event) { return false; }			//!< default for Window Close, returns false as default and says hasn't handled it.
		bool defaultOnWindowResize(WindowResizeEvent& event) { return false; }			//!< default for Window Resize, returns false.
		bool defaultOnWindowFocus(WindowFocusEvent& event) { return false; }			//!< default for Window Focus, returns false.
		bool defaultOnWindowLostFocus(WindowLostFocusEvent& event) { return false; }	//!< default for Window Lost Focus, returns false.
		bool defaultOnWindowMove(WindowMoveEvent& event) { return false; }				//!< default for Window Move, returns false.
		std::function<bool(WindowCloseEvent&)> m_onWindowCloseCallback = std::bind(&EventHandler::defaultOnWindowClose, this, std::placeholders::_1);		//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(WindowResizeEvent&)> m_onWindowResizeCallback = std::bind(&EventHandler::defaultOnWindowResize, this, std::placeholders::_1);	//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(WindowFocusEvent&)> m_onWindowFocusCallback = std::bind(&EventHandler::defaultOnWindowFocus, this, std::placeholders::_1);		//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(WindowLostFocusEvent&)> m_onWindowLostFocusCallback = std::bind(&EventHandler::defaultOnWindowLostFocus, this, std::placeholders::_1);	//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(WindowMoveEvent&)> m_onWindowMoveCallback = std::bind(&EventHandler::defaultOnWindowMove, this, std::placeholders::_1);			//!< binding function to this instance, wrapped with 1 param passed.

		bool defaultOnKeyPress(KeyPressedEvent& event) { return false; }		//!< default for Key Pressed, returns false.
		bool dafaultOnKeyRelease(KeyReleasedEvent& event) { return false; }		//!< default for Key Released, returns false.
		bool defaultOnKeyType(KeyTypedEvent& event) { return false; }			//!< default for Key Typed, returns false.
		std::function<bool(KeyPressedEvent&)> m_onKeyPressCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);		//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleaseCallback = std::bind(&EventHandler::dafaultOnKeyRelease, this, std::placeholders::_1);	//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(KeyTypedEvent&)> m_onKeyTypeCallback = std::bind(&EventHandler::defaultOnKeyType, this, std::placeholders::_1);			//!< binding function to this instance, wrapped with 1 param passed.

		bool defaultOnMouseMove(MouseMovementEvent& event) { return false; }				//!< default for Mouse Movement, returns false.
		bool defaultOnMouseScroll(MouseScrollEvent& event) { return false; }				//!< default for Mouse Scroll, returns false.
		bool defaultOnMouseButtonPress(MouseButtonPressEvent& event) { return false; }		//!< default for Mouse Button Pressed, returns false.
		bool defaultOnMouseButtonRelease(MouseButtonReleaseEvent& event) { return false; }	//!< default for Mouse Button Released, returns false.
		std::function<bool(MouseMovementEvent&)> m_onMouseMoveCallback = std::bind(&EventHandler::defaultOnMouseMove, this, std::placeholders::_1);		//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(MouseScrollEvent&)> m_onMouseScrollCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1);	//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(MouseButtonPressEvent&)> m_onMouseButtonPressCallback = std::bind(&EventHandler::defaultOnMouseButtonPress, this, std::placeholders::_1);		//!< binding function to this instance, wrapped with 1 param passed.
		std::function<bool(MouseButtonReleaseEvent&)> m_onMouseButtonReleaseCallback = std::bind(&EventHandler::defaultOnMouseButtonRelease, this, std::placeholders::_1);	//!< binding function to this instance, wrapped with 1 param passed.
	};
}