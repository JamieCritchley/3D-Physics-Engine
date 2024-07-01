#pragma once

#include "ConvexMesh.h"
#include <vector>

namespace PhysicsEngine::CustomScene
{
	class DynamicWedge : public Actors::MeshActors::ConvexMesh
	{
	private:
		
		vector<PxVec3> verts;

	public:

		//Wedge shape initialised with optional params:
		//Transform (default is 0,height,0)
		//Density (default is 1)
		DynamicWedge(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f);

	};
}
