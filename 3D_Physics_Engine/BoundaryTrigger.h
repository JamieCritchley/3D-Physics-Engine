#pragma once
#include "StaticActor.h"
#include "PhysicsEngine.h"

namespace PhysicsEngine::AssignmentScene {

    class BoundaryTrigger : public Actors::StaticActor
    
    {
    public:
        //Creates a static box at pos, which is set as a trigger
        BoundaryTrigger(PxTransform pos, PxVec3 dimensions);
    };

}

