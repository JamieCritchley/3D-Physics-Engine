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
		//As shapes do not store their densities, and each shape's densities are used for mass/inertia tensor calculations, a vector is needed
		std::vector<PxReal> shapeDensities;

		//Helper which updates mass and inertia tensor
		void UpdateMassAndIntertiaTensor();

		//Overriden to add extra functionality of updating the actor's mass and inertia tensor when a shape is created.
		void CreateShapeHelper(const PxGeometry& geometry, const PxReal& density);

		//Overriden to add extra functionality of updating the actor's intertia tensor when shapes are moved relative to their actor.
		void SetShapePosHelper(const PxU32& shape_index, const PxTransform& relativeTransform);


	protected:
		//Default constructor - creates dynamic rigidbody from position
		DynamicActor(const PxTransform& pose);

	public:
		//Changes object's kinematic state
		void SetKinematic(const bool& value);

		//Resets actor back to its starting position and sets velocity to 0 (when scene needs to be reset)
		void ResetPos();
	};

}