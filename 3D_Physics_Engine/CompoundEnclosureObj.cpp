#include "CompoundEnclosureObj.h"

namespace PhysicsEngine::CustomScene
{
	CompoundEnclosureObj::CompoundEnclosureObj(PxTransform pose, PxVec3 dimensions, PxReal thickness, PxReal density) : StaticActor(pose)
	{
		//Box uses half extents
		dimensions = dimensions / 2;
		thickness = thickness / 2;
		//Floor of enclosure
		CreateShape(PxBoxGeometry(PxVec3(dimensions.x, thickness, dimensions.z)), density);
		//Moved to bottom of shape
		GetShape(0)->setLocalPose(PxTransform(PxVec3(0, -dimensions.y, 0)));

		//Walls of enclosure
		CreateShape(PxBoxGeometry(PxVec3(thickness, dimensions.y, dimensions.z)), density);
		CreateShape(PxBoxGeometry(PxVec3(thickness, dimensions.y, dimensions.z)), density);
		//Moved to edge of floor
		GetShape(1)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0, 0)));
		GetShape(2)->setLocalPose(PxTransform(PxVec3(-dimensions.x, 0, 0)));


		//Walls of enclosure (other side)
		CreateShape(PxBoxGeometry(PxVec3(dimensions.x, dimensions.y, thickness)), density);
		CreateShape(PxBoxGeometry(PxVec3(dimensions.x, dimensions.y, thickness)), density);
		//Moved to edge of floor
		GetShape(3)->setLocalPose(PxTransform(PxVec3(0, 0, dimensions.z)));
		GetShape(4)->setLocalPose(PxTransform(PxVec3(0, 0, -dimensions.z)));


		//Roof of enclosure
		CreateShape(PxBoxGeometry(PxVec3(dimensions.x, thickness, dimensions.z)), density);
		//Moved to top of shape
		GetShape(5)->setLocalPose(PxTransform(PxVec3(0, dimensions.y, 0)));
	}
}