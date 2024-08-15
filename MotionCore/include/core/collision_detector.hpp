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

        void FoundCollision(ObjectInfo* objectInfo);
    private:
        struct SphereCollisionInfo
        {
            // collision normal from body1
            Vec3 normal;
            numeric depth;
            bool hitResult = false;
        };
        
        SphereCollisionInfo SphereCollision(numeric _sphereRadius1, numeric _sphereRadius2, const Vec3& _bodyPos1, const Vec3& _bodyPos2);
    };
}

