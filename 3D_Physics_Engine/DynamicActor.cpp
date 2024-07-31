#include "DynamicActor.h"

namespace PhysicsEngine::ActorTemplates 
{
	DynamicActor::DynamicActor(const PxTransform& pose)
	{
		startingPos = pose;
		//As this function creates a PxRigidDynamic, downasts to PxRigidDynamic can be used safetly (e.g in CreateShape function)
		actor = GetPhysics()->createRigidDynamic(pose);
		SetName("");
	}

	DynamicActor::~DynamicActor()
	{
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;

		//Calls interface for actor's destructor
		actor->release();
	}

	void DynamicActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = actor->createShape(geometry, *GetMaterial());
		PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidDynamic*>(actor), density);

		//Create a color pointer for the shape
		colors.push_back(std::make_unique<PxVec3>(default_color));
		//Pass the color pointer to the renderer
		shape->userData = new UserData();
		((UserData*)shape->userData)->color = colors[colors.size() - 1].get();
	}

	void DynamicActor::SetKinematic(bool value)
	{
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
		((PxRigidDynamic*)actor)->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, value);
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