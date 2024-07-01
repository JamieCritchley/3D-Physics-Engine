#include "ExtrudedHexagon.h"

namespace PhysicsEngine::CustomScene
{
	ExtrudedHexagon::ExtrudedHexagon(PxReal sideLength, PxReal height, PxTransform pose, PxReal density)
		//Verts are ordered by bottom hexagon, then top hexagon of prism
		: ConvexMesh(vector < PxVec3>{PxVec3(sideLength, 0, 0), PxVec3(-sideLength, 0, 0), PxVec3(sideLength / 2, 0, sideLength), //Bottom hexagon
			PxVec3(sideLength / 2, 0, -sideLength), PxVec3(-sideLength / 2, 0, -sideLength), PxVec3(-sideLength / 2, 0, sideLength), //Bottom hexagon
			PxVec3(sideLength, height, 0), PxVec3(-sideLength, height, 0), PxVec3(sideLength / 2, height, sideLength), //Top hexagon
			PxVec3(sideLength / 2, height, -sideLength), PxVec3(-sideLength / 2, height, -sideLength), PxVec3(-sideLength / 2, height, sideLength)}, //Top hexagon
			pose, density)//Rest of constructor

	{}
}