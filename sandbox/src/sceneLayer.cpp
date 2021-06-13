#include "sceneLayer.h"

//entt::registry registry;
//auto entity = registry.create();
//registry.destroy(entity);

SceneLayer::SceneLayer(const char * name) : Layer(name), m_registry(Application::getInstance().m_registry)
{
	m_transforms.resize(4);
	m_transforms[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
	m_transforms[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
	m_transforms[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));
	m_transforms[3] = glm::rotate(glm::translate(glm::mat4(1.0f), m_position), m_angle, { 0,1,0 });

	auto& window = Application::getInstance().getWindow();

	m_score = 0;

	FreeEulerParams CameraTopDownParams;
	CameraTopDownParams.position = glm::vec3(0.f, 0.f, 6.f);
	CameraTopDownParams.width = window->getWidth();
	CameraTopDownParams.height = window->getHeight();
	CameraTopDownParams.layer = std::shared_ptr<Layer>(this);
	m_TopDownCamera = std::make_shared<FreeEulerCamController>(FreeEulerCamController(CameraTopDownParams));

	FreeEulerParams Camera3rdPersonParams;
	Camera3rdPersonParams.position = glm::vec3(0.0f);
	Camera3rdPersonParams.width = window->getWidth();
	Camera3rdPersonParams.height = window->getHeight();
	Camera3rdPersonParams.layer = std::shared_ptr<Layer>(this);
	m_3rdPersonCamera = std::make_shared<FreeEulerCamController>(FreeEulerCamController(Camera3rdPersonParams));

	m_currentCamera = m_TopDownCamera;

	m_swu["u_view"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_currentCamera->getCamera().view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void *>(ShaderDataType::Mat4, static_cast<void *>(glm::value_ptr(m_currentCamera->getCamera().projection)));
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
	std::shared_ptr<Textures> letterTexture;
	std::shared_ptr<Textures> floorTexture;
	std::shared_ptr<Textures> wallTexture;
	std::shared_ptr<Textures> stoneTexture;
	std::shared_ptr<Textures> playerTexture;
	std::shared_ptr<Textures> collectableTexture;
	std::shared_ptr<Textures> aiTexture;


	letterTexture.reset(Textures::create("assets/textures/letterCube.png"));
	floorTexture.reset(Textures::create("assets/textures/floor.png"));
	wallTexture.reset(Textures::create("assets/textures/wall.png"));
	stoneTexture.reset(Textures::create("assets/textures/stone_floor_01.jpg"));
	playerTexture.reset(Textures::create("assets/textures/green.jpg"));
	collectableTexture.reset(Textures::create("assets/textures/collectable.png"));
	aiTexture.reset(Textures::create("assets/textures/aitexture.png"));


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

	TextureTypeStruct textureStructFloor;
	textureStructFloor.diffuseTexture = floorTexture;

	TextureTypeStruct textureStructWalls;
	textureStructWalls.diffuseTexture = wallTexture;

	TextureTypeStruct textureStructStoneFloor;
	textureStructStoneFloor.diffuseTexture = stoneTexture;

	TextureTypeStruct textureStructPlayer;
	textureStructPlayer.diffuseTexture = playerTexture;

	TextureTypeStruct textureStructCollectable;
	textureStructCollectable.diffuseTexture = collectableTexture;

	TextureTypeStruct textureStructAi;
	textureStructAi.diffuseTexture = aiTexture;


	pyramidMaterial.reset(new Material(TPShader, textureStructPyramid, { 0.3f, 0.9f, 0.4f, 1.0f }));
	letterCubeMaterial.reset(new Material(TPShader, textureStructLetter));

	CheckedFloorMaterial.reset(new Material(TPShader, textureStructFloor));
	wallMaterial.reset(new Material(TPShader, textureStructWalls));
	stoneFloorMaterial.reset(new Material(TPShader, textureStructStoneFloor));
	playerMaterial.reset(new Material(TPShader, textureStructPlayer));
	collectableMaterial.reset(new Material(TPShader, textureStructCollectable));
	aiMaterial.reset(new Material(TPShader, textureStructAi));
#pragma endregion 

#pragma region ENTITIES
	auto& m_entities = Application::getInstance().m_entities;

	m_entities.reserve(400);

	m_world = Application::getInstance().world;
	m_world->setEventListener(&m_physicsEventListener);

	//root
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RootComponent>(m_entities[0]);
	m_registry.emplace<TransformComponent>(m_entities[0]);
	m_registry.emplace<RelationshipComponent>(m_entities[0]);

	// Player cube 
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[1], cubeVertices, cubeIndices, playerMaterial);
	m_registry.emplace<TransformComponent>(m_entities[1],glm::vec3( -4 , 0, 9), glm::vec3(0,0,0 ), glm::vec3(1,1,1 ));
	m_registry.emplace<RelationshipComponent>(m_entities[1]);
	//HierarchySystem::setChild(m_entities[0], m_entities[1]);
	auto t = m_registry.get<TransformComponent>(m_entities[1]).getTransform();
	auto b = m_registry.emplace<RigidBodyComponent>(m_entities[1], RigidBodyType::Dynamic, t, 1);
	m_registry.emplace<BoxColliderComponent>(m_entities[1], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));
	// Needs a trigger to register if off ground,
	m_registry.emplace<Player>(m_entities[1], b.m_body);

	//floor
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities[2], glm::vec3(0.f, -1.f, -6.f), glm::vec3(0.f, 0.0f, 0.f), glm::vec3(100.f, 0.3f, 100.f));
	m_registry.emplace<RenderComponent>(m_entities[2], cubeVertices, cubeIndices, CheckedFloorMaterial);
	m_registry.emplace<RelationshipComponent>(m_entities[2]);
	//HierarchySystem::setChild(m_entities[0], m_entities[2]);
	t = m_registry.get<TransformComponent>(m_entities[2]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[2], RigidBodyType::Static, t, 2);
	m_registry.emplace<BoxColliderComponent>(m_entities[2], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// AI CUBE 1
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[3], cubeVertices, cubeIndices, aiMaterial);
	m_registry.emplace<TransformComponent>(m_entities[3], glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::vector<glm::vec3> waypoints = { glm::vec3(-8, 0, 0),  glm::vec3(1, 0, 0) };
	m_registry.emplace<SimpleAI>(m_entities[3], 0, SimpleAI::State::turning, waypoints);
	t = m_registry.get<TransformComponent>(m_entities[3]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[3], RigidBodyType::Dynamic, t, 3);
	m_registry.emplace<BoxColliderComponent>(m_entities[3], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Collectable 
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[4], cubeVertices, cubeIndices, collectableMaterial);
	m_registry.emplace<TransformComponent>(m_entities[4], glm::vec3(-8, 0, -8), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5));
	m_registry.emplace<RelationshipComponent>(m_entities[4]);
	t = m_registry.get<TransformComponent>(m_entities[4]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[4], RigidBodyType::Static, t, 4);
	m_registry.emplace<BoxColliderComponent>(m_entities[4], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));
	m_registry.emplace<DestroyOnContactComponent>(m_entities[4]);
	
	// Wall One
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[5], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[5], glm::vec3(10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 20));
	m_registry.emplace<RelationshipComponent>(m_entities[5]);
	t = m_registry.get<TransformComponent>(m_entities[5]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[5], RigidBodyType::Static, t, 5);
	m_registry.emplace<BoxColliderComponent>(m_entities[5], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Wall Two
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[6], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[6], glm::vec3(-10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 20));
	m_registry.emplace<RelationshipComponent>(m_entities[6]);
	t = m_registry.get<TransformComponent>(m_entities[6]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[6], RigidBodyType::Static, t, 6);
	m_registry.emplace<BoxColliderComponent>(m_entities[6], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));
	
	// Wall Three
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[7], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[7], glm::vec3(0, 0, 10.5), glm::vec3(0, 0, 0), glm::vec3(21, 1, 1));
	m_registry.emplace<RelationshipComponent>(m_entities[7]);
	t = m_registry.get<TransformComponent>(m_entities[7]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[7], RigidBodyType::Static, t, 7);
	m_registry.emplace<BoxColliderComponent>(m_entities[7], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Wall Four
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[8], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[8], glm::vec3(0, 0, -10.5), glm::vec3(0, 0, 0), glm::vec3(21, 1, 1));
	m_registry.emplace<RelationshipComponent>(m_entities[8]);
	t = m_registry.get<TransformComponent>(m_entities[8]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[8], RigidBodyType::Static, t, 8);
	m_registry.emplace<BoxColliderComponent>(m_entities[8], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Wall Five
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[9], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[9], glm::vec3(-6, 0, -5), glm::vec3(0, 0, 0), glm::vec3(7, 1, 1));
	m_registry.emplace<RelationshipComponent>(m_entities[9]);
	t = m_registry.get<TransformComponent>(m_entities[9]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[9], RigidBodyType::Static, t, 9);
	m_registry.emplace<BoxColliderComponent>(m_entities[9], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Wall Six
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[10], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[10], glm::vec3(6, 0, 0), glm::vec3(0, 0, 0), glm::vec3(7, 1, 1));
	m_registry.emplace<RelationshipComponent>(m_entities[10]);
	t = m_registry.get<TransformComponent>(m_entities[10]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[10], RigidBodyType::Static, t, 10);
	m_registry.emplace<BoxColliderComponent>(m_entities[10], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// Wall Seven
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[11], cubeVertices, cubeIndices, wallMaterial);
	m_registry.emplace<TransformComponent>(m_entities[11], glm::vec3(-6, 0, 5), glm::vec3(0, 0, 0), glm::vec3(7, 1, 1));
	m_registry.emplace<RelationshipComponent>(m_entities[11]);
	t = m_registry.get<TransformComponent>(m_entities[11]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[11], RigidBodyType::Static, t, 11);
	m_registry.emplace<BoxColliderComponent>(m_entities[11], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));

	// AI CUBE 2
	m_entities.push_back(m_registry.create());
	m_registry.emplace<RenderComponent>(m_entities[12], cubeVertices, cubeIndices, aiMaterial);
	m_registry.emplace<TransformComponent>(m_entities[12], glm::vec3(0, 0, -6), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	std::vector<glm::vec3> waypoints_two = { glm::vec3(-1, 0, -6),  glm::vec3(8, 0, -6) };
	m_registry.emplace<SimpleAI>(m_entities[12], 0, SimpleAI::State::turning, waypoints_two);
	t = m_registry.get<TransformComponent>(m_entities[12]).getTransform();
	b = m_registry.emplace<RigidBodyComponent>(m_entities[12], RigidBodyType::Dynamic, t, 12);
	m_registry.emplace<BoxColliderComponent>(m_entities[12], b, glm::vec3(t[0][0] * 0.5f, t[1][1] * 0.5f, t[2][2] * 0.5));
}
#pragma endregion

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

	Renderer3D::end();
}

