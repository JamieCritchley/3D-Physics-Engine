#pragma once
#include "ConvexMesh.h"

namespace PhysicsEngine::CustomScene
{
    class ExtrudedHexagon : public Actors::MeshActors::ConvexMesh
    {
    public:

        //Creates a hexagonal prism with inputs of:
        //Side length, m
        //Height, m
        //Pose (optional)
        //Density (optional)
        ExtrudedHexagon(PxReal sideLength, PxReal height, PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f);
    };
}

