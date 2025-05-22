#pragma once

#include "motion_core_header.h"
#include "rigid_body.hpp"

namespace MotionCore
{
    class BodyIntegrator
    {
    public:

        BodyIntegrator();

        ~BodyIntegrator();

        void Integrate(RigidBody* _bodyBegin, uint32_t _BodyCount);
        
    private:
        
    };    
}

