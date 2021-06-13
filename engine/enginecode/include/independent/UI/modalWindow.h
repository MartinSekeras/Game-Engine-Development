/* \file modalWindow.h */
//brief a window which holds the UI
#pragma once


#include "renderer/renderer2D.h"
#include "core/application.h"
#include "UI/UIComponent.h"
#include "UI/containers.h"


namespace Engine
{
	class ModalWindow : public UIComponent
	{
	public:
		ModalWindow(); //!< Default constructor


		UIColourScheme m_windowColourScheme; //!<Colour scheme of the window
		void show() { m_active = true; }//!< Show the window
		void hide() { m_active = false; }//!< Hide the window
		void onRender() const override;//!< Render window
		void addContainer(HorizontalContainer& container);//!< Add a container to hold widgets
		virtual void updateSize() override;//!< Update size of window 
		virtual void updatePosition(glm::ivec2& relativePosition) override;//!< Update window position


		virtual void onMousePress(glm::ivec2& mousePosition, int32_t button) override;//!<Process mouse press
		virtual void onMouseRelease(glm::ivec2& mousePosition, int32_t button) override;//!<Process mouse release
		virtual void onMouseMove(glm::ivec2& mousePosition) override;//!<Process mouse movement


		bool isShown() { return m_active; }//!<Whether window is displayed


		static int32_t padding;//!< Spacing between widgets


	private:
		bool m_active = false;
		RootContainer m_container;
	};
}