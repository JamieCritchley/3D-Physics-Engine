#pragma once

#include "PhysicsEngine.h"
#include "memory"

namespace PhysicsEngine::ActorTemplates
{
	//Wrspper for abstract actor class
	//This was previuously a PxActor wrapper. However, this class is clearly intended to only be used for PxRigidActors, 
	//as PxCloth/PxParticles do not create shapes. For now, this class will be a wrapper for PxRigidActors, and the engine
	//can be expanded for cloth and particle systems later.
	//Implementation leads to downcasting in dynamic child class - could this be avoided?
	class Actor
	{


	private:

		//Copy of renderer data kept in unique_ptr to allow easy deletion. As shapes are released when this wrapper is deleted,
		//this wrapper and its children also store shape data (which is very limitted) - PxRigidActor and PxShape are tightly coupled. 
		std::vector<std::unique_ptr<UserData>> shapeRendererData;

		//An empty function which can be overriden to add extra functionality to the end of CreateShape.
		virtual void CreateShapeHelper(const PxGeometry& geometry, const PxReal& density);

		//An empty function which can be overriden to add extra functionality to the end of SetShapePos.
		virtual void SetShapePosHelper(const PxU32& shape_index, const PxTransform& relativeTransform);

	protected:

		//PxRigidActor is instantiated by derived classes, so wrappers which inherit from this wrapper must create and pass an
		//actor derived from PxRigidActor
		Actor(PxRigidActor* Actor);
		//Rule of 5 - protected to prevent slicing (C.67 in core guidlines)
		Actor(const Actor& a) = default;
		Actor& operator= (const Actor& a) = default;
		Actor(Actor&&) = default;
		Actor& operator= (Actor&&) = default;

		//Smart pointer could not be used as the destructor is protected - need to use interface for memory management 
		PxRigidActor* actor = 0;
		std::string name = "";

		//Creates a shape with the geometry input. If the actor is dynamic, denisty is passed to the virtual CreateShapeHelper function,
		//which has been overridden to calculate mass and the inertia tensor. Static actors can use a placeholder PxReal for function calls.
		//Material index 0 (defualt material) is used
		//Default colour also used
		void CreateShape(const PxGeometry& geometry, const PxReal& density);

		//Changes the position of one of the actor's shapes relative to the actor - in "actor space". 
		//If the actor is dynamic, the inertia tensor is recalculated using the overriden SetShapePosHelper
		void SetShapePos(const PxU32& shape_index, const PxTransform& relativeTransform);

	public:

		//Public virtual destructor - derived classes are intended to be deletable through a base class pointer
		virtual ~Actor();

		//Basic getter
		PxRigidActor* GetActor();

		//Sets colour for specific shape index
		//Default value for shape index is -1, which sets color for all shapes
		void SetColor(const PxVec3& new_color, PxU32 shape_index = -1);

		//Gets colour for specific shape index
		//Default value for shape index is 0, which gets color for first shape
		PxVec3 GetColor(PxU32 shape_index = 0);

		//Gets an individual shape, for a specific index
		//Default value for index is 0, which gets first shape
		//WARNING - do not use this to call setLocalPose. This will not appropriately update the inertia tensor of dynamic actors.
		//Use the SetShapePos function to change a shape position.
		PxShape* GetShape(PxU32 index = 0);

		//Returns all shapes attached to the actor
		std::vector<PxShape*> GetShapes();

		//Sets material for specific shape index
		//Default value for shape index is -1, which sets color for all shapes
		void SetMaterial(PxMaterial* new_material, PxU32 shape_index = -1);

		//Toggles "trigger" state. If true, actor will not take part in physics simulation,
		//and can send reports when objects enter/leave its volume
		void SetTrigger(const bool& value, PxU32 index = -1);

		//Basic setter
		void SetName(const string& name);

		//Basic getter
		string GetName();
	};

}