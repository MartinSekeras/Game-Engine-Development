#include "engine_pch.h"
#include "core/application.h"
#include "components/physics.h"
#include "components/transform.h"
namespace Engine
{

}


void Engine::NGPhysicsSystem::updateTransform()
{
	auto& registry = Application::getInstance().m_registry;

	auto view = registry.view<TransformComponent, RigidBodyComponent>();

	for (auto entity : view)
	{
		auto& rb = registry.get<RigidBodyComponent>(entity);
		auto& transComp = registry.get<TransformComponent>(entity);

		auto& rbR = rb.m_body->getTransform().getOrientation();
		auto& rbP = rb.m_body->getTransform().getPosition();
		glm::quat r(rbR.w, rbR.x, rbR.y, rbR.z);
		glm::vec3 t(rbP.x, rbP.y, rbP.z);

		transComp.setTransform(t, r, transComp.scale);
	}
}
