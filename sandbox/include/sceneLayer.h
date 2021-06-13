#pragma once
#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/headerList.h"
#include "core/layer.h"
#include "components/renderComponent.h"
#include "components/transform.h"
#include "components/componentBasedCameras.h"
#include "components/player.h"
#include "components/physics.h"
#include "AI/SimpleAI.h"

using namespace Engine;

class SceneLayer : public Layer
{
public:
	SceneLayer(const char * name);
	void onRender() override;
	void onUpdate(float timestep) override;
	void onKeyPressed(KeyPressedEvent& e) override;
	void onResize(WindowResizeEvent& e) override;
	bool paused = false;
	int m_score = 0;
	//inline int getScore() { return m_score; };

	bool b3rdPersonCamera = true;
	bool bTopDownCamera = false;

	bool quitGame = false;
	bool winner = false;
	bool started = true;
private:
	SceneWideUniforms m_swu;
	glm::vec3 lightData[3] = { {1.0f, 1.0f, 1.0f} , {-2.0f, 4.0f, 6.0f} , {0.0f, 0.0f, 0.0f} };
	
	std::vector<glm::mat4> m_transforms;

	std::shared_ptr<CameraController> m_currentCamera;
	std::shared_ptr<FreeEulerCamController> m_TopDownCamera;
	std::shared_ptr<FreeEulerCamController> m_3rdPersonCamera;
	std::shared_ptr<FreeEulerCamController> m_TestCamera;

	std::shared_ptr<Material> pyramidMaterial;
	std::shared_ptr<Material> letterCubeMaterial;
	std::shared_ptr<Material> CheckedFloorMaterial;
	std::shared_ptr<Material> wallMaterial;
	std::shared_ptr<Material> stoneFloorMaterial;
	std::shared_ptr<Material> playerMaterial;
	std::shared_ptr<Material> obstacleMaterial;
	std::shared_ptr<Material> collectableMaterial;
	std::shared_ptr<Material> aiMaterial;

	std::shared_ptr<Shaders> TPShader;
	std::shared_ptr<VertexArray> pyramidVAO;

	glm::vec3 m_position = { 5,0,-4 };
	float m_angle = 0.3f;

	
	entt::registry& m_registry;
	rp3d::PhysicsWorld* m_world;
	enttListener m_physicsEventListener;

};
