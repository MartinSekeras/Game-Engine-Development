/* \file Relationship.cpp */
#include "engine_pch.h"
#include "components/relationship.h"
#include "components/transform.h"
#include "core/headerList.h"
#include "core/layer.h"


namespace Engine
{
	namespace HierarchySystem
	{
		void setChild(entt::entity& parentEntity, entt::entity& childEntity)
		{
			// m_registry ?????
			entt::registry& registry = Application::getInstance().m_registry;

			auto& parentComponent = registry.get<RelationshipComponent>(parentEntity);
			auto& childComponent = registry.get<RelationshipComponent>(childEntity);

			childComponent.parent = parentEntity;

			// Add child to parent
			if (parentComponent.children == 0)
			{
				parentComponent.children = 1;
				parentComponent.first = childEntity;
			}
			else
			{
				auto currentEntity = parentComponent.first;
				for (int i = 0; i < parentComponent.children; i++)
				{
					currentEntity = registry.get<RelationshipComponent>(currentEntity).next;
				}
				auto& currentComponent = registry.get<RelationshipComponent>(currentEntity);
				currentComponent.next = childEntity;
				parentComponent.children++;
			}
		}

		void updateChildren() // Might need change with parameter (child) that takes entity and updates children for that entity and then in the first pass update all the children in the root
		{
			entt::registry&	registry = Application::getInstance().m_registry;
			auto view = registry.view<RelationshipComponent, TransformComponent>(entt::exclude<RootComponent>);
			for (auto entity : view)
			{
				auto& relationship = registry.get<RelationshipComponent>(entity);
				auto& transform = registry.get<TransformComponent>(entity);

				if (relationship.parent != entt::null)
				{
					auto& parentTransform = registry.get<TransformComponent>(relationship.parent);
					transform.updateTransform(parentTransform.getTransform());
				}

			}
		}
	}
}