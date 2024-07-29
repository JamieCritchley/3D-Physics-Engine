#include "Actor.h"

namespace PhysicsEngine::ActorTemplates
{

	PxRigidActor* Actor::GetActor()
	{
		return actor;
	}

	//The memory address of all items in the color vector are intended to be passed to the renderer, 
	//allowing them to be changed here without passing the values again.
	//This is only implemented in the DynamicActor and StaticActor child classes however - not ideal structure
	//This structure could be improved to prevent missuse of the color vector
	void Actor::SetColor(PxVec3 new_color, PxU32 shape_index)
	{
		//change color of all shapes
		if (shape_index == -1)
		{
			for (unsigned int i = 0; i < colors.size(); i++)
				*colors[i] = new_color;
		}
		//or only the selected one
		else if (shape_index < colors.size())
		{
			*colors[shape_index] = new_color;
		}
	}

	const PxVec3* Actor::GetColor(PxU32 shape_indx)
	{
		if (shape_indx < colors.size())
			return colors[shape_indx];
		else
			return 0;
	}

	void Actor::SetMaterial(PxMaterial* new_material, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes(shape_index);
		for (PxU32 i = 0; i < shape_list.size(); i++)
		{
			std::vector<PxMaterial*> materials(shape_list[i]->getNbMaterials());
			for (unsigned int j = 0; j < materials.size(); j++)
				materials[j] = new_material;
			shape_list[i]->setMaterials(materials.data(), (PxU16)materials.size());
		}
	}

	PxShape* Actor::GetShape(PxU32 index)
	{
		std::vector<PxShape*> shapes(actor->getNbShapes());
		if (index < actor->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size()))
			return shapes[index];
		else
			return 0;
	}

	std::vector<PxShape*> Actor::GetShapes(PxU32 index)
	{
		std::vector<PxShape*> shapes(actor->getNbShapes());
		actor->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size());
		if (index == -1)
			return shapes;
		else if (index < shapes.size() && index > -1)
		{
			//Vector sliced if index is within range of vector
			shapes = vector<PxShape*>(shapes.begin(), shapes.end() - index);
			return shapes;
		}

		//empty vector returned if invalid index is given
		else
			return std::vector<PxShape*>();
	}

	void Actor::SetName(const string& new_name)
	{
		name = new_name;
		actor->setName(name.c_str());
	}

	void Actor::SetTrigger(bool value, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes(shape_index);
		for (PxU32 i = 0; i < shape_list.size(); i++)
		{
			shape_list[i]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !value);
			shape_list[i]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, value);
		}
	}


	string Actor::GetName()
	{
		return name;
	}
}