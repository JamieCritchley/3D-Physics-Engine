#include "GoalFrame.h"

namespace PhysicsEngine::AssignmentScene {

	GoalFrame::GoalFrame(PxTransform pos): StaticActor(pos) {

		//Compound object made up of 2 posts and crossbar
		//No density required - static shapes
		CreateShape(PxBoxGeometry(PxVec3(0.05, 0.05, 3.76)), 0); //Crossbar - this is the cuboid that overlaps the join, so 7.32m goal mouth extended by 0.2m (post width) 
		CreateShape(PxBoxGeometry(PxVec3(0.05, 1.22, 0.05)), 0); //Posts - not overlapping join, so only needs to be 2.44m high
		CreateShape(PxBoxGeometry(PxVec3(0.05, 1.22, 0.05)), 0); //Posts - not overlapping join, so only needs to be 2.44m high

		//Setting local pos
		GetShape(0)->setLocalPose(PxTransform(PxVec3(0, 2.49, 0))); //Crossbar placed at goalmouth height + half of crossbar width
		GetShape(1)->setLocalPose(PxTransform(0, 1.22, 3.71)); //Posts placed at half goalmouth height (y) and half goalmouth width + half post width#
		GetShape(2)->setLocalPose(PxTransform(0, 1.22, -3.71)); //Posts placed at half goalmouth height (y) and half goalmouth width + half post width
	}
}