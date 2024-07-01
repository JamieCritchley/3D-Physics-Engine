#include "Player.h"

namespace PhysicsEngine::AssignmentScene {

	Player::Player(PxTransform pos) {

		//Positions are set up so that the player's foot is pulled back
		upperLeg = new Actors::PrimitiveActors::Box(PxTransform(PxVec3(pos.p.x + 0, pos.p.y + 0.71, pos.p.z + 0), PxQuat(-PxPiDivFour, PxVec3(0, 0, 1))), PxVec3(.05, 0.2032, .05), 1010.0f);
		lowerLeg = new PlayerFoot(PxTransform(PxVec3(pos.p.x + 0, pos.p.y + 0.4568, pos.p.z + 0), PxQuat(-PxPiDivTwo, PxVec3(0,0,1))));
		body = new Actors::PrimitiveActors::Box(PxTransform(PxVec3(pos.p.x + 0, pos.p.y + 1.3503, pos.p.z - 0)), PxVec3(.11, 0.3675, 0.2f), 1010.0f);

		//knee and hip joints connect to respective player body parts
		PxQuat kneeJointRotation = PxQuat(PxPiDivTwo, PxVec3(0, 1, 0)) * PxQuat(PxPi, PxVec3(0,0,1));
		kneeJoint = new Joints::RevoluteJoint((Actors::Actor*)upperLeg, PxTransform(PxVec3(0, -0.2032, 0), kneeJointRotation),
			(Actors::Actor*)lowerLeg, PxTransform(PxVec3(0, 0.05, 0), kneeJointRotation));

		PxQuat hipJointRotation = PxQuat(PxPiDivTwo, PxVec3(0, 1, 0)) * PxQuat(PxPi, PxVec3(0, 0, 1));
		hipJoint = new Joints::RevoluteJoint((Actors::Actor*)body, PxTransform(PxVec3(0, -0.245, 0.1), hipJointRotation),
			(Actors::Actor*)upperLeg, PxTransform(PxVec3(0, 0.3675, 0), hipJointRotation));

		//Makes body kinematic
		body->SetKinematic(true);

		lowerLeg->GetActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		upperLeg->GetActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

		//Set limits to simulate a human knee and hip limits
		kneeJoint->SetLimits(-PxPiDivTwo, 0);
		hipJoint->SetLimits(-PxPiDivFour, PxPiDivFour);

		//Visualisation turned on for joint
		hipJoint->Get()->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, false);

		kickPower = 0;

	}

	std::vector<Actors::Actor*> Player::GetActors() {
		std::vector<Actors::Actor*> actors;
		actors.push_back(upperLeg);
		actors.push_back(lowerLeg);
		actors.push_back(body);
		return actors;
	}


	void Player::Rotate(PxReal degrees) {
		PxRigidBody* bodyRB = (PxRigidBody*)body->GetActor();

		//Body is kinematic, so is moved and rotated without forces
		PxTransform currentPose = bodyRB->getGlobalPose();
		bodyRB->setGlobalPose(PxTransform(currentPose.p, currentPose.q * PxQuat(degrees, PxVec3(0, 1, 0))));

		PxRigidBody* UpperLegRB = (PxRigidBody*)upperLeg->GetActor();
		PxRigidBody* LowerLegRB = (PxRigidBody*)lowerLeg->GetActor();

		UpperLegRB->setGlobalPose(UpperLegRB->getGlobalPose());
		LowerLegRB->setGlobalPose(LowerLegRB->getGlobalPose());
	}


	void Player::Kick() {
		PxRigidBody* UpperLegRB = (PxRigidBody*)upperLeg->GetActor();
		PxRigidBody* LowerLegRB = (PxRigidBody*)lowerLeg->GetActor();

		UpperLegRB->addForce(PxVec3(kickPower, 0, 0), PxForceMode::eIMPULSE);
		LowerLegRB->addForce(PxVec3(kickPower, 0, 0), PxForceMode::eIMPULSE);

		kneeJoint->SetDriveVelocity(kickPower);
		hipJoint->SetDriveVelocity(kickPower/4);

		kickPower = 0;
	}

	void Player::IncrementKickPower(PxReal power) {

		if (kickPower < 48) {
			kickPower += power;
		}
		
	}

	void Player::ResetMotors() {
		kneeJoint->SetDriveVelocity(0);
		hipJoint->SetDriveVelocity(0);
	}
}