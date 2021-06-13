/** \file graphicsContext.h */
#pragma once

namespace
{
	/* \class GraphicsContext
	*  \brief Short class to initiate which graphics context it is and swap the buffers for double buffering.
	*/
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default; //!< Destructor
		virtual void init() = 0;		//!< initiate the graphics context for the given windowing API
		virtual void swapBuffers() = 0;	//!< to swap the front and back buffers (aka double buffering).
		virtual void updateViewport(int32_t width, int32_t height) = 0; //!< Update the viewport after window resize
	private:

	};
}
