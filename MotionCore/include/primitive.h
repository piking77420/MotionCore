#pragma once

#include "motion_core_header.h" 


namespace MotionCore
{

    struct Sphere 
    {
        numeric radius;
    };

    struct AABB
    {
        Vec3 extend;
    };

    struct Caspule
    {
        numeric height;
        numeric radius;
    };

    inline AABB RotateAABB(const AABB& _aabb, const Quat& quat)
    {
        
    }
}
