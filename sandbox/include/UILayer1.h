/* UILayer.h */
//Brief a layer which holds in game menus

// TOOL
#pragma once


#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <events/eventHeaders.h>
#include <core/application.h>

#include "sceneLayer.h"
using namespace Engine;
enum class UILayerState { InActive, Activating, Active, Deactivating };


class UILayer : public Layer
{
public:
	UILayer(const char* name, SceneLayer& scene);
	void onRender() override;
	UILayerState getState() { return m_state; }
	void onUpdate(float time) override;
	
	virtual void onKeyPressed(KeyPressedEvent& e) override;
	virtual void onMouseMove(MouseMovementEvent& e) override;
	virtual void onMousePress(MouseButtonPressEvent& e) override;
	virtual void onMouseRelease(MouseButtonReleaseEvent& e) override;
	std::shared_ptr<Application> m_app;
	void closeMenu();
	bool paused = false; //!<Whether game is paused
	bool quit;//!< Whether game should be closed
	bool winner = false; //!<Whether game has been won
	//bool mainMenu = true;
	int score;//!<Current score
	float timeRemaining = 100;//!<Time left in the game
	bool gameOver = false;//!<Has user lost?
	float startingTime = 100;//!<Time that is remaining on start
	float startingTimeChanged = 100;//!< This allows slider to change the time



private:
	std::shared_ptr<FreeOthroCamController> m_camera;
	SceneWideUniforms m_swu;
	//ModalWindow m_mainMenu;
	//All the windows
	ModalWindow m_window;
	ModalWindow m_loserWindow;
	ModalWindow m_winWindow;
	UILayerState m_state = UILayerState::InActive;
	std::vector<Quad> m_quads;
	SceneLayer& m_scene;
	
};