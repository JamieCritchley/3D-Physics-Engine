#pragma once

#include "PhysicsEngine.h"


namespace PhysicsEngine::ActorTemplates
{
	//Abstract Actor class
	//Look into destructor - class includes hierarhcies and pointers.
	//^Try to avoid destructors - need to look into smart pointers and get them working
	//^This ran into the issues of the c-style casts used throughout this code - should look into static and dynamic casts
	class Actor
	{

	protected:

		PxActor* actor = 0;
		std::vector<PxVec3*> colors;
		std::string name = "";

		//Implement a function to add a shape to actor
		virtual void CreateShape(const PxGeometry& geometry, PxReal density) = 0;


	public:
		//Basic getter
		PxActor* GetActor();

		//Sets colour for specific shape index
		//Default value for shape index is -1, which sets color for all shapes
		void SetColor(PxVec3 new_color, PxU32 shape_index = -1);

		//Gets colour for specific shape index
		//Default value for shape index is 0, which gets color for first shape
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