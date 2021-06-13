/** \file generalFunctions.cpp */

#include "engine_pch.h"
#include "systems/generalFunctions.h"

namespace Engine
{
	std::array<int16_t, 3> GenFuncs::normalise(const glm::vec3 & norm)
	{
		std::array<int16_t, 3> result;

		//do x first.
		if (norm.x == 1.0)
			result.at(0) = INT16_MAX;
		else if (norm.x == -1.0)
			result.at(0) = INT16_MIN;
		else
			result.at(0) = static_cast<int16_t>(norm.x * static_cast<float>(INT16_MAX));

		//now y
		if (norm.y == 1.0)
			result.at(1) = INT16_MAX;
		else if (norm.y == -1.0)
			result.at(1) = INT16_MIN;
		else
			result.at(1) = static_cast<int16_t>(norm.y * static_cast<float>(INT16_MAX));

		//and now z
		if (norm.z == 1.0)
			result.at(2) = INT16_MAX;
		else if (norm.z == -1.0)
			result.at(2) = INT16_MIN;
		else
			result.at(2) = static_cast<int16_t>(norm.z * static_cast<float>(INT16_MAX));

		//finally, return the result.
		return result;
	}

	std::array<int16_t, 2> GenFuncs::normalise(const glm::vec2 & uv)
	{
		std::array<int16_t, 2> result;

		//do x first.
		if (uv.x == 1.0)
			result.at(0) = INT16_MAX;
		else if (uv.x == -1.0)
			result.at(0) = INT16_MIN;
		else
			result.at(0) = static_cast<int16_t>(uv.x * static_cast<float>(INT16_MAX));

		//now y
		if (uv.y == 1.0)
			result.at(1) = INT16_MAX;
		else if (uv.y == -1.0)
			result.at(1) = INT16_MIN;
		else
			result.at(1) = static_cast<int16_t>(uv.y * static_cast<float>(INT16_MAX));

		//finally, return the result.
		return result;
	}

	uint32_t GenFuncs::package(const glm::vec4 & colour)
	{
		//int to return the result, initialised to 0.
		uint32_t result = 0;

		//vars for each of the colour channels; R, G, B & A.
		//converting them from 0-1 to 0-255, static casting from float to uint32_T
		uint32_t r = (static_cast<uint32_t>(colour.r * 255.0f)) << 0;	//bytewise - 000R
		uint32_t g = (static_cast<uint32_t>(colour.g * 255.0f)) << 8;	//00B0
		uint32_t b = (static_cast<uint32_t>(colour.b * 255.0f)) << 16;	//0G00
		uint32_t a = (static_cast<uint32_t>(colour.a * 255.0f)) << 24;	//A000

		result = (r | g | b | a);
		return result;
	}
}