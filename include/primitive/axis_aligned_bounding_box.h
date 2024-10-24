#pragma once

#include "motion_core_header.h"


namespace MotionCore
{
    // ABB // 
    struct AABB
    {
        Vec3 min;
        Vec3 max;
        
        AABB GetRotatedAABB(const Quat& quat);

        FORCEINLINE Vec3 GetExtend() const
        {
            const Vec3 center = (max - min) * static_cast<numeric>(0.5);
            return max - center;
        }

        void GrowToInclude(const AABB& _other);

        numeric GetGrowVolume(const AABB& _other) const;

        bool Overlaps(const AABB& _other) const;

        numeric GetArea() const;
    };   
}

