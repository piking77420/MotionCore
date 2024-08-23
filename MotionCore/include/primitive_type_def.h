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

    struct OBB
    {
        Vec3 extend;
        Tbx::Matrix3x3<numeric> orientationMatrix = Tbx::Matrix3x3<numeric>::Identity();
    };

    struct Caspule
    {
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
                returnAbb.extend[i] += std::abs(matrix[j][i]) * _aabb.extend[j];
            }
        }

        return returnAbb;
    }

    

   
}
