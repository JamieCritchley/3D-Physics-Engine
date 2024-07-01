#pragma once

#include "DynamicActor.h"

namespace PhysicsEngine::Actors::MeshActors
{
	class ConvexMesh : public DynamicActor
	{

	protected:

		//mesh cooking (helper function)
		PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc);

	public:

		//a Convex Mesh with some optional default parameters:
		// - verticies (required)
		// - pose in 0,0,0
		// - denisty: 1kg/m^3
		ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose = PxTransform(PxIdentity), PxReal density = 1.f);

	};

}