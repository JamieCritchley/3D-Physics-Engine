#include "Capsule.h"

namespace PhysicsEngine::ActorTemplates::PrimitiveActors
{
	Capsule::Capsule(const PxTransform& pose, PxVec2 dimensions, PxReal density) : DynamicActor(pose)
	{
		CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
	}
}
