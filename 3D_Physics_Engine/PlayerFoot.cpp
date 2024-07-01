#include "PlayerFoot.h"

namespace PhysicsEngine::AssignmentScene {

	PlayerFoot::PlayerFoot(PxTransform pos) : DynamicActor(pos) {

		CreateShape(PxBoxGeometry(.05, 0.2032, .05), 1010.0f); //Lower leg
		CreateShape(PxBoxGeometry(.0525, .02, .14), 1010.0f); //Foot

		//Set local pos
		GetShape(0)->setLocalPose(PxTransform(PxVec3(0, -0.2032, 0))); //Lower leg
		GetShape(1)->setLocalPose(PxTransform(PxVec3(0, -0.4264, .09))); //Foot
	}
}