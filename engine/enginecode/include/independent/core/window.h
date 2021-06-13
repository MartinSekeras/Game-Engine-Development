/** \file window.h */
#pragma once
#include "events/eventHandler.h"
#include "core/graphicsContext.h"

namespace Engine
{
	struct WindowProperties
	{
		const char * windowTitle;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;
		WindowProperties(char * title = "Window Numero Uno", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false)
			: windowTitle(title), width(width), height(height), isFullScreen(fullscreen) {}
	};

	/** \class Window
	*	\brief Abstract base class for all implemented windows, which will code to this interface.
	*/
	class Window
	{
	public:
		virtual void initWindow(const WindowProperties& properties) = 0;	//!< func to initiate a window.
		virtual void closeWindow() = 0;					//!< func to close a window.
		virtual ~Window() {};							//!< deconstructor
		virtual void onUpdate(float timestep) = 0;		//!< func to update the window with each timestep.
		virtual void onResize(WindowResizeEvent& e) = 0;
		virtual void setVSync(bool VSync) = 0;			//!< func to set the VSync to the refresh rate of monitor.
		virtual unsigned int getWidth() const = 0;		//!< func to get the width of the window.
		virtual unsigned int getHeight() const = 0;		//!< func to get the height of the window.
		virtual void* getNativeWindow() const = 0;		//!< func to get the native window, ie the underlaying platform.
		virtual bool isFullScreenWindow() const = 0;	//!< func to check whether the window is in fullscreen.
		virtual bool isVSync() const = 0;				//!< func to check whether VSync-ed.
		virtual void setFullscreenMode(bool fullscreenState)  = 0; //!< Func to set to full screen

		inline EventHandler& getEventHandler() { return m_eventHandler; };	//!< func to get an instance of the event handler.
		static Window* createWindow(const WindowProperties& properties = WindowProperties());		//!< constructor, create a window using the properties definied in WindowProperties.
	protected:
		EventHandler m_eventHandler;						//!< event handler. 
		std::shared_ptr<GraphicsContext> m_graphicsContext;	//!< shared pointer to the graphics context.
	};
}
