#pragma once

#include "Actor.h"

namespace PhysicsEngine::ActorTemplates
{
	//Inherit from this to create static actors with specified geometry. Currently this has a protected constructor despite not
	//being abstract - this is because the design aims to make this generalised class more specific with gemoetry dedicated child 
	//classes - see the "PrimitiveActors" namespace for examples.
	class StaticActor : public Actor
	{

	protected:
		//Default constructor - creates static rigid actor from position
		StaticActor(const PxTransform& pose);

		//Creates a shape with gemoetry input (blank PxReal input to match virtual function signature)
		//Material index 0 (defualt material) is used
		//Default colour also used
		virtual void CreateShape(const PxGeometry& geometry, PxReal);

	public:
		//Deletes actors and renderer related shape data from memoy
		virtual ~StaticActor();

	};

}