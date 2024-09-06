#include "primitive.h"

MotionCore::AABB MotionCore::GetRotatedAABB(const AABB& _aabb, const Quat& quat)
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