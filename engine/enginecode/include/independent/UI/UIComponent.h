/* \file UIComponent.h */
//brief Used to create the UI
#pragma once
#include <glm/glm.hpp>


namespace Engine
{
	struct UIColourScheme
	{
		glm::vec4 background = { 0.0f, 0.4f, 0.6f, 1.0f };	//Blue
		glm::vec4 foreground = { 1.0f, 1.0f, 1.0f, 1.0f };	//White
		glm::vec4 highlight  = { 0.4f, 0.2f, 0.6f, 1.0f };
	};


	class UIComponent
	{
	public:
		glm::ivec2 getPosition() { return m_position; }
		glm::ivec2 getSize() { return m_size; }

		virtual void updateSize() = 0;
		virtual void updatePosition(glm::ivec2& relativePosition) = 0;
		virtual void onRender() const {};
		virtual void onMouseMove(glm::ivec2& mousePosition) {};
		virtual void onMousePress(glm::ivec2& mousePosition, int32_t button) {};
		virtual void onMouseRelease(glm::ivec2& mousePosition, int32_t button) {};
		void setParent(UIComponent* parent) { m_parent = parent; }
		UIComponent* getParent() const { return m_parent; }
		UIColourScheme* m_colourScheme = nullptr;

	protected:
		glm::ivec2 m_position;
		glm::ivec2 m_size;
		UIComponent* m_parent = nullptr;
	};
}