#pragma once

#include "core/application.h"
#include <glm/gtc/type_ptr.hpp>
#include "reactphysics3d/collision/CollisionCallback.h"



namespace Engine
{
	class EventListener : public rp3d::EventListener 
	{
	public:

		virtual void onContact(const CollisionCallback::CallbackData& callbackData) override;
		void onTrigger(); // Like begin contact but with triggers

		void offContact();

	private:

	};
}
