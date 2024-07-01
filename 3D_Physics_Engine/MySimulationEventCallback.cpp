#include "MySimulationEventCallback.h"
#include <iostream>

namespace PhysicsEngine::AssignmentScene {

	MySimulationEventCallback::MySimulationEventCallback() : trigger(false), goal(false), miss(false) {}

	void MySimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		//you can read the trigger information here
		for (PxU32 i = 0; i < count; i++)
		{
			//filter out contact with the planes
			if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
			{
				//check if eNOTIFY_TOUCH_FOUND trigger
				if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
					trigger = true;

					//Checks if trigger rperesents goal or miss (ADDITION TO TUTORIAL)
					if (pairs[i].triggerActor->getName() == "Goal" && pairs[i].otherActor->getName() == "Ball") {
						goal = true;
					}

					else if (pairs[i].triggerActor->getName() == "Miss" && pairs[i].otherActor->getName() == "Ball") {
						miss = true;
					}
				}
				//check if eNOTIFY_TOUCH_LOST trigger
				if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
					trigger = false;
				}
			}
		}
	}

	void MySimulationEventCallback::onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs)
	{
		cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

		//check all pairs
		for (PxU32 i = 0; i < nbPairs; i++)
		{
			//check eNOTIFY_TOUCH_FOUND
			if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
			}
			//check eNOTIFY_TOUCH_LOST
			if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
			{
				cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
			}
		}
	}

	bool MySimulationEventCallback::CheckGoal() {
		//Resets bool to false when player scores to prevent registering multiple goals
		if (goal) {
			goal = false;
			return true;
		}
		else {
			return false;
		}
	}

	bool MySimulationEventCallback::CheckMiss() {
		//Resets bool to false when player scores to prevent registering multiple misses
		if (miss) {
			miss = false;
			return true;
		}
		else {
			return false;
		}
	}

	void MySimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {}
	void MySimulationEventCallback::onWake(PxActor** actors, PxU32 count) {}
	void MySimulationEventCallback::onSleep(PxActor** actors, PxU32 count) {}
#if PX_PHYSICS_VERSION >= 0x304000
	void MySimulationEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {}
#endif
}

