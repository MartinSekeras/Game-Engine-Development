/* \file windowEvents.h */
#pragma once
#include "events.h"
#include <glm/glm.hpp>

namespace Engine
{
	/** \class WindowEvent
	*	\brief A class to take a number of funcs and vars that will be common in all window event classes.
	*/
	class WindowEvent : public Event
	{
	public:
		virtual inline int32_t getCategoryFlag() const override { return EventCategoryWindow; }	//!< get the category flag for the event.
	};

	/** \class WindowCloseEvent 
	*	\brief A class for window closing event.
	*/
	class WindowCloseEvent : public WindowEvent
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; }						//!< returns static type; reason for static type is that is gives me something to compare with when implementing a handler.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
	};

	/** \class WindowResizeEvent 
	*	\brief A class for resizing window event.
	*/
	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) { }	//!< using initaliser list as will set width/height straight to m_width/m_height rather than to 0 first.
		static EventType getStaticType() { return EventType::WindowResize; }					//!< returns static type; reason for static type is that is gives me something to compare with when implementing a handler.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
		inline int32_t getWidth() const { return m_width; }		//!< get the width of window.
		inline int32_t getHeight() const { return m_height; }	//!< get the height of window.
		inline glm::ivec2 getWindowSize() const { return glm::ivec2(m_width, m_height); }		//!< get the size of the window.
	private:
		int32_t m_width;		//!< window width after resize.
		int32_t m_height;		//!< window height after resize.
	};

	/** \class WindowFocusEvent 
	*	\brief A class for bringing window into focus event.
	*/
	class WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent() {}		//!< constructor.
		static EventType getStaticType() { return EventType::WindowFocus; }						//!< returns static type; reason for static type is that is gives me something to compare with when implementing a handler.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
	};

	/** \class WindowLostFocusEvent
	*	\brief A class for minimising window out of focus event.
	*/
	class WindowLostFocusEvent : public WindowEvent
	{
	public:
		WindowLostFocusEvent() {}	//!< constructor.
		static EventType getStaticType() { return EventType::WindowLostFocus; }					//!< returns static type; reason for static type is that is gives me something to compare with when implementing a handler.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
	};

	/** \class WindowMoveEvent 
	*	\brief A class for window movement event.
	*/
	class WindowMoveEvent : public WindowEvent
	{
	public:
		WindowMoveEvent(int32_t x, int32_t y) : m_winMoveX(x), m_winMoveY(y) {}					//!< initaliser, listed the x/y straight to windowMoveX/Y.
		static EventType getStaticType() { return EventType::WindowMove; }						//!< returns static type; reason for static type is that is gives me something to compare with when implementing a handler.
		virtual inline EventType getEventType() const override { return getStaticType(); }		//!< get the event type.
		inline int32_t getWindowXMove() { return m_winMoveX; }		//!< get the float for window movement on the X axis.
		inline int32_t getWindowYMove() { return m_winMoveY; }		//!< get the float for window movement on the Y axis.
		inline glm::ivec2 getWindowPosition() const { return glm::ivec2(m_winMoveX, m_winMoveY); }	//!< get the position of the window.
	private:
		int32_t m_winMoveX;		//!< int32_t for X position of window movement.
		int32_t m_winMoveY;		//!< int32_t for Y position of window movement.
	};
}