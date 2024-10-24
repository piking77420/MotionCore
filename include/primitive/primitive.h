#pragma once

#include "motion_core_header.h"
#include "sphere.h"
#include "axis_aligned_bounding_box.h"
#include "oriented_bounding_box.h"
#include "capsule.h"


namespace MotionCore
{
    //
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
}
