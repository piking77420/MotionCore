#pragma once

#include "motion_core_header.h"
#include "motion_core_typedef.h"

namespace MotionCore
{
    class CollisionSolver
    {
    public:

        CollisionSolver() = default;

        ~CollisionSolver() = default;

        void SolveCollsion(ObjectInfo* _objectInfo);
    private:
        
    };
}
