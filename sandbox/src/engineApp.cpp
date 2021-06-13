/** \file engineApp.cpp
*/
//#include "engineApp.h"
#include "engineApp.h"

engineApp::engineApp(Engine::ApplicationProps props) : Application(props)
{
	//Create the layers
	m_sceneLayer = new SceneLayer("Scene Layer");
	m_levelEditor = new LevelEditor("Level Editor");
	m_layerStack.push(m_sceneLayer);
	m_layerStack.push(m_levelEditor);
	//Layers with others referenced
	m_layerStack.push(new UILayer("UI Layer", *m_sceneLayer));
	m_layerStack.push(new MainMenu("Main Menu",*m_sceneLayer, *m_levelEditor));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	ApplicationProps props;
	props.winProps.windowTitle = "Sandbox App";
	props.winProps.width = 1024;
	props.winProps.height = 800;
	props.characterSize = 56;
	return new engineApp(props);
}

void engineApp::update(float t)
{
	if (m_uiLayer->quit == true) Log::info("quitting");
}