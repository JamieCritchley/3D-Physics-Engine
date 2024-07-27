#pragma once

#include "StaticActor.h"


namespace PhysicsEngine::ActorTemplates::MeshActors
{
	//Wrapper for a user-defined triangle mesh object. This allows the creation of complex shapes.
	//Inherits from StaticActor class as triangle meshes are too computationally demanding for dynamic rigidbody collisions.
	class TriangleMesh : public StaticActor
	{

	private:

		//mesh cooking (helper function)
		PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc);


	public:
		// Triangle Mesh with some optional default parameters:
		// - verticies (required)
		// - triangles (required)
		// - pose in 0,0,0
		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, 
			const PxTransform& pose = PxTransform(PxIdentity));

	};

}