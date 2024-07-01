#pragma once

#include "PhysicsEngine.h"
#include "Actor.h"

namespace PhysicsEngine
{

	class Scene
	{
	protected:
		//a PhysX scene object
		PxScene* px_scene;
		//pause simulation
		bool pause;
		//selected dynamic actor on the scene
		PxRigidDynamic* selected_actor;
		//original and modified colour of the selected actor
		std::vector<PxVec3> sactor_color_orig;

		void HighlightOn(PxRigidDynamic* actor);

		void HighlightOff(PxRigidDynamic* actor);

		///User defined initialisation
		//Can be overriden to add extra functionality onto the end of the init function (helper function)
		virtual void CustomInit();

		///User defined update step
		//Can be overriden to add extra functionality onto the end of the update function (helper function)
		virtual void CustomUpdate();

	public:
		///Init the scene
		void Init();

		///Perform a single simulation step
		//Takes a frame time in seconds as input
		void Update(PxReal dt);

		///Add single actor to scene
		void AddActor(Actors::Actor* actor);

		///Get the PxScene object
		PxScene* GetScene();

		///Reset the scene
		void Reset();

		///Pause/unpasue scene with bool
		void SetPause(bool Pause);

		///Get pause state of scene
		bool GetPause();

		///Get the selected dynamic actor on the scene
		PxRigidDynamic* GetSelectedActor();

		///Switch to the next dynamic actor
		void SelectNextActor();

		///a list with all actors
		std::vector<PxActor*> GetAllActors();
	};

}