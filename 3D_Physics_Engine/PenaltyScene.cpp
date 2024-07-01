#include "PenaltyScene.h"
#include "VisualDebugger.h"
#include <iostream>

namespace PhysicsEngine::AssignmentScene {

	PenaltyScene::PenaltyScene(VisualDebugger::HUD* _hud) {
		hud = _hud;
	}

	void PenaltyScene::SetVisualisation() {
		px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f); //Controls scale  of axes (and probably other stuff)
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f); //Shows collider lines

		////Added workshop2
		//px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_AXES, 1.0f); //Shows red-green-blue- 3D axes
		//px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f); //Shows direction and magniture of velocity


		//Added workshop3
		px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f); //Shows joint local axes
		px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f); //Shows the limits of joints
	}

	void PenaltyScene::CustomInit() {
		SetVisualisation();

		GetMaterial()->setDynamicFriction(.02f);
		GetMaterial()->setStaticFriction(.02f);

		plane = new Actors::PrimitiveActors::Plane();
		plane->SetColor(PxVec3(19.0f / 255.0f, 133.0f / 255.0f, 16.0f / 255.0f)); //Set to grass colour
		AddActor(plane);

		//0,0,0 is used as penalty spot
		//Init football
		ball = new Actors::PrimitiveActors::Sphere(PxTransform(physx::PxVec3(0, 0.055, 0)), 0.11, 77.52f); //Radius and denisty based on IFAB
		ball->SetColor(PxVec3(255.0f / 255.0f, 247.0f / 255.0f, 0.0f / 255.0f));
		ball->GetActor()->setName("Ball");
		AddActor(ball);

		//Init goal
		goalFrame = new GoalFrame(PxTransform(10.95, 0, 0));
		goalFrame->SetColor(PxVec3(1.0f, 1.0f, 1.0f)); //Set goal frame to white, as IFAB specifices this
		AddActor(goalFrame);

		//Init boundaires - ball has to cross lines to count as out/goal, so this is used for positioning
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(11.5, 1.22, 0)), PxVec3(1, 2.44, 7.32)));
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(11.5, 52.49, 0)), PxVec3(1, 100, 100)));
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(11.5, 1.27, 53.66)), PxVec3(1, 2.54, 100)));
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(11.5, 1.27, -53.66)), PxVec3(1, 2.54, 100)));
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(-39, 50, 32.5)), PxVec3(100, 100, 1)));
		boundaries.push_back(new BoundaryTrigger(PxTransform(PxVec3(-39, 50, -32.5)), PxVec3(100, 100, 1)));


		for (BoundaryTrigger* boundary : boundaries)
		{
			//First boundary represents the goal, others are everything else (which when touched, means the player has missed)
			if (boundary == boundaries[0]) {
				boundary->GetActor()->setName("Goal");
				boundary->SetColor(PxVec3(140.0f / 255.0f, 0, 255.0f / 255.0f));
			}
			else {
				boundary->GetActor()->setName("Miss");
				boundary->SetColor(PxVec3(255.0f / 255.0f, 166.0f / 255.0f, 0));
			}

			AddActor(boundary);
		}



		//Init pitch lines - boundarytrigger class reused as a quick way to get a static box with no collisions
		//Touchlines and goal lines
		lines.push_back(new BoundaryTrigger(PxTransform(10.95, 0.005, 0), PxVec3(0.1, 0.01, 64)));
		lines.push_back(new BoundaryTrigger(PxTransform(-39, 0.005, 31.95), PxVec3(100, 0.01, 0.1)));
		lines.push_back(new BoundaryTrigger(PxTransform(-39, 0.005, -31.95), PxVec3(100, 0.01, 0.1)));

		//Goal area
		lines.push_back(new BoundaryTrigger(PxTransform(8.25, 0.005, 9.11), PxVec3(5.5, 0.01, 0.1)));
		lines.push_back(new BoundaryTrigger(PxTransform(8.25, 0.005, -9.11), PxVec3(5.5, 0.01, 0.1)));
		lines.push_back(new BoundaryTrigger(PxTransform(5.55, 0.005, 0), PxVec3(0.1, 0.01, 18.32)));

		//Penalty box
		lines.push_back(new BoundaryTrigger(PxTransform(2.75, 0.005, 20.11), PxVec3(16.5, 0.01, 0.1)));
		lines.push_back(new BoundaryTrigger(PxTransform(2.75, 0.005, -20.11), PxVec3(16.5, 0.01, 0.1)));
		lines.push_back(new BoundaryTrigger(PxTransform(-5.45, 0.005, 0), PxVec3(0.1, 0.01, 40.32)));

		for (BoundaryTrigger* line : lines)
		{
			AddActor(line);
			line->SetColor(PxVec3(1.0f, 1.0f, 1.0f)); //Set lines to white
		}

		//Init player
		player = new Player(PxTransform(PxVec3(.1, 0, -.3)));

		//player object is made up of multiple actors, which all need colour and to be added to the scene
		std::vector<Actors::Actor*> temps = player->GetActors();
		for (Actors::Actor* temp : temps)
		{
			temp->SetColor(PxVec3(255.0f / 255.0f, 13.0f / 255.0f, 0.0f / 255.0f));
			AddActor(temp);

		}


		//Init event callback
		myEventCallback = new MySimulationEventCallback();
		px_scene->setSimulationEventCallback(myEventCallback);

		//Init HUD (with game state)
		hud->AddLine(VisualDebugger::HUDState::HELP, ""); //As help screen is main screen, game state is placed here
		hud->AddLine(VisualDebugger::HUDState::HELP, "----GAME STATE ----"); //As help screen is main screen, game state is placed here
		hud->AddLine(VisualDebugger::HUDState::HELP, "Objective: Score 5 penalties to win");
		hud->AddLine(VisualDebugger::HUDState::HELP, "Score: " + to_string(score));
		ResetDyamicActors();
	}

	void PenaltyScene::CustomUpdate() {

		//Check if player has scored or missed
		//If player has scored, reset actors, check for win condition and update texty
		if (myEventCallback->CheckGoal()) {
			ResetDyamicActors();

			//Increment score and update text
			score++;
			hud->RemoveLine(VisualDebugger::HUDState::HELP);

			//Remove and replace victory message if player lkeeps scoring after winning
			if (score > 5) {
				hud->RemoveLine(VisualDebugger::HUDState::HELP);
			}
			hud->AddLine(VisualDebugger::HUDState::HELP, "Score: " + to_string(score));

			//Victory message
			if (score >= 5) {
				hud->AddLine(VisualDebugger::HUDState::HELP, "Congrats, you've won!");
			}

		}

		//If player hads missed, reset actors but don't update score
		if (myEventCallback->CheckMiss()) {
			ResetDyamicActors();
		}

		//Checks if ball has missed, but not gone out
		CheckBallMoving();
		CheckBallMissed();

		//Checks if player has completely missed the ball
		CheckKickStarted();
		CheckKickMissed();
	}

	void PenaltyScene::ResetDyamicActors() {

		//Only resets ball if it is being simulated (doesn't reset for catastrophe mode)
		if (!ball->GetActor()->getActorFlags().isSet(PxActorFlag::eDISABLE_SIMULATION)) {
			ball->ResetPos();
		}


		//Have to reset player's joint motors too
		player->ResetMotors();
		//player object is made up of multiple actors, which all need to be reset
		std::vector<Actors::Actor*> temps = player->GetActors();
		for (Actors::Actor* temp : temps) {
			Actors::DynamicActor* dynamicTemp = (Actors::DynamicActor*)temp;
			dynamicTemp->ResetPos();
		}

		//Bools are reset too
		isBallMoving = false;
		hasPlayerKicked = false;
		hasLegStartedMoving = false;
	}

	void PenaltyScene::RotatePlayer(PxReal degrees) {
		player->Rotate(degrees);
	}

	void PenaltyScene::PlayerKick()
	{
		player->Kick();
		hasPlayerKicked = true;
	}

	void PenaltyScene::IncrementKickPower(PxReal power) {
		player->IncrementKickPower(power);
	}

	void PenaltyScene::SpawnHuman() {

		PxRigidBody* rb = (PxRigidBody*)ball->GetActor();
		rb->setGlobalPose(PxTransform(0, 10000000, 0));
		ball->GetActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);

		humans.push_back(new Box(PxTransform(PxVec3(0, 5, 0)), PxVec3(.15f, 0.914f, 0.3f), 1010.0f));
		humans[humans.size() - 1]->SetColor(PxVec3(0.0f / 255.0f, 13.0f / 255.0f, 255.0f / 255.0f));
		AddActor(humans[humans.size() - 1]);
	}

	void PenaltyScene::CheckBallMoving() {

		//If ball isn't marked as moving, and the player has kicked, check if it has velocity
		if (!isBallMoving && hasPlayerKicked) {

			//If it has siginificant velocity, mark ball as moving
			PxRigidBody* rb = (PxRigidBody*)ball->GetActor();
			if (rb->getLinearVelocity().magnitude() > 0.1) {
				isBallMoving = true;
				hasPlayerKicked = false;
			}
		}
	}

	void PenaltyScene::CheckBallMissed() {

		//If ball has started moving and has now stopped, reset scene
		//If ball isn't being simulated, catastrophic mode is engaged so don't reset actors
		if (!ball->GetActor()->getActorFlags().isSet(PxActorFlag::eDISABLE_SIMULATION))
		{
			//Earlies out if ball is not moving
			if (!isBallMoving) {
				return;
			}
			//Checks if ball is moving away from the goal, or if it is moving so slowly it would be saved in a football match
			PxRigidBody* rb = (PxRigidBody*)ball->GetActor();
			if (rb->getLinearVelocity().x <= 0 || rb->getLinearVelocity().magnitude() < 0.2) {

				//If ball has stopped/missed, reset scene
				ResetDyamicActors();
			}
		}
	}

	void PenaltyScene::CheckKickStarted() {


		//If input has been given to kick, check if movement in leg has started
		if (hasPlayerKicked && !hasLegStartedMoving) {

			std::vector<Actors::Actor*> temps = player->GetActors();
			for (int i = 0; i < temps.size(); i++) {
				//Last actor is body which is kinematic, so don't check
				if (i == temps.size() - 1) {
					continue;
				}

				PxRigidBody* rb = (PxRigidBody*)temps[i]->GetActor();
				if (rb->getAngularVelocity().magnitude() > 0) {
					hasLegStartedMoving = true;
				}

			}
		}
	}


	void PenaltyScene::CheckKickMissed() {

		//If player's leg isn't moving, and ball is stationary, kick has missed
		if (!hasLegStartedMoving || isBallMoving) {
			return;
		}

		bool hasPlayerStopped = true;
		std::vector<Actors::Actor*> temps = player->GetActors();
		for (int i = 0; i < temps.size(); i++) {
			//Last actor is body which is kinematic, so don't check
			if (i == temps.size() - 1) {
				continue;
			}

			PxRigidBody* rb = (PxRigidBody*)temps[i]->GetActor();
			if (rb->getLinearVelocity().magnitude() > 0) {
				hasPlayerStopped = false;
			}
		}

		//If player isn't moving, has kicked, and the ball isn't moving, reset game
		if (hasPlayerStopped) {
			ResetDyamicActors();
		}



	}

}