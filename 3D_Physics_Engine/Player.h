#pragma once

#include "Box.h"
#include "RevoluteJoint.h"
#include "PhysicsEngine.h"
#include "PlayerFoot.h"

namespace PhysicsEngine::AssignmentScene {

	class Player
	{
	private:
		Actors::PrimitiveActors::Box* upperLeg;
		PlayerFoot* lowerLeg;
		Actors::PrimitiveActors::Box* body;
		Joints::RevoluteJoint* kneeJoint;
		Joints::RevoluteJoint* hipJoint;
		PxReal kickPower; //In Newtons

	public:

		//Creates the freekick taker's kicking leg (may be expanded to more body parts)
		//Made up of dynamic and kinematic actors, such that the leg can float in the air, but still kick with realistic physics
		//Position is the point at the center of the player's kicking foot (may change)
		Player(PxTransform pos = PxTransform(PxIdentity));

		//Getter for actors to allow them to be added to scene, have colour set, etc.
		std::vector<Actors::Actor*> GetActors();

		//Rotates player around the ball - positive value for right, negative for left
		void Rotate(PxReal degrees);

		//Pushes upper and lower leg forward to kick ball - uses power stored from incrementation, before resetting it to 0
		void Kick();

		//Increases power of next kick (with upper limit)
		void IncrementKickPower(PxReal power);

		void ResetMotors();
	};
}

