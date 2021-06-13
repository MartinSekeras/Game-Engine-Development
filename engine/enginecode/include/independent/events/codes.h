/** \file codes.h */
#pragma once

#ifndef NG_PLATFORM_WINDOWS
	#include "platform/windows/win32Codes.h"
#else
	#include "platform/GLFW/GLFWCodes.h"
#endif //NG_PLATFORM_WINDOWS