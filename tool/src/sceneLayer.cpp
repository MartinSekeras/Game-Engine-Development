#include "sceneLayer.h"

//entt::registry registry;
//auto entity = registry.create();
//registry.destroy(entity);

SceneLayer::SceneLayer(const char * name) : Layer(name)
{
	m_transforms.resize(4);
	m_transforms[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
	m_transforms[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
	m_transforms[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));
	m_transforms[3] = glm::rotate(glm::translate(glm::mat4(1.0f), m_position), m_angle, { 0,1,0 });

	
	auto& window = Application::getInstance().getWindow();

	FreeEulerParams FPSCamParams;
	FPSCamParams.position = glm::vec3(0.f, 0.f, 6.f);
	FPSCamParams.width = window->getWidth();
	FPSCamParams.height = window->getHeight();
	FPSCamParams.layer = std::shared_ptr<Layer>(this);

	m_FPSCamera = std::make_shared<FreeEulerCamController>(FreeEulerCamController(FPSCamParams));

	m_currentCamera = m_FPSCamera;

	m_swu["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_FPSCamera->getCamera().view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_FPSCamera->getCamera().projection)));
	m_swu["u_lightColour"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightData[0])));
	m_swu["u_lightPos"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightData[1])));
	m_swu["u_viewPos"] = std::pair<ShaderDataType, void *>(ShaderDataType::Float3, static_cast<void *>(glm::value_ptr(lightData[2])));

	{
		std::shared_ptr<RenderCommands> setClearCommand;
		setClearCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setClearColour, 0.7f, 0.7f, 0.7f, 1.0f));
		RendererCommons::actionCommand(setClearCommand);
	}

#pragma region TEXTURES

	//auto& resources = Application::getInstance().getResourceManager();
	//std::shared_ptr<Textures> letterTexture =;
	std::shared_ptr<Textures> letterTexture;
	letterTexture.reset(Textures::create("assets/textures/letterCube.png"));

	//SubTexture letterSubTextre(letterTexture, glm::vec2(0.f), glm::vec2(1.f));
	//SubTexture ESubTexture(letterTexture, glm::vec2(0.33f, 0.5), glm::vec2(0.66f, 1.f));


#pragma endregion 

#pragma region RAW_DATA
		std::vector<TPVertexNormalised> cubeVertices(24);
	//										 <------- Pos ------->             <----- normal ----->             <---- UV ---->
	cubeVertices.at(0) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  0.0f, -1.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	cubeVertices.at(1) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  0.0f, -1.0f }), GenFuncs::normalise({ 0.0f,  0.5f }));
	cubeVertices.at(2) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  0.0f, -1.0f }), GenFuncs::normalise({ 0.33f, 0.5f }));
	cubeVertices.at(3) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  0.0f, -1.0f }), GenFuncs::normalise({ 0.33f, 0.0f }));

	cubeVertices.at(4) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  0.0f,  1.0f }), GenFuncs::normalise({ 0.33f, 0.5f }));
	cubeVertices.at(5) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  0.0f,  1.0f }), GenFuncs::normalise({ 0.66f, 0.5f }));
	cubeVertices.at(6) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  0.0f,  1.0f }), GenFuncs::normalise({ 0.66f, 0.0f }));
	cubeVertices.at(7) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  0.0f,  1.0f }), GenFuncs::normalise({ 0.33f, 0.0f }));

	cubeVertices.at(8) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f, -1.0f,  0.0f }), GenFuncs::normalise({ 1.0f,  0.0f }));
	cubeVertices.at(9) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f, -1.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 0.0f }));
	cubeVertices.at(10) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f, -1.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 0.5f }));
	cubeVertices.at(11) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f, -1.0f,  0.0f }), GenFuncs::normalise({ 1.0f,  0.5f }));

	cubeVertices.at(12) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  1.0f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.5f }));
	cubeVertices.at(13) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  1.0f,  0.0f }), GenFuncs::normalise({ 0.0f,  1.0f }));
	cubeVertices.at(14) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,  1.0f,  0.0f }), GenFuncs::normalise({ 0.33f, 1.0f }));
	cubeVertices.at(15) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,  1.0f,  0.0f }), GenFuncs::normalise({ 0.3f,  0.5f }));

	cubeVertices.at(16) = TPVertexNormalised({ -0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ -1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 0.5f }));
	cubeVertices.at(17) = TPVertexNormalised({ -0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ -1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.33f, 0.5f }));
	cubeVertices.at(18) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ -1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.33f, 1.0f }));
	cubeVertices.at(19) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ -1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 1.0f }));

	cubeVertices.at(20) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 1.0f,  1.0f }));
	cubeVertices.at(21) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f }, GenFuncs::normalise({ 1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 1.0f,  0.5f }));
	cubeVertices.at(22) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f }, GenFuncs::normalise({ 1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 0.5f }));
	cubeVertices.at(23) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 1.0f,  0.0f,  0.0f }), GenFuncs::normalise({ 0.66f, 1.0f }));

	std::vector<TPVertexNormalised> pyramidVertices(16);
	//										     <------- Pos ------->            <--------- normal --------->               <---- UV ---->		
	pyramidVertices.at(0) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,	-1.0f,     0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(1) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,	-1.0f,	   0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(2) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,	-1.0f,     0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(3) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,	-1.0f,     0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));

	pyramidVertices.at(4) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ -0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(5) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ -0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(6) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, GenFuncs::normalise({ -0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));

	pyramidVertices.at(7) = TPVertexNormalised({ -0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,	 0.4472f,  0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(8) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.0f,	 0.4472f,  0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(9) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, GenFuncs::normalise({ 0.0f,	 0.4472f,  0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));

	pyramidVertices.at(10) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f }, GenFuncs::normalise({ 0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(11) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(12) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, GenFuncs::normalise({ 0.8944f, 0.4472f,  0.0f }), GenFuncs::normalise({ 0.0f,  0.0f }));

	pyramidVertices.at(13) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,	 0.4472f, -0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(14) = TPVertexNormalised({ -0.5f, -0.5f, -0.5f }, GenFuncs::normalise({ 0.0f,	 0.4472f, -0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));
	pyramidVertices.at(15) = TPVertexNormalised({ 0.0f,  0.5f,  0.0f }, GenFuncs::normalise({ 0.0f,	 0.4472f, -0.8944f }), GenFuncs::normalise({ 0.0f,  0.0f }));


	uint32_t pyramidIndices[3 * 6] =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		7, 8, 9,
		10, 11, 12,
		13, 14, 15
	};

	std::vector<uint32_t> cubeIndices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};
#pragma endregion

#pragma region GL_BUFFERS
	//if (!Renderer3D::addGeometry(cubeVerticesBatch, cubeIndices, cube)) Log::error("Could not add geometry");

	std::shared_ptr<VertexBuffer> pyramidVBO;
	std::shared_ptr<IndexBuffer> pyramidIBO;


	//create/reset the VAO, VBO & IBO.
	pyramidVAO.reset(VertexArray::create());
	pyramidVBO.reset(VertexBuffer::create(pyramidVertices.data(), sizeof(TPVertexNormalised) * pyramidVertices.size(), TPVertexNormalised::getBufferLayout()));
	pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

	//set the vertex and index buffers. 
	pyramidVAO->addVertexBuffer(pyramidVBO);
	pyramidVAO->setIndexBuffer(pyramidIBO);

#pragma endregion 



	//initiate 3D renderer & attach shaders.
	Renderer3D::init();
#pragma region SHADERS

	TPShader.reset(Shaders::create("assets/shaders/texturedPhong.glsl"));
	Renderer3D::attachShader(TPShader);

#pragma endregion 



#pragma region MATERIALS
	
	TextureTypeStruct textureStructPyramid;


	TextureTypeStruct textureStructLetter;
	textureStructLetter.diffuseTexture = letterTexture;

	pyramidMaterial.reset(new Material(TPShader, textureStructPyramid, { 0.3f, 0.9f, 0.4f, 1.0f }));
	letterCubeMaterial.reset(new Material(TPShader, textureStructLetter));
	
#pragma endregion 

	auto& m_entities = Application::getInstance().m_entities;

	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities.back(), cubeVertices, cubeIndices, letterCubeMaterial);
	m_registry.emplace<TransformComponent>(m_entities.back(),glm::vec3( 0,0,-6 ), glm::vec3(0,0,0 ), glm::vec3(1,1,1 ));
}

