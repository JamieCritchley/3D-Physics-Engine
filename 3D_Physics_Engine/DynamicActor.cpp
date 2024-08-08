#include "DynamicActor.h"

namespace PhysicsEngine::ActorTemplates 
{
	DynamicActor::DynamicActor(const PxTransform& pose): startingPos(pose)
	{
		//Actor is defined as an empty pointer, and is given a value here to allow creation of dynamic vs static rigidbodies
		//As this function creates a PxRigidDynamic, downasts to PxRigidDynamic can be used safetly (e.g in CreateShape function)
		actor = GetPhysics()->createRigidDynamic(pose);
		SetName("");
	}

	DynamicActor::~DynamicActor()
	{
		std::vector<PxShape*> shapes = GetShapes();
		for (PxU32 i = 0; i < shapes.size(); i++)
			delete (UserData*)shapes[i]->userData;

		//Calls interface for actor's destructor
		//Also releases all shapes
		actor->release();
	}

	void DynamicActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = actor->createShape(geometry, *GetMaterial());
		//Set mass and intertia tensor(matrix)
		//TODO - look at this function, as currently it is applying the same mass and inertia to all shapes, regardless of previous
		//shape density inputs.
		PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidDynamic*>(actor), density);

		//Initialise the renderer data, including a default color value
		//Unable to use smart pointers here, as the library uses a raw generic pointer
		shape->userData = new UserData(default_color);
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