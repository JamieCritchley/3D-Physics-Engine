#include "DynamicWedge.h"

namespace PhysicsEngine::CustomScene
{
	DynamicWedge::DynamicWedge(PxTransform pose, PxReal density) 
		: ConvexMesh(vector<PxVec3>{PxVec3(1, 1, 0), PxVec3(0, 1, 1), PxVec3(1, 0, 0), PxVec3(-1, 0, 0), PxVec3(0, 0, 1), PxVec3(0, 0, -1)}, pose, density) {}
}