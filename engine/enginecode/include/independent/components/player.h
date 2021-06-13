#pragma once
#include <reactphysics3d/reactphysics3d.h>

namespace Engine
{
	/** \class Player
	*	\brief Class that holds player component attached to the player cube.
	*/
	class Player
	{
	public:
		Player::Player(rp3d::RigidBody* body); 
		void onUpdate(float time);
	private:
		rp3d::RigidBody* m_body;
	};
}
