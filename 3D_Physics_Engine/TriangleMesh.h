#pragma once

#include "StaticActor.h"


namespace PhysicsEngine::Actors::MeshActors
{

	class TriangleMesh : public StaticActor
	{

	protected:

		//mesh cooking (helper function)
		PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc);


	public:
		//a Convex Mesh with some optional default parameters:
		// - verticies (required)
		// - triangles (required)
		// - pose in 0,0,0
		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, 
			const PxTransform& pose = PxTransform(PxIdentity));

	};

}