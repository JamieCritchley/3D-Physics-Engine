#pragma once

#include "Actor.h"

namespace PhysicsEngine::Actors
{
	class DynamicActor : public Actor
	{

	//May move some stuff back to public if necessary
	protected:

		//Need to store a reference to starting pos to allow dynamic actors to be reset in scene
		PxTransform startingPos;

		//Default constructor - creates dynamic rigidbody from position
		DynamicActor(const PxTransform& pose);

		//Deletes actors from memoy (may be shifted to base class)
		~DynamicActor();

		//Creates a shape with inputs of gemoetry and density
		//Material index 0 (defualt material) is used
		//Default colour also used
		virtual void CreateShape(const PxGeometry& geometry, PxReal density);


	public:

		//Changes object's kinematic state
		void SetKinematic(bool value);

		//Resets actor back to its starting position and sets velocity to 0 (when scene needs to be reset)
		void ResetPos();
	};

}