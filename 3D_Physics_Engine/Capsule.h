#pragma once

#include "DynamicActor.h"

namespace PhysicsEngine::Actors::PrimitiveActors
{
	class Capsule : public DynamicActor
	{
	public:

		//a Capsule with optional default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m radius x 1m height
		// - denisty: 1kg/m^3
		Capsule(const PxTransform& pose = PxTransform(PxIdentity), PxVec2 dimensions = PxVec2(1.f, 1.f), PxReal density = 1.f);

	};
}