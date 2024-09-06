#pragma once

#include "motion_core_header.h"


namespace MotionCore
{
    // ABB // 
    struct OBB
    {
        Vec3 center;
        Vec3 extend;
        Tbx::Matrix3x3<numeric> orientationMatrix = Tbx::Matrix3x3<numeric>::Identity();
    };   
}
