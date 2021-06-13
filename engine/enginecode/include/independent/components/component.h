//#pragma once
//#include <any> // The class any describes a type-safe container for single values of any type.
//#include "gameObject.h"
//#include "events/events.h"
//#include "events/codes.h"
//
//namespace Engine
//{
//	enum class ComponentMessageType
//	{
//		None = 0,
//		PositionIntegrate, PositionSet, RelativePositionSet,
//		VelocityIntegrate, VelocitySetLinear, VelocitySetAngular,
//		AccelerationSet,
//		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved,
//		UniformSet, TextureSet
//	};
//
//	class ComponentMessage
//	{
//	public:
//		ComponentMessage(ComponentMessageType type, std::any data) : m_msgType(type), m_msgData(data) {};
//		ComponentMessageType m_msgType; //!< Message type
//		std::any m_msgData; //!< Data associated with the message
//
//	};
//
//	class Component
//	{
//	protected:
//		GameObject* m_owner = nullptr;
//
//		virtual void sendMessage(const ComponentMessage& msg);
//	public:
//		virtual void onAttach(GameObject* owner) { m_owner = owner; };
//		virtual void onDetach() { m_owner = nullptr; };
//		virtual void onUpdate(float timestep) {};
//		virtual void onEvent(Event& e) {};
//		virtual void receiveMessage(const ComponentMessage& msg) = 0;
//	};
//
////}