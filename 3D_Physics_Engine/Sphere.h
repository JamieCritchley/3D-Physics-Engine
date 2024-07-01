#pragma once

#include "DynamicActor.h"

namespace PhysicsEngine::Actors::PrimitiveActors
{
	class Sphere : public DynamicActor
	{

	public:
		//a sphere with optional default parameters:
		// - pose in 0,0,0
		// - radius: 1m
		// - denisty: 1kg/m^3
		Sphere(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal density = 1.f);
	};

}