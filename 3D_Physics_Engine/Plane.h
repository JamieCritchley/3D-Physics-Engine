#pragma once

#include "StaticActor.h"


namespace PhysicsEngine::Actors::PrimitiveActors
{
	class Plane : public StaticActor
	{

	public:

		//A plane with optional default paramters:
		//- normal of 0,1,0
		//- distance from origin: 0m
		Plane(PxVec3 normal = PxVec3(0.f, 1.f, 0.f), PxReal distance = 0.f);

	};
}