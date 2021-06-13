/** \file engineApp.cpp
*/
//#include "engineApp.h"
#include "engineApp.h"

engineApp::engineApp(Engine::ApplicationProps props) : Application(props)
{
	m_layerStack.push(new SceneLayer("Scene Layer"));
	m_layerStack.push(new UILayer("UI Layer"));
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