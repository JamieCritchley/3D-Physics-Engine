#pragma once

#include "Actor.h"

namespace PhysicsEngine::Actors
{
	class StaticActor : public Actor
	{

	//May move some stuff back to public if necessary
	protected:
		//Default constructor - creates static rigid actor from position
		StaticActor(const PxTransform& pose);

		//Deletes actors from memoy (may be shifted to base class)
		~StaticActor();

		//Creates a shape with gemoetry input (blank PxReal input to match virtual function signature)
		//Material index 0 (defualt material) is used
		//Default colour also used
		virtual void CreateShape(const PxGeometry& geometry, PxReal);


	};

}