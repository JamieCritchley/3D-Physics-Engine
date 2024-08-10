#include "Actor.h"

namespace PhysicsEngine::ActorTemplates
{

	Actor::Actor(PxRigidActor* Actor): actor(Actor)
	{
		SetName("");
	}

	void Actor::CreateShapeHelper(const PxGeometry& geometry, const PxReal& density) {}

	void Actor::SetShapePosHelper(const PxU32& shape_index, const PxTransform& relativeTransform) {}

	void Actor::CreateShape(const PxGeometry& geometry, const PxReal& density)

	{
		//Ownership of shape is given to actor
		PxShape* shape = actor->createShape(geometry, *GetMaterial());

		//Initialise the renderer data, including a default color value
		//Stored as a member to allow easy deletion
		shapeRendererData.push_back(std::make_unique<UserData>(default_color));
		shape->userData = shapeRendererData.back().get(); //Shape has observing ptr, not ownership

		CreateShapeHelper(geometry, density);
	}

	void Actor::SetShapePos(const PxU32& shape_index, const PxTransform& relativeTransform)
	{
		GetShape(shape_index)->setLocalPose(relativeTransform);
		SetShapePosHelper(shape_index, relativeTransform);
	}

	Actor::~Actor() 
	{
		//Calls interface for actor's destructor
		//Also releases all shapes, (and their renderer data via unique_ptr)
		actor->release();
	}

	PxRigidActor* Actor::GetActor()
	{
		return actor;
	}


	void Actor::SetColor(const PxVec3& new_color, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes();
		//change color of all shapes
		if (shape_index == -1)
		{
			for (PxU32 i = 0; i < shape_list.size(); i++)
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
		std::vector<PxShape*> shape_list = GetShapes();

		//change material of all shapes
		if (shape_index == -1) 
		{
			for (PxU32 i = 0; i < shape_list.size(); i++)
			{
				std::vector<PxMaterial*> materials(shape_list[i]->getNbMaterials());
				for (PxU32 j = 0; j < materials.size(); j++)
				{
					materials[j] = new_material;
				}
				shape_list[i]->setMaterials(materials.data(), (PxU16)materials.size());
			}
		}

		//or only the selected one
		else if (shape_index < shape_list.size())
		{
			std::vector<PxMaterial*> materials(shape_list[shape_index]->getNbMaterials());
			for (PxU32 j = 0; j < materials.size(); j++)
			{
				materials[j] = new_material;
			}
			shape_list[shape_index]->setMaterials(materials.data(), (PxU16)materials.size());
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

	std::vector<PxShape*> Actor::GetShapes()
	{
		std::vector<PxShape*> shapes(actor->getNbShapes());
		actor->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size());
		return shapes;
	}

	void Actor::SetName(const string& new_name)
	{
		name = new_name;
		actor->setName(name.c_str());
	}

	void Actor::SetTrigger(const bool& value, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes();
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