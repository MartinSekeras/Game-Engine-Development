/* \file events.h */
#pragma once
#include <intTypes.h>

namespace Engine
{
	/** \enum EventType
	*	\brief An enum class for all the event types. Using the class type as safer than plain enum.
	*/
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
		KeyPress, KeyRelease, KeyType,
		MouseMovement, MouseScroll, MouseButtonPress, MouseButtonRelease
	};

	/** \enum EventCategory
	*	\brief An enum for type category flags. An older plain classical version of enum use bitshifting/operators. As something can belong to more than one category, can use flags.
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,		//!< 00000001
		EventCategoryInput = 1 << 1,		//!< 00000010
		EventCategoryKey = 1 << 2,			//!< 00000100
		EventCategoryMouse = 1 << 3,		//!< 00001000
		EventCategoryButton = 1 << 4		//!< 00010000
	};

	/** \class Event
	*	\brief Base class for Event.
	*/
	class Event
	{
	public:
		virtual EventType getEventType() const = 0;			//!< get the event type, deferring implementation of this.
		virtual int32_t getCategoryFlag() const = 0;		//!< get the event category, deferring implementation of this.
		inline bool isEventHandled() const { return m_eventHandled; }				//!< has the event in question been handled.
		inline void handleEvent(bool isHandled) { m_eventHandled = isHandled; }		//!< handle the relevant event.
		inline bool isEventInCategory(EventCategory category) const { return getCategoryFlag() & category; }	//!< is this event in a category?
	protected:
		bool m_eventHandled = false;	//!< has the event been handled.
	};

}
