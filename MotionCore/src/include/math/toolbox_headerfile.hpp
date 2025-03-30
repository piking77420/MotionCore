#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdint.h>
#include <cassert>

#include "simd_define.h"

#if defined(MOTION_DYNAMIC_IMAGE)
#ifdef MOTION_CORE_EXPORTS
#define MOTION_CORE_API __declspec(dllexport)
#elif MOTION_CORE_IMPORTS
#define MOTION_CORE_API __declspec(dllimport)
#else
#define MOTION_CORE_API
#endif
#else
#define MOTION_CORE_API
#endif

#define FORCEINLINE __forceinline
#define EPSILON 1e-6

#if defined(__clang__)
#define RESTRICT __restrict

#elif defined(__GNUC__) || defined(__GNUG__)
#define RESTRICT __restrict__

#elif defined(_MSC_VER)
#define RESTRICT __restrict

#endif

static constexpr float fEpsilon = 1e-6f;
static constexpr double dEpsilon = 1e-6;

template<typename T>
constexpr bool IsEqual(T _value, T _compare, T epsilon = static_cast<T>(EPSILON))
{
    return std::abs(_value - _compare) <= epsilon;
}

constexpr float fDeg2Rad { static_cast<float>(M_PI) / 180.0f};
constexpr float fRad2Deg {57.29578f};

constexpr double dDeg2Rad{ static_cast<double>(M_PI) / 180.0 };
constexpr double dRad2Deg{ 57.29578 };
