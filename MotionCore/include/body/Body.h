
#pragma once
#include "physic_material.h"

namespace MotionCore
{
    struct Body
    {
        uint32_t id = -1;
        Tbx::Vector2f position;
        Tbx::Vector2f velocity;
        Tbx::Vector2f acceleration;
        Tbx::Vector2f force;
        float invMass = 1.f;
        PhysicMaterial physicMaterial;
    };
}

