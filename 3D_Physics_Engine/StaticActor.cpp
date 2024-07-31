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
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;

		//Calls interface for actor's destructor
		actor->release();
	}

	void StaticActor::CreateShape(const PxGeometry& geometry, PxReal)
	{
		PxShape* shape = actor->createShape(geometry, *GetMaterial());

		//Create a color pointer for the shape
		colors.push_back(std::make_unique<PxVec3>(default_color));
		//Pass the color pointer to the renderer
		shape->userData = new UserData();
		((UserData*)shape->userData)->color = colors[colors.size() - 1].get();
	}
}