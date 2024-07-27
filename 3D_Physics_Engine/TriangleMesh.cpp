#include "TriangleMesh.h"

namespace PhysicsEngine::ActorTemplates::MeshActors
{

	TriangleMesh::TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, 
		const PxTransform& pose) : StaticActor(pose)
	{
		//Descriptor containing input data for mesh object creation
		PxTriangleMeshDesc mesh_desc;
		mesh_desc.points.count = (PxU32)verts.size();
		mesh_desc.points.stride = sizeof(PxVec3);
		mesh_desc.points.data = &verts.front();
		mesh_desc.triangles.count = (PxU32)trigs.size() / 3;
		mesh_desc.triangles.stride = 3 * sizeof(PxU32);
		mesh_desc.triangles.data = &trigs.front();

		CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)),0);
	}


	PxTriangleMesh* TriangleMesh::CookMesh(const PxTriangleMeshDesc& mesh_desc)
	{
		PxDefaultMemoryOutputStream stream;

		//Checks for successful mesh cooking. Currently unsure if exception is correctly handled - may need to revist
		if (!GetCooking()->cookTriangleMesh(mesh_desc, stream))
			throw new Exception("TriangleMesh::CookMesh, cooking failed.");

		PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

		return GetPhysics()->createTriangleMesh(input);
	}
}