// Create a view that gets all AI components
void SceneLayer::onUpdate(float timestep)
{
	if (paused == false)
	{
		auto& m_entities = Application::getInstance().m_entities;

		TransformComponent playerTransComp = m_registry.get<TransformComponent>(m_entities[1]);
		TransformComponent testTransComp = m_registry.get<TransformComponent>(m_entities[3]);
		if (b3rdPersonCamera)
		{
			m_currentCamera = m_3rdPersonCamera;
			m_currentCamera->onUpdate(timestep, playerTransComp);
			//m_currentCamera->onUpdate(timestep, testTransComp);
		}
		else
		{
			//keep top-down as go-to default.
			m_currentCamera = m_TopDownCamera;
			m_currentCamera->onUpdate(timestep);
		}


		//m_transforms[0] = glm::rotate(m_transforms[0], timestep, { 0,1,0 });
		m_world->update(timestep);
		m_score += m_physicsEventListener.actionDestroy() * 100;
		NGPhysicsSystem::updateTransform();

		// Update the AI
		auto AIview = m_registry.view<SimpleAI>();
		for (auto entity : AIview) FSMSystem::Update(entity, timestep);

		// Update player movement
		auto k_view = m_registry.view<Player>();
		for (auto entity : k_view)
		{
			auto& playerComp = m_registry.get<Player>(entity);
			playerComp.onUpdate(timestep);
		}

		HierarchySystem::updateChildren();
		Log::info("score {0}", m_score);
		if (m_score == 100)
		{
			winner = true;
		}
		if (winner == true)
		{
			paused = true;
		}
	}
}

void SceneLayer::onKeyPressed(KeyPressedEvent & e)
{
	if (m_currentCamera == m_TopDownCamera || m_currentCamera == m_3rdPersonCamera)
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
		case NG_KEY_C:
			//switch camera.
			if (bTopDownCamera)
			{
				b3rdPersonCamera = true;
				bTopDownCamera   = false;
			}
			else
			{
				b3rdPersonCamera = false;
				bTopDownCamera   = true;
			}
			break;
		}
		m_transforms[0] = glm::rotate(glm::translate(glm::mat4(1.0f), m_position), m_angle, { 0,1,0 });
	}
}

void SceneLayer::onResize(WindowResizeEvent & e)
{
	m_currentCamera->onResize(e);
}



