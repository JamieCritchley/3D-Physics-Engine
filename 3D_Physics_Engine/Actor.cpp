#include "Actor.h"

namespace PhysicsEngine::ActorTemplates
{

	PxRigidActor* Actor::GetActor()
	{
		return actor;
	}


	void Actor::SetColor(PxVec3 new_color, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes(shape_index);
		//change color of all shapes
		if (shape_index == -1)
		{
			std::vector<PxShape*> shape_list = GetShapes(shape_index);
			for (int i = 0; i < shape_list.size(); i++)
			{
				static_cast<UserData*>(shape_list[i]->userData)->color = new_color;
			}
		}
		//or only the selected one
		else if (shape_index < shape_list.size())
		{
			static_cast<UserData*>(shape_list[shape_index]->userData)->color = new_color;
		}
	}

	PxVec3 Actor::GetColor(PxU32 shape_index)
	{
		PxShape* shape = GetShape(shape_index);
		if (shape != 0)
		{
			return static_cast<UserData*>(shape->userData)->color;
		}

		//Returns uninitialised PxVec3 if the shape_index is not valid - equivelant to the null ptr returns of other functions
		else
		{
			return PxVec3();
		}
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
		{
			return shapes[index];
		}

		else
		{
			return 0;
		}
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

		//empty vector returned if invalid index is given - equivelant to the null ptr returns of other functions
		else
		{
			return std::vector<PxShape*>();
		}
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