void SceneLayer::onRender()
{
	m_swu["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_currentCamera->getCamera().view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_currentCamera->getCamera().projection)));



	std::shared_ptr<RenderCommands> clearCommand;
	clearCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::clearColourAndDepthBuffer));

	std::shared_ptr<RenderCommands> enableDepthTestCommand;
	enableDepthTestCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglEnableDepthTest));
	std::shared_ptr<RenderCommands> disableBlendCommand;
	disableBlendCommand.reset(RenderCommandsFactory::createCommand(RenderCommands::Commands::setglDisableBlend));

	RendererCommons::actionCommand(clearCommand);

	RendererCommons::actionCommand(enableDepthTestCommand);
	RendererCommons::actionCommand(disableBlendCommand);

	Renderer3D::begin(m_swu);

	auto group = m_registry.group<TransformComponent, RenderComponent>();
	for (auto entity : group)
	{
		auto& transform = group.get<TransformComponent>(entity);
		auto& render = group.get<RenderComponent>(entity);
		Renderer3D::submit(render.geometry, render.material, transform.getTransform());
	}


	Renderer3D::submit(pyramidVAO, pyramidMaterial, m_transforms[0]);

	Renderer3D::end();
}

void SceneLayer::onUpdate(float timestep)
{
	m_currentCamera->onUpdate(timestep);

	m_transforms[0] = glm::rotate(m_transforms[0], timestep, { 0,1,0 });
}

void SceneLayer::onKeyPressed(KeyPressedEvent & e)
{
	if (m_currentCamera == m_FPSCamera)
	{
		glm::vec3 forward, right;
		switch (e.getKeycode())
		{
		case NG_KEY_W:
			forward = { -m_transforms[0][0][0], -m_transforms[0][0][1], -m_transforms[0][0][2] };
			m_position += forward * 0.1f;
			e.handleEvent(true);
			break;
		case NG_KEY_S:
			forward = { -m_transforms[0][0][0], -m_transforms[0][0][1], -m_transforms[0][0][2] };
			m_position -= forward * 0.1f;
			e.handleEvent(true);
			break;
		case NG_KEY_A:
			right = { m_transforms[0][0][0], m_transforms[0][0][1], m_transforms[0][0][2] };
			m_position += right * 0.1f;
			e.handleEvent(true);
			break;
		case NG_KEY_D:
			right = { -m_transforms[0][0][0], -m_transforms[0][0][1], -m_transforms[0][0][2] };
			m_position += right * 0.1f;
			e.handleEvent(true);
			break;
		case NG_KEY_Q:
			m_angle -= 0.05f;
			e.handleEvent(true);
			break;
		case NG_KEY_E:
			m_angle -= 0.05f;
			e.handleEvent(true);
			break;
		}
		m_transforms[0] = glm::rotate(glm::translate(glm::mat4(1.0f), m_position), m_angle, { 0,1,0 });
	}
}

void SceneLayer::onResize(WindowResizeEvent & e)
{
	m_currentCamera->onResize(e);
}
