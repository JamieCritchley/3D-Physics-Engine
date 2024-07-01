#include "Joint.h"

namespace PhysicsEngine::Joints {

	Joint::Joint() : joint(0) {}

	PxJoint* Joint::Get() { return joint; }
}