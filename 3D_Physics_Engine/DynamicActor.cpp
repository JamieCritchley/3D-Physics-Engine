#include "DynamicActor.h"

namespace PhysicsEngine::ActorTemplates 
{
	DynamicActor::DynamicActor(const PxTransform& pose): Actor(GetPhysics()->createRigidDynamic(pose)), startingPos(pose) {}

	void DynamicActor::CreateShapeHelper(const PxGeometry& geometry, PxReal density)
	{
		shapeDensities.push_back(density);
		//Set mass and intertia tensor(matrix)
		//Vector used to store values as PxShape class does not store densities. As this is the only context in which shape density
		//is necessary, it seemed unecessary to create a dedicate PxShape wrapper.
		//Note - array pointer not stored for further use by function, so vector address used
		PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidBody*>(actor), &shapeDensities[0], shapeDensities.size());
	}

	void DynamicActor::SetKinematic(const bool& value)
	{
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
		static_cast<PxRigidDynamic*>(actor)->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, value);
#else
		static_cast<PxRigidDynamic*>(actor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
#endif

	}

	void DynamicActor::ResetPos() {
		PxRigidDynamic* rb = static_cast<PxRigidDynamic*>(actor);
		rb->setGlobalPose(startingPos);
		rb->setLinearVelocity(PxVec3(0,0,0));
		rb->setAngularVelocity(PxVec3(0, 0, 0));
	}
}