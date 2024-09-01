#pragma once

#include "motion_core_header.h" 


namespace MotionCore
{

    struct Sphere 
    {
        Vec3 center;
        numeric radius;
    };

    struct AABB
    {
        Vec3 min;
        Vec3 max;
    };

    struct OBB
    {
        Vec3 center;
        Vec3 extend;
        Tbx::Matrix3x3<numeric> orientationMatrix = Tbx::Matrix3x3<numeric>::Identity();
    };

    struct Caspule
    {
        Vec3 center;
        numeric height;
        numeric radius;
    };

    struct Plane
    {
        Vec3 normal;
        numeric distance;
    };

    struct RayCast
    {
        Vec3 ori;
        Vec3 dir;
        numeric distance = std::numeric_limits<numeric>::max();
    };

    FORCEINLINE AABB GetRotatedAABB(const AABB& _aabb, const Quat& quat)
    {   
        Tbx::Matrix3x3<numeric> matrix;
        Tbx::RotationMatrix3D(quat, &matrix);
        AABB returnAbb; 
        
        for (size_t i = 0; i < Tbx::Matrix3x3<numeric>::Size; i++)
        {
            for (size_t j = 0; j < Tbx::Matrix3x3<numeric>::Size; j++)
            {
                const numeric e = _aabb.min[j] * matrix[i][j];
                const numeric f = _aabb.max[j] * matrix[i][j];
                if (e < f )
                {
                    returnAbb.min[i] += e;
                    returnAbb.max[i] += f;
                }
                else
                {
                    returnAbb.min[i] += f;
                    returnAbb.max[i] += e;
                }
            }
        }

        return returnAbb;
    }

    
    FORCEINLINE Vec3 GetExtend(const AABB& _abb)
    {
        const Vec3 center = (_abb.max - _abb.min) * static_cast<numeric>(0.5);
        return _abb.max - center;
    }

   
}
