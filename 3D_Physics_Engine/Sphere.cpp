#include "Sphere.h"

namespace PhysicsEngine::Actors::PrimitiveActors
{
	Sphere::Sphere(const PxTransform& pose, PxReal radius, PxReal density) : DynamicActor(pose)
	{
		CreateShape(PxSphereGeometry(radius), density);
	}

}
		