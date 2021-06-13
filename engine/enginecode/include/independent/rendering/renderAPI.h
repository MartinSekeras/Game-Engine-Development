/** \file renderAPI.h */
#pragma once


namespace Engine
{
	/** \class RenderAPI
	*	\brief API agnostic class, dealing with which rendering API being used.
	*/
	class RenderAPI
	{
	public:
		enum class API {None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3};		//!< enum class required graphics API.
		inline static API getAPI() { return s_API; };		//!< function to get the current API.
	private:
		static API s_API;	//!< current API. NOTE: static so needs to be initialised outside the class, so need a .cpp just for this...
	};
}
