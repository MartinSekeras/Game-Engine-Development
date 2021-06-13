/** \file renderCommands.h */
#pragma once
#include <functional>

namespace Engine
{
	class RendererCommons;

	/** \class RenderCommands
	*	\brief Class to take Rendering Commands and can be used API agnostic within the main application.
	*/
	class RenderCommands
	{
	public:
		enum class Commands { clearDepthBuffer, clearColourBuffer, clearColourAndDepthBuffer, setClearColour,
								setglEnableDepthTest, setglDisableDepthTest, setglEnableBlend, setglDisableBlend, 
								setglBlendFunc };		//!< enum class to take types of commands.
	private:
		std::function<void(void)> m_action;		//!< action of the render command.
		friend class RenderCommandsFactory;		//!< coupled with friend RenderCommandFactory, as both won't work without the other.
		friend class RendererCommons;			//!< coupled with friend RendererCommons, as both will action commands from here.
	};

	/** \class RenderCommandsFactory
	*	\brief Class to store functions api agnostic commands for clearing things like buffers.
	*/
	class RenderCommandsFactory
	{
	public:
		template<typename ... Args> static RenderCommands* createCommand(RenderCommands::Commands command, Args&& ...args)
		{
			RenderCommands* result = new RenderCommands;		//raw pointer prevent ownership attached to the pointer; used instead of shared_ptr.

			switch (command)
			{
			case RenderCommands::Commands::clearColourAndDepthBuffer :
				result->m_action = getClearColourAndDepthBufferCommand();
				return result;

			case RenderCommands::Commands::setglEnableDepthTest : 
				result->m_action = getSetglEnableDepthTestCommand();
				return result;

			case RenderCommands::Commands::setglDisableDepthTest:
				result->m_action = getSetglDisableDepthTestCommand();
				return result;

			case RenderCommands::Commands::setglEnableBlend:
				result->m_action = getSetglEnableBlendCommand();
				return result;

			case RenderCommands::Commands::setglDisableBlend:
				result->m_action = getSetglDisableBlendCommand();
				return result;

			case RenderCommands::Commands::setglBlendFunc:
				result->m_action = getSetglBlendFuncCommand();
				return result;

			case RenderCommands::Commands::setClearColour :
				float r, g, b, a;

				//make tuple from parameter pack. Note - a tuple is not fixed in length.
				auto argTuple = std::make_tuple(args...);

				getValue<float, 0>(r, argTuple);
				getValue<float, 1>(g, argTuple);
				getValue<float, 2>(b, argTuple);
				getValue<float, 3>(a, argTuple);

				result->m_action = getSetClearColourCommand(r, g, b, a);
				return result;
			}
		}			//!< template with typename arguements; creates commands, with switch statements for command type and the action required for each.
	private:
		static std::function<void(void)> getClearColourAndDepthBufferCommand();	//!< function to clear colour and depth buffers.
		static std::function<void(void)> getSetglEnableDepthTestCommand();		//!< function to enable the GL depth test.
		static std::function<void(void)> getSetglDisableDepthTestCommand();		//!< function to disable the GL depth test.
		static std::function<void(void)> getSetglEnableBlendCommand();			//!< function to enable the GL blend.
		static std::function<void(void)> getSetglDisableBlendCommand();			//!< function to disable the GL blend.
		static std::function<void(void)> getSetglBlendFuncCommand();			//!< function to set the GL blend function.
		static std::function<void(void)> getSetClearColourCommand(float r, float g, float b, float a);		//!< command to clear colour, with float RBGA params.

		//following code based on https://www.geeksforgeeks.org/how-to-iterate-over-the-elements-of-an-stdtuple-in-c/		
		//check value I - if MORE OR EQUALSs number of values in tuple (size of parameter pack) then do nothing for these.
		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<I >= sizeof...(Ts), void>::type			
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			//if I is greater or equal to the size of the tuple; then don't do anything.
		}

		//check value I - if LESS than number of values in tuple (size of parameter pack) and get that thing.
		template <typename G, size_t I, typename... Ts>
		typename std::enable_if<(I < sizeof...(Ts)), void>::type
		static getValue(G& result, std::tuple<Ts...> tup)
		{
			//get the I-th thing within the tuple.
			result = std::get<I>(tup);
		}
	};
}