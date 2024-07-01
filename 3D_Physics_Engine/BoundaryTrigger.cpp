#include "BoundaryTrigger.h"

namespace PhysicsEngine::AssignmentScene {

	BoundaryTrigger::BoundaryTrigger(PxTransform pos, PxVec3 dimensions): StaticActor(pos)
	{

		CreateShape(PxBoxGeometry(dimensions/2), 0);
		
		SetTrigger(true);
	}
}
