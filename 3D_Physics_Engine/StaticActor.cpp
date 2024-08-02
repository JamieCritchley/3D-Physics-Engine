# include "StaticActor.h"

namespace PhysicsEngine::ActorTemplates
{
	StaticActor::StaticActor(const PxTransform& pose)
	{
		//Actor is defined as an empty unique_ptr, and is given a value here to allow creation of dynamic vs static rigidbody
		actor = GetPhysics()->createRigidStatic(pose);
		SetName("");
	}

	StaticActor::~StaticActor()
	{
		for (unsigned int i = 0; i < GetShapes().size(); i++)
			delete (UserData*)GetShape(i)->userData;

		//Calls interface for actor's destructor
		//Also releases all shapes
		actor->release();
	}

	void StaticActor::CreateShape(const PxGeometry& geometry, PxReal)
	{
		PxShape* shape = actor->createShape(geometry, *GetMaterial());

		//Initialise the renderer data, including a default color value
		shape->userData = new UserData(default_color);
	}
}