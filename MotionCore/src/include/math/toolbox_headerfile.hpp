#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <array>
#include <string>

#define TOOLBOX_INLINE _forceinline 
#define EPSILON 1e-6

static constexpr float fEpsilon = 1e-6f;
static constexpr double dEpsilon = 1e-6;

template<typename T>
constexpr bool IsEqual(T _value, T _compare, T epsilon = static_cast<T>(EPSILON))
{
    return std::abs(_value - _compare) <= epsilon;
}

constexpr float Deg2Rad { static_cast<float>(M_PI) / 180.0f};
constexpr float Rad2Deg {57.29578f};