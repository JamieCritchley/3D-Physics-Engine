# include "StaticActor.h"

namespace PhysicsEngine::ActorTemplates
{
	StaticActor::StaticActor(const PxTransform& pose)
	{
		//Actor is defined as an empty pointer, and is given a value here to allow creation of dynamic vs static rigidbodies
		//As this function creates a PxRigidStatic, downasts to PxRigidStatic can be used safetly
		actor = GetPhysics()->createRigidStatic(pose);
		SetName("");
	}

	StaticActor::~StaticActor()
	{
		std::vector<PxShape*> shapes = GetShapes();
		for (PxU32 i = 0; i < shapes.size(); i++)
			delete (UserData*)shapes[i]->userData;

		//Calls interface for actor's destructor
		//Also releases all shapes
		actor->release();
	}

	void StaticActor::CreateShape(const PxGeometry& geometry, PxReal)
	{
		PxShape* shape = actor->createShape(geometry, *GetMaterial());

		//Initialise the renderer data, including a default color value
		//Unable to use smart pointers here, as the library uses a raw generic pointer
		shape->userData = new UserData(default_color);
	}
}