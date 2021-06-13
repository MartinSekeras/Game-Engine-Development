/* \file keyEvents.h */
#pragma once

#include "events.h"
#include <glm/glm.hpp>

namespace Engine
{
	/** \class KeyEvent
	*	\brief A class to take a number of funcs and vars that will be common in all key event classes.
	*/
	class KeyEvent : public Event
	{
	public:
		inline int32_t getKeycode() const { return m_keycode; }				//!< get the keycode that has been pressed.
		virtual inline int32_t getCategoryFlag() const override { return EventCategoryKey | EventCategoryInput; }	//!< get the category flag/s for the event.
	protected:
		KeyEvent(int32_t keycode) : m_keycode(keycode) {}		//!< get the keycode.
		int32_t m_keycode;		//!< int32_t to take keycode int.
	};

	/** \class KeyPressedEvent 
	*	\brief A class for key pressed event.
	*/
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const int32_t keycode, const int32_t keycount) : KeyEvent(keycode), m_repeatCount(keycount) {}	//!< initialiser, listed params straight to m_keycode & m_repeatCount.
		static EventType getStaticType() { return EventType::KeyPress; }	//!< get the static event type, can use to compare.
		virtual inline EventType getEventType() const override { return  getStaticType(); }			//!< get the event type.
		inline int32_t getRepeatCount() const { return m_repeatCount; }		//!< get the count if key press repeated.
	private:
		int32_t m_repeatCount;		//!< int32_t to take the count of repeated input.
	};

	/** \class KeyReleasedEvent
	*	\brief A class for key released event.
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int32_t keycode) : KeyEvent(keycode) {}		//!< initialiser, listed params straight to m_keycode.
		static EventType getStaticType() { return EventType::KeyRelease; }	//!< get the static event type, can use to compare.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
	};

	/** \class KeyTypedEvent 
	*	\brief A class for key typing event.
	*/
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int32_t keycode) : KeyEvent(keycode) {}			//!< initialiser, listed param straight to m_keycode.
		static EventType getStaticType() { return EventType::KeyType; }		//!< get the static event type, can use to compare.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
	};
}