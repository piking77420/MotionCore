#pragma once

#include "motion_core_header.h"

namespace MotionCore
{
    struct BeginHull
    {
        void* _verticiesData = nullptr;
        uint32_t _nbrOfVerticies = 0;
        uint32_t _vertexSize = 0;

        uint32_t _vectorSize = 0;
        uint32_t _vectorDataSize = 0;
        uint32_t _positionOffSet = 0;
        
    };

    struct QuickHullOut
    {
        void* _verticies = nullptr;
        uint32_t nbrOfPoint = 0;
    };


    struct SATSphereSphereOut
    {
        numeric depth;
        Vec3 normal;
    };

}

