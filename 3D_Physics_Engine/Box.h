#pragma once

#include "DynamicActor.h"

namespace PhysicsEngine::ActorTemplates::PrimitiveActors
{
	//Wrapper for a dynamic box object
	class Box : public DynamicActor
	{
	public:
		//a Box with optional default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f);

	};

}