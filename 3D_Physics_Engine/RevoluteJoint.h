#pragma once
#include "Joint.h"

#include "Actor.h"

namespace PhysicsEngine::Joints {

    class RevoluteJoint : public Joint
    {
	public:
		RevoluteJoint(ActorTemplates::Actor* actor0, const PxTransform& localFrame0, ActorTemplates::Actor* actor1, const PxTransform& localFrame1);

		void SetDriveVelocity(PxReal value);

		PxReal GetDriveVelocity();

		void SetGearRatio(PxReal ratio);

		PxReal GetGearRatio();

		void SetLimits(PxReal lower, PxReal upper);
    };
}

