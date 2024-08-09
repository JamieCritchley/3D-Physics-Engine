# include "StaticActor.h"

namespace PhysicsEngine::ActorTemplates
{
	StaticActor::StaticActor(const PxTransform& pose): Actor(GetPhysics()->createRigidStatic(pose)) {}
}