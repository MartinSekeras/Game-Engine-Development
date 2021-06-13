//#include "core/UILayer1.h"


// TOOL
#include "UILayer1.h"
#include <string>
using namespace std;
// add a comment
UILayer::UILayer(const char* name, SceneLayer& scene) : Layer(name), m_scene(scene)
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
	
	

	//Pause window, create containers and fill with widgets 
	HorizontalContainer top, middle, gap, slider, bottom;
	top.addWidget<Spacer>(300, 10);
	top.addWidget<Label>(100, 50, "Paused");
	gap.addWidget<Spacer>(250, 100);
	gap.addWidget<Button>(200, 60, "Resume", [&]() {Log::info("Resuming Game"); UILayer::closeMenu(); m_scene.paused = false; });
	
	middle.addWidget<Spacer>(200, 10);

	slider.addWidget<Spacer>(130, 20);
	slider.addWidget<Slider>(400, 10, 190, "Low", "High", "Adjust Timer");
	
	   
	bottom.addWidget<Spacer>(30, 10);
	bottom.addWidget<Button>(200, 60, "Restart", [&]() {Log::info("Restarting Game"); Application::getInstance().restart(); winner = false; timeRemaining = startingTime; m_scene.m_score = 0; m_scene.paused = false; m_state = UILayerState::Deactivating;  });
	bottom.addWidget<Spacer>(200, 10);
	bottom.addWidget<Button>(200, 60, "Quit Game", [&]()	
		{
			Log::info("Quitting game");
			m_scene.quitGame = true;
			//m_app->m_running = false;
		});
	

	//Loser window	
	HorizontalContainer loserTop, loserMiddle, loserGap, loserBottom;

	loserTop.addWidget<Spacer>(280, 10);
	loserTop.addWidget<Label>(100, 50, "Game Over!");

	loserMiddle.addWidget<Spacer>(280, 50);
	loserMiddle.addWidget<Label>(100, 200, "You Ran Out of Time");

	loserBottom.addWidget<Spacer>(30, 10);
	loserBottom.addWidget<Button>(200, 60, "Play Again", [&]() {Log::info("Restarting Game"); Application::getInstance().restart(); timeRemaining = startingTime; m_scene.m_score = 0; gameOver = false; m_scene.paused = false; m_loserWindow.hide(); });
	loserBottom.addWidget<Spacer>(200, 10);
	loserBottom.addWidget<Button>(200, 60, "Quit Game", [&]() 
		{
			m_scene.quitGame = true;

			Log::info("Quitting game");
			m_loserWindow.hide();
		});

	//Win Window
	HorizontalContainer winTop, winMiddle, winGap, winBottom;

	winTop.addWidget<Spacer>(280, 100);
	winTop.addWidget<Label>(100, 50, "You Win!");

	winMiddle.addWidget<Spacer>(280, 150);
	winMiddle.addWidget<Label>(100, 50, "Would You Like to Play Again?");

	winBottom.addWidget<Spacer>(30, 10);
	winBottom.addWidget<Button>(200, 60, "Play Again", [&]() {Log::info("Restarting Game"); Application::getInstance().restart(); timeRemaining = startingTime; m_scene.m_score = 0; winner = false; m_winWindow.hide(); m_scene.paused = false; paused = false; });
	winBottom.addWidget<Spacer>(200, 10);
	winBottom.addWidget<Button>(200, 60, "Quit Game", [&]() 
		{
			m_scene.quitGame = true;
			Log::info("Quitting game");
			m_winWindow.hide();
		});
	
	

	
	m_window.addContainer(top);
	m_window.addContainer(gap);
	m_window.addContainer(slider);
	m_window.addContainer(middle);
	m_window.addContainer(bottom);

	m_loserWindow.addContainer(loserTop);
	m_loserWindow.addContainer(loserMiddle);
	m_loserWindow.addContainer(loserBottom);	
	
	m_winWindow.addContainer(winTop);
	m_winWindow.addContainer(winMiddle);
	m_winWindow.addContainer(winBottom);
	

	score = 0;

	//m_quads.push_back(Quad::createCentreHalfExtents({ 512.f,750 }, { 512.f,50.f }));

	//Prep windows for rendering
	m_loserWindow.show();
	m_winWindow.show();
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
		paused = true;
		m_state = UILayerState::InActive;
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
	if (m_state == UILayerState::Active)
	{
		m_window.onRender();
	}
	//Create the score and time footer
	string scoreText = ("Score: " + std::to_string(m_scene.m_score));
	const char* scoreTextChar = scoreText.c_str();

	int timeInt = (int)timeRemaining;
	string timeRem = std::to_string(timeInt);
	string timerString = ("Time Remaining: " + timeRem);

	const char* timer = timerString.c_str();
	if (m_scene.paused == false)
	{
		Renderer2D::submit(scoreTextChar, { 200.f,780.f }, { 0.4f,0.0f,0.0f,0.8f });
		Renderer2D::submit(timer, { 500.f,780.f }, { 0.4f,0.0f,0.0f,0.8f });

	}

	//If circumstances are met, show the right screen
	if (gameOver == true)
	{
		m_loserWindow.show();
		m_loserWindow.onRender();
	}
	if (winner == true)
	{
		m_window.hide();
		m_winWindow.show();
		m_winWindow.onRender();
	}	
	
	Renderer2D::end();
}

