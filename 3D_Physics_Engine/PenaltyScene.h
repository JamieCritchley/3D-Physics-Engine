#pragma once

#include "PhysicsEngine.h"

#include "Scene.h"
#include "Plane.h"
#include "Sphere.h"
#include "GoalFrame.h"
#include "Player.h"
#include "BoundaryTrigger.h"
#include "MySimulationEventCallback.h"
#include "Extras\HUD.h"

namespace PhysicsEngine::AssignmentScene {

	class PenaltyScene : public Scene
	{
	private:
		Actors::PrimitiveActors::Plane* plane;
		Actors::PrimitiveActors::Sphere* ball;
		GoalFrame* goalFrame;
		Player* player;
		vector<BoundaryTrigger*> boundaries;
		vector<BoundaryTrigger*> lines;
		vector<Actors::PrimitiveActors::Box*> humans;
		MySimulationEventCallback* myEventCallback;
		VisualDebugger::HUD* hud;
		int score = 0;
		bool isBallMoving = false;
		bool hasPlayerKicked = false;
		bool hasLegStartedMoving = false;

	protected:

		void SetVisualisation();

		//Custom scene initialisation
		//Exapnds base class init implementation
		//Populates scene with actors
		//Takes reference to HUD so that game state can be updated
		virtual void CustomInit();

		//Custom scene update
		//Exapnds base class init implementation
		//Updates rotation of a box
		virtual void CustomUpdate();

		//Resets all dynamic actors in scene (e.g. when scoring/missing a shot)
		void ResetDyamicActors();

		//Function pair to check if ball has started moving, and then stopped moving after being kicked, but hasn't gone out (e.g. player hits the post/crossbar)
		void CheckBallMoving();

		//Pair to CheckBallMoving
		void CheckBallMissed();


		//Checks when player's leg starts moving (pair to CheckKickMissing)
		void CheckKickStarted();

		//Checks if layer has kicked but missed the ball
		void CheckKickMissed();

	public:

		//Consturctor used to pass vars across (as CustomInit can't take arguments due to it being an override of a (protected) virtual function)
		PenaltyScene(VisualDebugger::HUD* _hud);

		//User inputs

		//Rotates player around ball, with input of positive value for right and negative for left
		void RotatePlayer(PxReal degrees);

		//Makes player kick the ball, with value stored while incrementing kick power when holding button
		void PlayerKick();

		//Increments player kick power by Newtons input (longer player holds kick, harder the kick is
		void IncrementKickPower(PxReal power);

		//Replaces ball with human which spawns from the sky (can spawn multiple)
		void SpawnHuman();
	};
}


