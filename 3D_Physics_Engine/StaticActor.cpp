# include "StaticActor.h"

namespace PhysicsEngine::Actors
{
	StaticActor::StaticActor(const PxTransform& pose)
	{
		actor = (PxActor*)GetPhysics()->createRigidStatic(pose);
		SetName("");
	}

	StaticActor::~StaticActor()
	{
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;
	}

	void StaticActor::CreateShape(const PxGeometry& geometry, PxReal)
	{
		PxShape* shape = ((PxRigidStatic*)actor)->createShape(geometry, *GetMaterial());
		colors.push_back(default_color);
		//pass the color pointers to the renderer
		shape->userData = new UserData();
		for (unsigned int i = 0; i < colors.size(); i++)
			((UserData*)GetShape(i)->userData)->color = &colors[i];
	}
}