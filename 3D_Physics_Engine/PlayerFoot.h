#pragma once
#include "DynamicActor.h"

namespace PhysicsEngine::AssignmentScene {

    class PlayerFoot : public Actors::DynamicActor
    {
    public:

        //Compound object used for Player object
        //Position set to identity if not provided - its placed at the top of the lower leg
        PlayerFoot(PxTransform pos = PxTransform(PxIdentity));
    };
}
