#pragma once

// entry point
//#include "include/independent/core/entrypoint.h"
#include "core/entryPoint.h"
#include "engine.h"

#include "sceneLayer.h"
#include "UILayer1.h"

class engineApp : public Engine::Application
{
public:
	engineApp(Engine::ApplicationProps props);
	~engineApp() override;

private:
	std::shared_ptr<UILayer> m_uiLayer;
    std::shared_ptr<SceneLayer> m_sceneLayer;
};
