/* \file KeyControllers.h */
#pragma once

#include <stdint.h>
#include "events/codes.h"

namespace Engine
{
	class KeyTranslationControllerComponent
	{
	public:
		KeyTranslationControllerComponent() = default;
		KeyTranslationControllerComponent(uint32_t flags) { movementFlags = flags; }
		int32_t forwardKey = NG_KEY_W;
		int32_t leftKey = NG_KEY_A;
		int32_t backKey = NG_KEY_S;
		int32_t rightKey = NG_KEY_D;
		int32_t rollUpKey = NG_KEY_Q;
		int32_t rollDownKey = NG_KEY_E;
		int32_t yawUpKey = NG_KEY_LEFT;
		int32_t yawDownKey = NG_KEY_RIGHT;
		int32_t pitchUpKey = NG_KEY_UP;
		int32_t pitchDownKey = NG_KEY_DOWN;
		uint32_t movementFlags;
		
		static const uint32_t forwardBackFlag = 1 < 0;
		static const uint32_t leftRightFlag = 1 << 1;
		static const uint32_t rollFlag = 1 << 2;
		static const uint32_t pitchFlag = 1 << 3;
		static const uint32_t yawFlag = 1 << 4;
		static const uint32_t stdNoRotationFlags = forwardBackFlag | leftRightFlag;
		static const uint32_t stdWithRotationFlags = forwardBackFlag | leftRightFlag | rollFlag | pitchFlag | yawFlag;

		bool isSet(uint32_t flags)
		{
			return flags & movementFlags;
		}

	};
}
