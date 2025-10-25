#pragma once

#include "MotionCoreHeader.h"
#include "RigidBody.hpp"

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

