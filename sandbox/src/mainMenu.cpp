//#include "core/UILayer1.h"


// TOOL
#include "mainMenu.h"

// add a comment
MainMenu::MainMenu(const char* name, SceneLayer& scene, LevelEditor& editor) : Layer(name), m_scene(scene), m_editor(editor)
{
	auto& window = Application::getInstance().getWindow();

	//initiate 2D renderer.
	Renderer2D::init();

	Fixed2DParams camParams;
	camParams.width = window->getWidth();
	camParams.height = window->getHeight();

	m_camera.reset(new FreeOthroCamController(camParams));

	m_swu["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)));
	
	

	//Main Menu, create containers an fill with widgets
	HorizontalContainer topSpace, mainTop, mainMiddle,mainMiddleEditor, mainBottom, bottomSpace;
	topSpace.addWidget<Spacer>(1000, 300);
	mainTop.addWidget<Spacer>(500, 100);
	mainTop.addWidget<Label>(100, 10, "The Game");

	//mainTop.addWidget<Spacer>(480, 100);

	mainMiddle.addWidget<Spacer>(450, 300);
	mainMiddle.addWidget<Button>(200, 80, "Start Game", [&]()
		{
			Log::info("Starting Game");
			m_window.hide();
			m_scene.paused = false;
			m_scene.started = true;
		});

	mainMiddleEditor.addWidget<Spacer>(450, 200);

	mainMiddleEditor.addWidget<Button>(200, 80, "Level Editor", [&]()
		{
			Log::info("Level Editor starting");
			m_editor.showScreen = true;
			m_state = MenuLayerState::Deactivating;
		});

	mainBottom.addWidget<Spacer>(250, 10);
	mainBottom.addWidget<Button>(200, 60, "Settings", []() {Log::info("Settings"); });
	mainBottom.addWidget<Spacer>(200, 400);
	mainBottom.addWidget<Button>(200, 60, "Quit Game", [&]() {Log::info("Game closing"); m_app->getInstance().m_running = false; });


	m_window.addContainer(topSpace);
	m_window.addContainer(mainTop);
	m_window.addContainer(mainMiddle);
	m_window.addContainer(mainMiddleEditor);

	m_window.addContainer(mainBottom);
	



	//m_quads.push_back(Quad::createCentreHalfExtents({ 512.f,750 }, { 512.f,50.f }));
	//Show the window
	m_window.show();


}

void MainMenu::onRender()
{
	switch (m_state)
	{
	case MenuLayerState::Activating:
		m_state = MenuLayerState::Active;
		break;
	case MenuLayerState::Deactivating:
		m_state = MenuLayerState::InActive;
		break;
	}

	std::shared_ptr<RenderCommands> disableDepthTestCommand;
	disableDepthTestCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglDisableDepthTest));

	std::shared_ptr<RenderCommands> enableBlendCommand;
	enableBlendCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglEnableBlend));

	std::shared_ptr<RenderCommands> blendFuncCommand;
	blendFuncCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglBlendFunc));
	RendererCommons::actionCommand(enableBlendCommand);
	RendererCommons::actionCommand(disableDepthTestCommand);
	RendererCommons::actionCommand(blendFuncCommand);
	Renderer2D::begin(m_swu);

	if (m_state == MenuLayerState::Active)
	{
		m_window.onRender();
	}
	//Renderer2D::submit(m_quads[0], { 0.2f,0.6f,0.4f,0.5f });
	//int score = SceneLayer::getScore();


	Renderer2D::end();
}

void MainMenu::onKeyPressed(KeyPressedEvent& event)
{

	switch (event.getKeycode())
	{


	}

	//return event.isEventHandled();
	if (m_state == MenuLayerState::Active) event.handleEvent(true);
}


void MainMenu::onMouseMove(MouseMovementEvent& e)
{
	glm::ivec2 mousePos = e.getMousePosition();
	m_window.onMouseMove(mousePos);
}


void MainMenu::onMousePress(MouseButtonPressEvent& e)
{
	Log::error("Mouse pressed");
	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMousePress(mousePos, e.getButtonPressed());
}


void MainMenu::onMouseRelease(MouseButtonReleaseEvent& e)
{
	Log::error("Mouse released");


	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMouseRelease(mousePos, e.getButtonReleased());
}

void MainMenu::closeMenu()
{
	m_state = MenuLayerState::Deactivating;
}

void MainMenu::onUpdate(float time)
{
	if (m_scene.quitGame == true)
	{
		m_state = MenuLayerState::Activating;
		m_window.show();
		m_scene.quitGame = false;
	}
	if (m_editor.returnToMenu == true)
	{
		m_state = MenuLayerState::Activating;
		m_editor.returnToMenu = false;
	}
	//Log::info(mainMenu);
	//score = m_scene->getScore();
}
