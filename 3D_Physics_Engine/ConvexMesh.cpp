#include "ConvexMesh.h"

namespace PhysicsEngine::ActorTemplates::MeshActors
{

	ConvexMesh::ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose, PxReal density) : DynamicActor(pose)
	{
		//Descriptor containing input data for mesh object creation
		PxConvexMeshDesc mesh_desc;
		mesh_desc.points.count = (PxU32)verts.size();
		mesh_desc.points.stride = sizeof(PxVec3);
		mesh_desc.points.data = &verts.front();
		mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
		mesh_desc.vertexLimit = 256;

		CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
	}


	PxConvexMesh* ConvexMesh::CookMesh(const PxConvexMeshDesc& mesh_desc)
	{
		PxDefaultMemoryOutputStream stream;

		//Checks for successful mesh cooking. Currently unsure if exception is correctly handled - may need to revist
		if (!GetCooking()->cookConvexMesh(mesh_desc, stream))
			throw new Exception("ConvexMesh::CookMesh, cooking failed.");

		PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

		return GetPhysics()->createConvexMesh(input);
	}
}