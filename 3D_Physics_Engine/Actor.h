#pragma once

#include "PhysicsEngine.h"
#include "memory"

namespace PhysicsEngine::ActorTemplates
{

	//This was previuously a PxActor wrapper. However, this class is clearly intended to only be used for PxRigidActors, 
	//as PxCloth/PxParticles do not create shapes. For now, this class will be a wrapper for PxRigidActors, and the engine
	//can be expanded for cloth and particle systems later.
	//Implementation leads to downcasting in dynamic child class - could this be avoided?
	
	//Look into destructor - class includes virtual function, need virtual destructor and then rule of 5.
	//Keep looking for any places smart pointers can be used (Physx's protected destructors prevents them always being used)
	class Actor
	{

	protected:

		////
		//Actor(const Actor&) = default;
		//Actor& operator= (const Actor&) = default;
		//Actor(Actor&&) = default;
		//Actor& operator= (Actor&&) = default;

		//Smart pointer could not be used as the destructor is protected - need to use interface for memory management 
		//(handled in child classes, where the specific actor instance is created)
		PxRigidActor* actor = 0;
		std::vector<std::unique_ptr<PxVec3>> colors;
		std::string name = "";

		//Implement a function to add a shape to actor
		virtual void CreateShape(const PxGeometry& geometry, PxReal density) = 0;


	public:
		//Basic getter
		PxRigidActor* GetActor();

		//Sets colour for specific shape index
		//Default value for shape index is -1, which sets color for all shapes
		void SetColor(PxVec3 new_color, PxU32 shape_index = -1);

		//Gets colour for specific shape index
		//Default value for shape index is 0, which gets color for first color
		const PxVec3* GetColor(PxU32 shape_indx = 0);

		//Gets an individual shape, for a specific index
		//Default value for index is 0, which gets first shape
		PxShape* GetShape(PxU32 index = 0);

		//Gets a range of shapes
		//Default index of -1 will return all shapes
		//To get a sub-array of shapes, give an index value to use as the end range
		//Note - this may be updated to include start range indexing
		std::vector<PxShape*> GetShapes(PxU32 index = -1);

		//Sets material for specific shape index
		//Default value for shape index is -1, which sets color for all shapes
		void SetMaterial(PxMaterial* new_material, PxU32 shape_index = -1);

		void SetTrigger(bool value, PxU32 index = -1);

		//Basic setter
		void SetName(const string& name);

		//Basic getter
		string GetName();
	};

}