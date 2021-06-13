/** \file FCVertex.h */
#pragma once

#include "rendering/bufferLayout.h"
#include <glm/glm.hpp>

namespace Engine
{
	/* when done properly need three classes for final engine;
	* one for 2d rendering - 2d vertices,
	* one for static 3d vertices,
	* one for animated 3d vertices. */


	/** \class FCVertex
	*	\brief Class that deals with the flat colour (FC) layout.
	*/
	class FCVertex : public VertexBufferLayout
	{
	public:
		FCVertex() : 
			m_position(glm::vec3(0.0f)), 
			m_colour(glm::vec3(0.0f)) 
		{}	//!< constructor with position & colour initialised.
		FCVertex(const glm::vec3& pos, const glm::vec3& col) : 
			m_position(pos), 
			m_colour(col) 
		{}	//!< constructor, passing by reference, colour just a vec3.
		FCVertex(const glm::vec3& pos, const glm::vec4& col_a) :
			m_position(pos),
			m_colour_a(col_a)
		{}	//!< constructor, passing by reference, colour a *VEC4* so takes the alpha as well.
		
		static VertexBufferLayout getLayout() { return s_layout; }		//!< accessor to get the layout.

		glm::vec3 m_position;					//!< vec3 for position.
		glm::vec3 m_colour;						//!< vec3 for colour.
		glm::vec4 m_colour_a;					//!< vec4 for colour with alpha.
	private:
		static VertexBufferLayout s_layout;		//!< the layout for a vertex buffer.
	};

	/*	\class TPVertexNormalised
	*	\brief A class that normalises the normal and uv with reduced data size for efficiency.
	*/
	class TPVertexNormalised
	{
	public:
		TPVertexNormalised() :
			m_position(glm::vec3(0.0f)),
			m_normalise({ 0, 0, 0 }),
			m_UVcoords({ 0, 0 })
		{};		//!< default constructor, initalising values to 0.

		TPVertexNormalised(const glm::vec3& position, const std::array<int16_t, 3> normal, const std::array<int16_t, 2> uv) :
			m_position(position),
			m_normalise(normal),
			m_UVcoords(uv)
		{};		//!< constructor with params for a textured phong, position, normal values and UV coordinates.

		glm::vec3 m_position;					//!< vec3 to take position of vertex.
		std::array<int16_t, 3> m_normalise; 	//!< short var to take normalised values. Array used as very easy to pass back arrays from functions.
		std::array<int16_t, 2> m_UVcoords;		//!< short var to take UV coordinate values. Array used as very easy to pass back arrays from functions.

		inline VertexBufferLayout static getBufferLayout() { return s_BufferLayout; }		//!< accessor function to get the static buffer layout.
	private:
		static VertexBufferLayout s_BufferLayout;
	};
}