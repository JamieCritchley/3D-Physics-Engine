#pragma once

#include "PhysicsEngine.h"

#include "StaticActor.h"
#include <string>

namespace PhysicsEngine::AssignmentScene {

    class GoalFrame : public ActorTemplates::StaticActor

    {
    public:

        //Standard size football goal frame 
        //Is a compound object made from cuboids
        //Position is the point halfway inbetween the bottom of the two goalposts
        GoalFrame(PxTransform pos = PxTransform(PxIdentity));

    };
}

