/* \file layer.h */
#pragma once

#include <string>
#include "core/window.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(const char* name) : m_name(name) {}; //!< Constructor

		virtual void onAttach() {}; //!< Runs when layer is attached
		virtual void onDetach() {}; //!< Runs when layer is detached
		virtual void onRender() {}; //!< Runs when layer is rendered
		virtual void onUpdate(float timestep) {}; //!< Runs every frame
		virtual void onResize(WindowResizeEvent& e) {}; //!< Runs when window is resized

		inline const char* getName() const { return m_name; }
		inline void setDisplayed(bool displayStatus) { m_isDisplayed = displayStatus; }
		inline void setActive(bool activeStatus) { m_isActive = activeStatus; }
		inline void setFocused(bool focusedStatus) { m_isFocused = focusedStatus; }
		inline const bool isDisplayed() const { return m_isDisplayed; }
		inline const bool isActive() const { return m_isActive; }
		inline const bool isFocused() const { return m_isFocused; }

		virtual void onKeyPressed(KeyPressedEvent& e) { e.handleEvent(false); }//!<On key press event
		virtual void onMouseMove(MouseMovementEvent& e) { e.handleEvent(false); }//!<On mouse move event
		virtual void onMousePress(MouseButtonPressEvent& e) { e.handleEvent(false); }//!<On mouse press event
		virtual void onMouseRelease(MouseButtonReleaseEvent& e) { e.handleEvent(false); }//!<On mouse release event

		
	protected:
		const char* m_name; //!< Name used for debugging
		bool m_isDisplayed = true; //!< Should layer be rendered
		bool m_isActive = true; //!< Should layer be updated
		bool m_isFocused = true; //!< Should layer be getting events
		bool m_quitGame = false; //!< Should game be quit
	};
}



