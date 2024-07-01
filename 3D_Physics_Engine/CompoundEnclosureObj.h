#pragma once

#include "StaticActor.h"

namespace PhysicsEngine::CustomScene
{
	//Represents a rectangular enclosure (like a crate/closed box)
	class CompoundEnclosureObj : public Actors::StaticActor 
	{
	public:

		//Creates a rectangular enclosure (like a crate/closed box)
		//Dimensions represents the size, while thickness is how thick the walls and floor of the enclosure is
		//Spawns on xz plane so it is resting on it
		CompoundEnclosureObj(PxTransform pose, PxVec3 dimensions, PxReal thickness, PxReal density);
	};

}