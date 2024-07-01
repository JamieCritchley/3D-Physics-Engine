#pragma once

#include "DynamicActor.h"


namespace PhysicsEngine::CustomScene 
{

	//Represents two adjacent 1x1 cubes
	class CompoundObject : public Actors::DynamicActor 
	{

	public:

		//Creates two boxes with corresponding size (half-verts)
		CompoundObject(PxVec3 boxDimensions);

	};

}