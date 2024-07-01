#pragma once


#include "DynamicActor.h"


namespace PhysicsEngine::CustomScene
{
	//Represents four capsules pointing in compass directions
	class CompoundCapsuleObject : public Actors::DynamicActor
	{
	public:

		//Creates four capsules pointing in compass directions (lyuing on XZ plane)
		CompoundCapsuleObject(PxReal height, PxReal radius);

	};

}
