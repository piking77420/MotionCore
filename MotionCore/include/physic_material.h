#pragma once

#include "motion_core_header.h"

namespace MotionCore
{
    struct PhysicMaterial
    {
        numeric drag = static_cast<numeric>(0.99);
        numeric restitutionCoef = static_cast<numeric>(0.99);
    };
}

 