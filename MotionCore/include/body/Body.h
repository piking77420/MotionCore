
#pragma once
#include "PhysicMaterial.h"

namespace MotionCore
{
    struct Body
    {
        uint32_t id = -1;
        ToolBox::Vector2f position;
        ToolBox::Vector2f velocity;
        ToolBox::Vector2f acceleration;
        ToolBox::Vector2f force;
        float invMass = 1.f;
        PhysicMaterial physicMaterial;
    };
}

