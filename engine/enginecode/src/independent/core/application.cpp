/** \file application.cpp */

#include "engine_pch.h"
#include "core/application.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/headerList.h"

#ifdef  NG_PLATFORM_WINDOWS
/*  #include "platform/windows/win32System.h"
	#include "platform/windows/winTimer.h"
	#else */
	#include "platform/GLFW/GLFWSystem.h"
#endif //  NG_PLATFORM_WINDOWS

namespace Engine {
	// setting the static vars
	VertexBufferLayout TPVertexNormalised::s_BufferLayout = {{ShaderDataType::Float3, { ShaderDataType::Short3, true }, { ShaderDataType::Short2, true }}, 24 };
	Application* Application::s_instance = nullptr;

	Application::Application(ApplicationProps appProps) 
	{
		if (s_instance == nullptr)
			s_instance = this;

		//start the systems.
		//starting with the log system.
		m_logSystem.reset(new Log);
		m_logSystem->start();
		
		//start the windows system.
#ifdef NG_PLATFORM_WINDOWS
		/* m_windowsSystem.reset(new Win32System);
		#else */
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		m_resourceManager.reset(new ResourceManager);
		m_resourceManager->start(SystemSignal::ResourceCount, appProps.shadersCapacity, appProps.texturesCapacity);
		//reset & start the timer.
		//if on a windows platform then make a windows timer, otherwise make a chrono timer.
		//NOTE - not a system! Don't need to stop it.
#ifdef  NG_PLATFORM_WINDOWS
		/* m_timer.reset(new WinTimer);
		#else */
		m_timer.reset(new ChronoTimer);
#endif //  NG_PLATFORM_WINDOWS
		m_timer->start();

		//modify the window a little.
		WindowProperties properties("IT'S AN ENGINE!", 800, 600, false);
		//create a default window.
		m_window.reset(Window::createWindow(appProps.winProps));

		//start the random number syste,
		m_ranNumSytem.reset(new RandomNumberGenerator);
		m_ranNumSytem->start();

		//calling function that binds all the callbacks for the event types.
		bindAllEventsTypes();

		//ImGuiHelper::init();//!< Start ImGui helper

		InputPoller::setNativeWindow(m_window->getNativeWindow());

		world = physCommon.createPhysicsWorld();
		m_timer->reset();
	}


#pragma region USER_EVENTS
	void Application::bindAllEventsTypes()
	{
		//window events.
		m_window->getEventHandler().setOnWindowCloseCallback(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowResizeCallback(std::bind(&Application::onWindowResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMoveCallback(std::bind(&Application::onWindowMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowFocusCallback(std::bind(&Application::onWindowFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowLostFocusCallback(std::bind(&Application::onWindowLostFocus, this, std::placeholders::_1));

		//key events.
		m_window->getEventHandler().setOnKeyPressCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleaseCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));

		//mouse events.
		m_window->getEventHandler().setOnMouseMoveCallback(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonPressCallback(std::bind(&Application::onMouseButtonPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonReleaseCallback(std::bind(&Application::onMouseButtonRelease, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseScrollCallback(std::bind(&Application::onMouseScroll, this, std::placeholders::_1));
	}

	bool Application::onWindowClose(WindowCloseEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Window Closed Event: {0}");
		m_running = false;
		return event.isEventHandled();
	}

	bool Application::onWindowResize(WindowResizeEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Window Resized Event: ({0}, {1})", event.getWindowSize().x, event.getWindowSize().y);
		return event.isEventHandled();
	}

	bool Application::onWindowMove(WindowMoveEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Window Move Event: ({0}, {1})", event.getWindowPosition().x, event.getWindowPosition().y);
		return event.isEventHandled();
	}

	bool Application::onWindowFocus(WindowFocusEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Window Focus Event: {0}");
		return event.isEventHandled();
	}

	bool Application::onWindowLostFocus(WindowLostFocusEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Window Lost Focus Event: {0}");
		return event.isEventHandled();
	}

	bool Application::onKeyPressed(KeyPressedEvent& event)
	{
		//event.handleEvent(true);
		//Log::info("Key Pressed Event: key: {0}, repeat: {1}", event.getKeycode(), event.getRepeatCount());
		/*if (event.getKeycode() == NG_KEY_SPACE)
		{
			Log::error("SPACEBAR PRESSED");
		}
		return event.isEventHandled();
		*/
		switch (event.getKeycode())
		{
		default:
			m_layerStack.onKeyPressed(event);
			event.handleEvent(true);
		}
		return event.isEventHandled();
	}

	bool Application::onKeyReleased(KeyReleasedEvent& event)
	{
		//event.handleEvent(true);
		//Log::info("Key Released Event: key: {0}", event.getKeycode());
		if (event.getKeycode() == NG_KEY_UP)
		{
			Log::error("UP RELEASED");
		}
		switch (event.getKeycode())
		{
		case NG_KEY_ESCAPE:
			m_running = false;
			event.handleEvent(true);
		case NG_KEY_F10:
			m_window->setFullscreenMode(!m_window->isFullScreenWindow());
			event.handleEvent(true);
			break;
		default:
			m_layerStack.onKeyReleased(event);
			event.handleEvent(true);
		}
		return event.isEventHandled();
	}

	bool Application::onMouseMove(MouseMovementEvent& event)
	{
		m_layerStack.onMouseMoved(event);
		event.handleEvent(true);
		//Log::info("Mouse Move Event: ({0}, {1})", event.getMousePosition().x, event.getMousePosition().y);
		return event.isEventHandled();
	}

	bool Application::onMouseButtonPress(MouseButtonPressEvent& event)
	{
		m_layerStack.onMousePressed(event);
		event.handleEvent(true);
		//Log::info("Mouse Button Pressed Event: {0}", event.getButtonPressed());
		return event.isEventHandled();
	}

	bool Application::onMouseButtonRelease(MouseButtonReleaseEvent& event)
	{
		m_layerStack.onMouseReleased(event);
		event.handleEvent(true);
		//Log::info("Mouse Button Released Event: {0}", event.getButtonReleased());
		return event.isEventHandled();
	}

	bool Application::onMouseScroll(MouseScrollEvent & event)
	{
		event.handleEvent(true);
		//Log::info("Mouse Scroll Event: ({0}, {1})", static_cast<float>(event.getXMouseScroll()), static_cast<float>(event.getYMouseScroll()));
		return event.isEventHandled();
	}
#pragma endregion

	Application::~Application()
	{
		//stop the systems in the REVERSE ORDER to how they start.
		m_ranNumSytem->stop();
		m_windowsSystem->stop();
		m_logSystem->stop();
		m_resourceManager->stop();
	}
	
	void Application::run()
	{
		//create a float for the time step and initialise at 0.
		float timeStep = 0.0f;
		while (m_running)
		{
			//update the time step with the timer function getElapsedTime()
			timeStep = m_timer->getElapsedTime();
			m_timer->reset();

			/*** DO STUFF IN THE FRAME... ***/
			m_layerStack.update(timeStep);
			m_layerStack.render();
			
			m_window->onUpdate(timeStep);
		}
	}

	void Application::restart()
	{

		m_running = false;
		m_running = true;
	}
}