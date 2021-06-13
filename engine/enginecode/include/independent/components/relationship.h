/* \file Relationship.h */
#pragma once

#include <entt/entt.hpp>


namespace Engine
{
	class RootComponent
	{
	public:
	};

	class RelationshipComponent
	{
	// Single linked list for relationship

	public:
		std::size_t children = 0;
		entt::entity first = entt::null;
		entt::entity next = entt::null;
		entt::entity parent = entt::null;
	};

	namespace HierarchySystem
	{
		void setChild(entt::entity& parentEntity, entt::entity& childEntity);
		void updateChildren();
	}
}