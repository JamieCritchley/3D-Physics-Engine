#pragma once

#include "PhysicsEngine.h"

namespace PhysicsEngine::AssignmentScene {

    class MySimulationEventCallback : public PxSimulationEventCallback
    {
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;
		bool goal;
		bool miss;

		MySimulationEventCallback();

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

		//Getter to check for goal
		bool CheckGoal();

		//Getter to check for miss
		bool CheckMiss();

		//Overriden to empty as they are pure virtual
		virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);
		virtual void onWake(PxActor** actors, PxU32 count);
		virtual void onSleep(PxActor** actors, PxU32 count);
#if PX_PHYSICS_VERSION >= 0x304000
		virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);
#endif

	};
    
}

