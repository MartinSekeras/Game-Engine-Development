#pragma once
#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/headerList.h"
#include "core/layer.h"
#include "components/renderComponent.h"
#include "components/transform.h"

using namespace Engine;

class SceneLayer : public Layer
{
public:
	SceneLayer(const char * name);
	void onRender() override;
	void onUpdate(float timestep) override;
	void onKeyPressed(KeyPressedEvent& e) override;
	void onResize(WindowResizeEvent& e) override;
private:
	SceneWideUniforms m_swu;
	glm::vec3 lightData[3] = { {1.0f, 1.0f, 1.0f} , {-2.0f, 4.0f, 6.0f} , {0.0f, 0.0f, 0.0f} };
	
	std::vector<glm::mat4> m_transforms;

	std::shared_ptr<CameraController> m_currentCamera;
	std::shared_ptr<FreeEulerCamController> m_FPSCamera;
	
	std::shared_ptr<Material> pyramidMaterial;
	std::shared_ptr<Material> letterCubeMaterial;

	std::shared_ptr<Shaders> TPShader;
	std::shared_ptr<VertexArray> pyramidVAO;

	glm::vec3 m_position = { 5,0,-4 };
	float m_angle = 0.3f;

	// ??
	entt::registry m_registry;

};
