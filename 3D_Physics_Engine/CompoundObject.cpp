#include "CompoundObject.h"

namespace PhysicsEngine::CustomScene
{
	CompoundObject::CompoundObject(PxVec3 boxDimensions) : DynamicActor(PxTransform(PxVec3(0, 10, 0)))
	{

		//Boexs are 1x1 with density of 1
		CreateShape(PxBoxGeometry(boxDimensions), PxReal(1));
		CreateShape(PxBoxGeometry(boxDimensions), PxReal(1));

		//Move second box so they are adjacent (sets local position, relative to transform in DynamicActor constructor
		GetShape(0)->setLocalPose(PxTransform(PxVec3(boxDimensions.x, 0, 0)));
		GetShape(1)->setLocalPose(PxTransform(PxVec3(-boxDimensions.x, 0, 0)));
	}
}
