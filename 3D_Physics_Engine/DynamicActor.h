#pragma once

#include "Actor.h"

namespace PhysicsEngine::ActorTemplates
{
	//Inherit from this to create dynamic actors with specified geometry. Currently this has a protected constructor despite not
	//being abstract - this is because the design aims to make this generalised class more specific with gemoetry dedicated child 
	//classes - see the "PrimitiveActors" namespace for examples.
	class DynamicActor : public Actor
	{

	private:
		//Need to store a reference to starting pos to allow dynamic actors to be reset in scene
		PxTransform startingPos;

	protected:
		//Default constructor - creates dynamic rigidbody from position
		DynamicActor(const PxTransform& pose);

		//Creates a shape with inputs of gemoetry and density
		//Material index 0 (defualt material) is used
		//Default colour also used
		virtual void CreateShape(const PxGeometry& geometry, PxReal density);

	public:
		//Deletes actors and renderer related shape data from memoy
		virtual ~DynamicActor();

		//Changes object's kinematic state
		void SetKinematic(const bool& value);

		//Resets actor back to its starting position and sets velocity to 0 (when scene needs to be reset)
		void ResetPos();
	};

}