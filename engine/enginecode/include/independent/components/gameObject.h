//#pragma once
//
//#include "events/events.h"
////#include "events/codes.h"
////#include "events/eventHeaders.h"
//#include "component.h"
//#include <vector>
//#include <memory>
//
//// An entity "gameobject" can just be a unique identifier
//// Components can be stored in associative or direct access containers
//// Systems retrieve components and perform so process on them
//
//// Dense and sparse set?
//namespace Engine
//{
//	// 
//	class GameObject
//	{
//	protected:
//		std::vector<std::shared_ptr<Component>> m_components;
//	public:
//		void onUpdate(float timestep);
//		void onEvent(Event& e);
//		void addComponent(const std::shared_ptr<Component>& comp);
//		void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter);
//
//		template<typename G>
//		std::vector<std::shared_ptr<Component>>::iterator getComponent()
//		{
//			auto result = m_components.end();
//			for (auto it = m_components.begin(); it != m_components.end(); ++it)
//			{
//				if (typeid(decltype(*(it->get()))).hash_code() == typeid(G).hash_code()) return it;
//			}
//			return result;
//		}
//
//		inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
//		inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
//	};
//}

