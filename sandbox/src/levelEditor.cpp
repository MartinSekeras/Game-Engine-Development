//#include "core/UILayer1.h"


// TOOL
#include "levelEditor.h"

// add a comment
LevelEditor::LevelEditor(const char* name) : Layer(name)
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



	//Level Editor
	HorizontalContainer topSpace, topButton, top, middle, bottomButtons, bottomSpace;

	topSpace.addWidget<Spacer>(800, 50);
	topButton.addWidget<Spacer>(100, 50);
	topButton.addWidget<Button>(100, 60, "Return", [&]() {Log::info("Returning to menu"); showScreen = false; returnToMenu = true; });
	topButton.addWidget<Spacer>(700, 200);

	topButton.addWidget<Button>(100, 60, "Test", [&]() {Log::info("Testing"); });

	top.addWidget<Spacer>(200, 100);

	top.addWidget<Label>(150, 50, "Game Zone");
	top.addWidget<Spacer>(400, 100);
	top.addWidget<Slider>(250, 10, 190, "Low", "High", "Adjust Timer");

	middle.addWidget<Spacer>(300, 100);


	//Buttons to add objects to the level, these should be placed in scene

	bottomButtons.addWidget<Spacer>(50, 50);
	bottomButtons.addWidget<Button>(100, 60, "Wall", [&]() {Log::info("Inserting wall"); });
	bottomButtons.addWidget<Spacer>(40, 50);
	bottomButtons.addWidget<Button>(100, 60, "Enemy", [&]() {Log::info("Inserting Enemy"); });
	bottomButtons.addWidget<Spacer>(40, 50);
	bottomButtons.addWidget<Button>(100, 60, "Player", [&]() {Log::info("Inserting Player"); });	
	bottomButtons.addWidget<Spacer>(40, 50);
	bottomButtons.addWidget<Button>(100, 60, "Undo", [&]() {Log::info("Undo Change"); });	
	bottomButtons.addWidget<Spacer>(40, 50);
	bottomButtons.addWidget<Button>(100, 60, "Redo", [&]() {Log::info("Redo Change"); });	
	bottomButtons.addWidget<Spacer>(20, 50);
	bottomButtons.addWidget<Slider>(250, 0, 100, "Low", "High", "Difficulty");

	//bottomSpace.addWidget<Spacer>(1000, 100);

	m_window.addContainer(topSpace);
	m_window.addContainer(topButton);
	m_window.addContainer(top);
	m_window.addContainer(middle);
	m_window.addContainer(bottomButtons);

	m_window.addContainer(bottomSpace);




	m_window.show();



}

void LevelEditor::onRender()
{
	if (showScreen == true)
	{
		m_state = editorLayerState::Activating;
	}
	else { m_state = editorLayerState::Deactivating; }
	switch (m_state)
	{
	case editorLayerState::Activating:
		m_state = editorLayerState::Active;
		break;
	case editorLayerState::Deactivating:
		m_state = editorLayerState::InActive;
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


	if (m_state == editorLayerState::Active)
	{
		m_window.onRender();
	}


	Renderer2D::end();
}

void LevelEditor::onKeyPressed(KeyPressedEvent& event)
{

	switch (event.getKeycode())
	{


	}

	//return event.isEventHandled();
	if (m_state == editorLayerState::Active) event.handleEvent(true);
}


void LevelEditor::onMouseMove(MouseMovementEvent& e)
{
	glm::ivec2 mousePos = e.getMousePosition();
	m_window.onMouseMove(mousePos);
}


void LevelEditor::onMousePress(MouseButtonPressEvent& e)
{
	Log::error("Mouse pressed");
	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMousePress(mousePos, e.getButtonPressed());
}


void LevelEditor::onMouseRelease(MouseButtonReleaseEvent& e)
{
	Log::error("Mouse released");


	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMouseRelease(mousePos, e.getButtonReleased());
}

void LevelEditor::closeMenu()
{
	m_state = editorLayerState::Deactivating;
}

void LevelEditor::onUpdate(float time)
{

}
