/** \file application.h */
#pragma once

#include "systems/log.h"
#include "systems/randomNumberGenerator.h"
#include "events/eventHeaders.h"

#include "core/window.h"
#include "core/timer.h"
#include "core/inputPoller.h"
#include "core/layerStack1.h"
#include "UI/widget.h"
#include "UI/containers.h"
#include "UI/modalWindow.h"
#include "systems/resourceManager.h"
#include <entt/entt.hpp>
#include <reactphysics3d/reactphysics3d.h>

namespace Engine {

	struct ApplicationProps
	{
		WindowProperties winProps;
		uint32_t vertexCapacity3D = 4000;
		uint32_t indexCapacity3D = 1000;
		uint32_t batchSize3D = 4000;
		uint32_t batchSize2D = 8192;
		const char* fontFilePath = "./assets/fonts/arial.ttf";
		uint32_t characterSize = 86;
		uint32_t shadersCapacity = 40;
		uint32_t texturesCapacity = 30;

	};

	/** \class Application
		\brief Fundemental class of the engine. A singleton which runs the game loop infinitely.
	*/
	class Application
	{
	protected:
		Application(ApplicationProps props);	//!< Constructor
		std::shared_ptr<Log> m_logSystem;						//!< the log system.
		std::shared_ptr<RandomNumberGenerator> m_ranNumSytem;	//!< the random number generator system.
		std::shared_ptr<System> m_windowsSystem;				//!< the windows system.
													
		/* ***NOTE*** - IF MORE THAN ONE WINDOW. Should have a list or vector containing all windows.
		* THEN - the below m_window would become m_CURRENTwindow
		* THEN - lost or gain focus events would be set to whatever current window is.
		* MORE BELOW on the getWindow() function.
		*/
		std::shared_ptr<Window> m_window;				//!< the windows.
		std::shared_ptr<ITimer> m_timer;				//!< the timer.
		LayerStack m_layerStack;		//!< The layer stack
		std::shared_ptr<ResourceManager> m_resourceManager; //!< The resource manager
		//std::shared_ptr<RigidBodyComponent> world;

		void bindAllEventsTypes();						//!< func to keep all the bindings of event types together.

		bool onWindowClose(WindowCloseEvent& event);	//!< run when the window closes.
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
		static Application* s_instance;					//!< Singleton instance of the application

	public:

		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; }	//!< Instance getter from singleton pattern
		/* ***NOTE*** TODO : if more than one window at a time possible. Must change below function to getCURRENTWindow()
		* THAT then returns to new var m_CURRENTwindow.
		*/
		bool m_running = true;							//!< Is the application running?

		inline std::shared_ptr<ResourceManager> getResourceManager(){return m_resourceManager; }
		//inline std::shared_ptr<RigidBodyComponent> getWorld() { return world; }
		inline std::shared_ptr<Window> getWindow() { return m_window; }		//!< gets and returns our window from instance.
		inline LayerStack getLayerStack() { return m_layerStack; }
		void run();				//!< Main loop

		void restart();
		entt::registry m_registry;
		std::vector<entt::entity> m_entities;

		rp3d::PhysicsWorld* world;
		rp3d::PhysicsCommon physCommon;

		float sliderValue = 100;
	};
	// To be defined in users code
	Application* startApplication();		//!< Function definition which provides an entry hook
}