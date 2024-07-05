#pragma once

#include "DynamicActor.h"

namespace PhysicsEngine::Actors::MeshActors
{

	//Wrapper for a user-defined convex mesh object. This allows the creation of complex shapes. 
	//Only vertices are necessary for computation, with the hull being automatically created.
	//Inherits from DynamicActor class to contrast the static TriangleMesh class, as dynamic triangle meshes are too expensive.
	//More research needed for the differences between static convex vs triangle meshes.
	class ConvexMesh : public DynamicActor
	{

	private:

		//mesh cooking (helper function)
		PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc);

	public:

		// Convex Mesh with some optional default parameters:
		// - verticies (required)
		// - pose in 0,0,0
		// - denisty: 1kg/m^3
		ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose = PxTransform(PxIdentity), PxReal density = 1.f);

	};

}