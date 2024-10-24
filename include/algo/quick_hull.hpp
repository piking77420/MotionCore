#pragma once
#include "algo_typedef.hpp"

namespace MotionCore
{
    QuickHullOut QuickHull(const BeginHull* _beginQuickHull);

    int FarestVertexFromFacesAndOutSideTheOrigin(const Tbx::Vector3f& p1, const Tbx::Vector3f& p2, const Tbx::Vector3f& p3,
                              const BeginHull* _beginQuickHull);

}

