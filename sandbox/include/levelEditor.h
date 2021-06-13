#pragma once

/* levelEditor.h */
//Brief A layer which holds the level editor tool

// TOOL
#pragma once


#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <events/eventHeaders.h>
#include <core/application.h>

using namespace Engine;
enum class editorLayerState { InActive, Activating, Active, Deactivating }; //!< Class with states for the layer


class LevelEditor : public Layer
{
public:
	LevelEditor(const char* name);//!<Constructor
	void onRender() override;//!< On render function
	editorLayerState getState() { return m_state; }//!<Return the state
	void onUpdate(float time) override;//!<On update function

	virtual void onKeyPressed(KeyPressedEvent& e) override;//!< Functions for key presses
	virtual void onMouseMove(MouseMovementEvent& e) override;//!<Mouse movement functions
	virtual void onMousePress(MouseButtonPressEvent& e) override;//!<Mouse press functions
	virtual void onMouseRelease(MouseButtonReleaseEvent& e) override;//!<Mouse release functions
	void closeMenu();//!<Close the menu
	bool showScreen = false;//!< Show this screen
	bool returnToMenu = false; //!<Go back to main menu

private:
	std::shared_ptr<FreeOthroCamController> m_camera;
	SceneWideUniforms m_swu;

	ModalWindow m_window;
	editorLayerState m_state = editorLayerState::Activating;
	std::vector<Quad> m_quads;

};
