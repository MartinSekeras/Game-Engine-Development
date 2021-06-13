/* mainMenu.h */
//Brief a class for the main menu layer

// TOOL
#pragma once


#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <events/eventHeaders.h>
#include <core/application.h>

#include "sceneLayer.h"
#include "levelEditor.h"
using namespace Engine;
enum class MenuLayerState { InActive, Activating, Active, Deactivating };


class MainMenu : public Layer
{
public:
	//Repeated across all layers
	MainMenu(const char* name, SceneLayer& scene, LevelEditor& editor);
	void onRender() override;
	MenuLayerState getState() { return m_state; }
	void onUpdate(float time) override;

	virtual void onKeyPressed(KeyPressedEvent& e) override;
	virtual void onMouseMove(MouseMovementEvent& e) override;
	virtual void onMousePress(MouseButtonPressEvent& e) override;
	virtual void onMouseRelease(MouseButtonReleaseEvent& e) override;
	std::shared_ptr<Application> m_app; //!< A pointer to the application 
	void closeMenu();
	bool paused = false; //Whether the game is paused



private:
	std::shared_ptr<FreeOthroCamController> m_camera;
	SceneWideUniforms m_swu;
	//ModalWindow m_mainMenu;

	ModalWindow m_window;
	MenuLayerState m_state = MenuLayerState::Activating;
	std::vector<Quad> m_quads;
	SceneLayer& m_scene;
	LevelEditor& m_editor;

};
