#include "DynamicActor.h"

namespace PhysicsEngine::ActorTemplates 
{
	DynamicActor::DynamicActor(const PxTransform& pose)
	{
		startingPos = pose;
		actor = (PxActor*)GetPhysics()->createRigidDynamic(pose);
		SetName("");
	}

	DynamicActor::~DynamicActor()
	{
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;
	}

	void DynamicActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = ((PxRigidDynamic*)actor)->createShape(geometry, *GetMaterial());
		PxRigidBodyExt::updateMassAndInertia(*(PxRigidDynamic*)actor, density);

		//Create a color pointer for the shape
		PxVec3* colorptr = new PxVec3;
		*colorptr = default_color;
		colors.push_back(colorptr);
		//Pass the color pointer to the renderer
		shape->userData = new UserData();
		((UserData*)shape->userData)->color = colors[colors.size() - 1];
	}

	void DynamicActor::SetKinematic(bool value)
	{
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
		((PxRigidDynamic*)actor)->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, value);
#else
		((PxRigidDynamic*)actor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
#endif

	}

	void DynamicActor::ResetPos() {
		PxRigidDynamic* rb = (PxRigidDynamic*)actor;
		rb->setGlobalPose(startingPos);
		rb->setLinearVelocity(PxVec3(0,0,0));
		rb->setAngularVelocity(PxVec3(0, 0, 0));
	}
}