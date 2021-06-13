//#include "core/UILayer1.h"

// TOOL
#include "UILayer1.h"
// add a comment
UILayer::UILayer(const char* name) : Layer(name)
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
	
	HorizontalContainer top, middle, slider, bottom;
	top.addWidget<Spacer>(100, 10);
	top.addWidget<Label>(300, 100,"Hello World!");

	middle.addWidget<Spacer>(50, 10);
	middle.addWidget<Label>(500, 100, "Some text message");

	slider.addWidget<Slider>(400, 0, 100, "Low", "High");
	slider.addWidget<Spacer>(50, 10);
	slider.addWidget<Slider>(200, 25, 75, "Min", "Max");

	bottom.addWidget<Button>(200, 60, "Button 1", []() {Log::info("Clicked on button 1"); });
	bottom.addWidget<Spacer>(300, 10);
	bottom.addWidget<Button>(200, 60, "Button 2", []() {Log::info("Clicked on button 2"); });


	m_window.addContainer(top);
	m_window.addContainer(middle);
	m_window.addContainer(slider);
	m_window.addContainer(bottom);
	
	//m_quads.push_back(Quad::createCentreHalfExtents({ 512.f,750 }, { 512.f,50.f }));
	m_window.show();
}

void UILayer::onRender()
{
	switch (m_state)
	{
	case UILayerState::Activating:
		m_state = UILayerState::Active;
		break;	
	case UILayerState::Deactivating:
		m_state = UILayerState::InActive;
		break;
	}

	if (m_state == UILayerState::Active)
	{
		std::shared_ptr<RenderCommands> disableDepthTestCommand;
		disableDepthTestCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglDisableDepthTest));

		std::shared_ptr<RenderCommands> enableBlendCommand;
		enableBlendCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglEnableBlend));

		std::shared_ptr<RenderCommands> blendFuncCommand;
		blendFuncCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglBlendFunc));

		Renderer2D::begin(m_swu);
		m_window.onRender();
		//Renderer2D::submit(m_quads[0], { 0.2f,0.6f,0.4f,0.5f });
		//Renderer2D::submit("Test Footer", { 300.f,780.f }, { 0.4f,0.0f,0.0f,0.8f });

		Renderer2D::end();

	}


	
	/*
	//disable the depth test.
	RendererCommons::actionCommand(disableDepthTestCommand);
	//enable blending.
	RendererCommons::actionCommand(enableBlendCommand);
	RendererCommons::actionCommand(blendFuncCommand);
	*/

		
}

void UILayer::onKeyPressed(KeyPressedEvent& e)
{
	switch (e.getKeycode())
	{
	case NG_KEY_G:
		m_state = UILayerState::Activating;
		break;
	case NG_KEY_H:
		m_state = UILayerState::Deactivating;
		break;
	}
	if (m_state == UILayerState::Active) e.handleEvent(true);

}

void UILayer::onMouseMove(MouseMovementEvent& e)
{
	glm::ivec2 mousePos = e.getMousePosition();
	m_window.onMouseMove(mousePos);
}

void UILayer::onMousePress(MouseButtonPressEvent& e)
{
	glm::ivec2 mousePos =InputPoller::getMousePosition();
	m_window.onMousePress(mousePos,e.getButtonPressed());
}

void UILayer::onMouseRelease(MouseButtonReleaseEvent& e)
{
	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMouseRelease(mousePos, e.getButtonReleased());
}