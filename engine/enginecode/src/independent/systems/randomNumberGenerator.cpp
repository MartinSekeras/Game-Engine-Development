/** filr randomNumberGenerator.cpp */
#pragma once

#include "engine_pch.h"
#include "systems/randomNumberGenerator.h"
#include <chrono>

namespace Engine
{
	//initialising...
	//setting shared pointer to nullptrs.
	std::shared_ptr<std::mt19937> RandomNumberGenerator::s_generator = nullptr;
	
	//setting the number distributors between min and max of int32.
	std::uniform_int_distribution<int32_t> RandomNumberGenerator::s_uniformInt = std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
	std::uniform_real_distribution<float> RandomNumberGenerator::s_uniformFloat = std::uniform_real_distribution<float>(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
	
	//setting the ranges for int and float from max and min of their 32bit numeric limits.
	float RandomNumberGenerator::s_intRange = static_cast<float>(std::numeric_limits<int32_t>::max() - std::numeric_limits<int32_t>::min());
	float RandomNumberGenerator::s_floatRange = std::numeric_limits<float>::max() - std::numeric_limits<float>::min();


	void RandomNumberGenerator::start(SystemSignal init, ...)
	{
		//when start, need to seed random number generator.
		//will reset the generator using the time now.
		auto timeNow = std::chrono::high_resolution_clock::now();
		s_generator.reset(new std::mt19937(timeNow.time_since_epoch().count()));
	}

	void RandomNumberGenerator::stop(SystemSignal close, ...)
	{
		s_generator.reset();
	}

	int32_t RandomNumberGenerator::uniformIntBetween(int32_t min, int32_t max)
	{
		//***PROBLEM HERE*** result is always NEGATIVE!!!
		return min + (fabs(static_cast<float>(s_uniformInt(*s_generator))) / s_intRange) * (max - min);
	}

	float RandomNumberGenerator::uniformFloatBetween(float min, float max)
	{
		//***NOTE*** - very similar uniformIntBetween() BUT DOES NOT HAVE THE SAME PROBLEM??? Look into!
		return min + (fabs(s_uniformFloat(*s_generator)) / s_floatRange) * (max - min);
	}

	int32_t RandomNumberGenerator::normalIntBetween(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return static_cast<int32_t>(distribution(*s_generator));
	}

	float RandomNumberGenerator::normalFloatBetween(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return distribution(*s_generator);
	}
}