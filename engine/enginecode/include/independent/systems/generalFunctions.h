/** \file generalFunctions.h */
#pragma once

#include <glm/glm.hpp>
#include <array>

namespace Engine
{
	/**	\class GenFuncs
	*	\brief Class to take a group of general functions that are used throughout the program.
	*/
	class GenFuncs
	{
	public:
		static std::array<int16_t, 3> normalise(const glm::vec3& norm);		//!< normalise vec3
		static std::array<int16_t, 2> normalise(const glm::vec2& uv);		//!< normalise vec2
		uint32_t package(const glm::vec4& colour);						//!< package vec4
		uint32_t package(const glm::vec3& colour)	
		{
			return package({ colour.x, colour.y, colour.z, 1.0f });
		}																//!< package vec3
	private:

	};
}