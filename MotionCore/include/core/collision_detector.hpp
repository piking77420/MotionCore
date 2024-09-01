#pragma once

#include "motion_core_header.h"
#include "motion_core_typedef.h"

namespace MotionCore
{
    class CollisionDetector
    {
    public:

        CollisionDetector() = default;

        ~CollisionDetector() = default;

        void FoundCollision(MotionCoreContext* _objectInfo);
    private:

        MotionCoreContext* motionCoreContext = nullptr;
        
        void ComputeWorldABBB(Body* _body) const;

        MotionCore::AABB GetLocalAABB(Body* _body) const;

       
    };
}

