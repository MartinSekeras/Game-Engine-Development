/* UILayer.h */

// TOOL
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace Engine;
enum class UILayerState { InActive, Activating, Active, Deactivating };

class UILayer : public Layer
{
public:
	UILayer(const char* name);
	void onRender() override;
	UILayerState getState() { return m_state; }

	virtual void onKeyPressed(KeyPressedEvent& e) override;
	virtual void onMouseMove(MouseMovementEvent& e) override;
	virtual void onMousePress(MouseButtonPressEvent& e) override;
	virtual void onMouseRelease(MouseButtonReleaseEvent& e) override;

private:
	std::shared_ptr<FreeOthroCamController> m_camera;
	SceneWideUniforms m_swu;
	ModalWindow m_window;
	UILayerState m_state = UILayerState::Activating;
	std::vector<Quad> m_quads;
};