void UILayer::onKeyPressed(KeyPressedEvent& event)
{

	switch (event.getKeycode())
	{
	//Press p to pause
	case NG_KEY_P:
		Log::info("Pause toggled");

		if (m_state == UILayerState::Active)
		{
			m_state = UILayerState::Deactivating;
		}
		else if (m_state == UILayerState::InActive)
		{
			m_state = UILayerState::Activating;
		}
		m_scene.paused = !m_scene.paused;


	}

	//return event.isEventHandled();
	if (m_state == UILayerState::Active) event.handleEvent(true);
}


void UILayer::onMouseMove(MouseMovementEvent& e)
{
	glm::ivec2 mousePos = e.getMousePosition();
	m_window.onMouseMove(mousePos);
}


void UILayer::onMousePress(MouseButtonPressEvent& e)
{
	Log::error("Mouse pressed");
	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMousePress(mousePos, e.getButtonPressed());
}


void UILayer::onMouseRelease(MouseButtonReleaseEvent& e)
{
	Log::error("Mouse released");


	glm::ivec2 mousePos = InputPoller::getMousePosition();
	m_window.onMouseRelease(mousePos, e.getButtonReleased());
}

void UILayer::closeMenu()
{
	m_state = UILayerState::Deactivating;
}

void UILayer::onUpdate(float time)
{
	//A reset function
	if (m_scene.started == true)
	{
		score = 0;
		timeRemaining = startingTime;
		
		m_winWindow.hide();
		m_loserWindow.hide();
		gameOver = false;
		winner = false;
		m_scene.winner = false;
		//m_scene.paused = false;
		//Dont call again
		m_scene.started = false;
	}

	//If scene is paused, stop timer, if not count down
	if (m_scene.paused == false)
	{
		timeRemaining = timeRemaining - time;

	}
	//If time is up, game is over
	if (timeRemaining <= 0)
	{
		m_scene.paused = true;
		gameOver = true;
		timeRemaining = 0;
		m_window.hide();
	}
	//Get score and check if game is won
	score = m_scene.m_score;
	if (score == 100)
	{
		winner = true;
	}

	//Quit the game if met
	if (m_scene.quitGame == true)
	{
		m_state = UILayerState::Deactivating;
		m_winWindow.hide();
		m_loserWindow.hide();
	}
	//Check if the timer has been changed by the slider
	startingTimeChanged = Application::getInstance().sliderValue;
	if (startingTimeChanged != startingTime)
	{
		startingTime = startingTimeChanged;
		timeRemaining = startingTime;
	}

}
