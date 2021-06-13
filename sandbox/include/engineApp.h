#pragma once

// entry point
//#include "include/independent/core/entrypoint.h"
#include "core/entryPoint.h"
#include "engine.h"

#include "sceneLayer.h"
#include "UILayer1.h"
#include "mainMenu.h"
#include "levelEditor.h"

class engineApp : public Engine::Application
{
public:
	engineApp(Engine::ApplicationProps props);
	~engineApp() override;
	void update(float t);
private:
	//Used to reference each layer
	SceneLayer* m_sceneLayer;
	UILayer* m_uiLayer;
	MainMenu* m_mainMenu;
	LevelEditor* m_levelEditor;

};
