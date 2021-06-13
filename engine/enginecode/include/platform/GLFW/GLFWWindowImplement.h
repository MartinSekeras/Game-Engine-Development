/** \file GLFWWindowImplement.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWWindowImplement
	*	\brief Implemenation of a window using GLFW, inheriting from Window.
	*/
	class GLFWWindowImplement : public Window
	{
	public:
		GLFWWindowImplement(const WindowProperties& properties);		//!< constructor.
		virtual void initWindow(const WindowProperties& properties) override;	//!< func to initiate a window.
		virtual void closeWindow() override;					//!< func to close a window.
		//virtual ~Window() {};									//!< deconstructor
		virtual void onUpdate(float timestep) override;			//!< func to update the window with each timestep.
		virtual void onResize(WindowResizeEvent& e) override;	//!< Function to change viewport on resize
		virtual void setVSync(bool VSync) override;				//!< func to set the VSync to the refresh rate of monitor.
		virtual inline unsigned int getWidth() const override { return m_windowProperties.width; };		//!< func to get the width of the window.
		virtual inline unsigned int getHeight() const override { return m_windowProperties.height; };	//!< func to get the height of the window.
		virtual inline void* getNativeWindow() const override { return m_nativeWindow; };				//!< func to get the native window, ie the underlaying platform.
		virtual inline bool isFullScreenWindow() const override { return m_windowProperties.isFullScreen; };	//!< func to check whether the window is in fullscreen.
		virtual inline bool isVSync() const override { return m_windowProperties.isVSync; };			//!< func to check whether VSync-ed.
		virtual void setFullscreenMode(bool fullscreenState) override; //!< Enables full screen
	private:
		WindowProperties m_windowProperties;	//!< properties of window.
		GLFWwindow * m_nativeWindow;			//!< native GLFW window.
		float m_aspectRatio;					//!< aspect ratio.
		GLFWmonitor* m_monitor; //!< Monitor window is being rendered to
		glm::ivec2 m_nonFullscreenPos; //!< Position of window before fullscreen
		glm::ivec2 m_nonFullscreenSize; //!< Size of window before fullscreen
	};
}
