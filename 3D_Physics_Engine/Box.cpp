#include "Box.h"

namespace PhysicsEngine::ActorTemplates::PrimitiveActors
{
	Box::Box(const PxTransform& pose, PxVec3 dimensions, PxReal density) : DynamicActor(pose)
	{
		CreateShape(PxBoxGeometry(dimensions), density);
	}
}