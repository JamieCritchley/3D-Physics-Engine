#include "CompoundCapsuleObject.h"

namespace PhysicsEngine::CustomScene
{
	CompoundCapsuleObject::CompoundCapsuleObject(PxReal height, PxReal radius) 
		: DynamicActor(PxTransform(0, radius ,0, PxQuat(PxPi/2, PxVec3(1,0,0))))//Rotated 90 degrees around z axis to make capsules "lie down"
	{
		//Creates shapes and sets local pos
		CreateShape(PxCapsuleGeometry(radius, height/2), PxReal(1));
		CreateShape(PxCapsuleGeometry(radius, height / 2), PxReal(1));
		CreateShape(PxCapsuleGeometry(radius, height / 2), PxReal(1));
		CreateShape(PxCapsuleGeometry(radius, height / 2), PxReal(1));

		//Local pos adjusted for changes to actor pos
		GetShape(0)->setLocalPose(PxTransform(PxVec3(height * 2, 0, 0)));
		GetShape(1)->setLocalPose(PxTransform(PxVec3(-height * 2, 0, 0)));

		//Need to make "top" and "bottom" capsules point away from center
		GetShape(2)->setLocalPose(PxTransform(PxVec3(0, height * 2, 0), PxQuat(PxPi/2, PxVec3(0,0,1))));
		GetShape(3)->setLocalPose(PxTransform(PxVec3(0, -height * 2, 0), PxQuat(PxPi / 2, PxVec3(0, 0, 1))));

		

	}
}
