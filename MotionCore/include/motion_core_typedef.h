
#pragma once
#include "physic_material.h"

namespace MotionCore
{
    struct CreateBodyInfo 
    {
        float mass = 1.f;
    };
    
    struct PhyscicalMaterial
    {
        float drag = 0.99f;
    };
    
    struct Body
    {
        uint32_t id = -1;
        float invMass = 1.f;
        PhyscicalMaterial physcicalMaterial;

        Tbx::Vector3f position;
        Tbx::Vector3f velocity;
        Tbx::Vector3f acceleration;
        Tbx::Vector3f force;
    };

    
    struct Sphere
    {
        Body body;
        float radius = 10.f;
    };

}

