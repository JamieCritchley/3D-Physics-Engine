#include "ConvexMesh.h"

namespace PhysicsEngine::Actors::MeshActors
{

	//Unchanged from original, may be errors but currently don't understand code
	ConvexMesh::ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose, PxReal density) : DynamicActor(pose)
	{
		PxConvexMeshDesc mesh_desc;
		mesh_desc.points.count = (PxU32)verts.size();
		mesh_desc.points.stride = sizeof(PxVec3);
		mesh_desc.points.data = &verts.front();
		mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
		mesh_desc.vertexLimit = 256;

		CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
	}

	//Unchanged from original, may be errors but currently don't understand code
	PxConvexMesh* ConvexMesh::CookMesh(const PxConvexMeshDesc& mesh_desc)
	{
		PxDefaultMemoryOutputStream stream;

		if (!GetCooking()->cookConvexMesh(mesh_desc, stream))
			throw new Exception("ConvexMesh::CookMesh, cooking failed.");

		PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

		return GetPhysics()->createConvexMesh(input);
	}
}