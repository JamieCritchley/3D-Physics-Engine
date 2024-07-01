#pragma once

#include "PhysicsEngine.h"

//Taken from week 3

namespace PhysicsEngine::Joints {

	///Generic Joint class
	class Joint
	{
	protected:
		PxJoint* joint;

	public:
		Joint();

		PxJoint* Get();
	};
}


