#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdint.h>
#include <cassert>
#include <float.h>


#ifndef FORCEINLINE
#if defined(_MSC_VER)
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCEINLINE inline __attribute__((always_inline))
#else
#define FORCEINLINE inline
#endif
#endif

#define INLINE inline

#if defined(__clang__)
#define RESTRICT __restrict

#elif defined(__GNUC__) || defined(__GNUG__)
#define RESTRICT __restrict__

#elif defined(_MSC_VER)
#define RESTRICT __restrict

#endif

// C++20 (and later) code
#if __cplusplus >= 202002L

#define CONSTEVAL consteval

#else
#define CONSTEVAL constexpr

#endif

namespace Tbx
{
    template<typename T>
    CONSTEVAL T Epsilon();

    template<>
    CONSTEVAL float Epsilon<float>() {
        return static_cast<float>(FLT_EPSILON);
    }

    template<>
    CONSTEVAL double Epsilon<double>() {
        return static_cast<double>(DBL_EPSILON);
    }

    template<typename T>
    CONSTEVAL T IsEqualValue();

    template<>
    CONSTEVAL float IsEqualValue<float>() {
        return static_cast<float>(1e-2);
    }

    template<>
    CONSTEVAL double IsEqualValue<double>() {
        return static_cast<double>(1e-7);
    }


    template<typename T>
    FORCEINLINE constexpr bool IsEqual(T _value, T _compare, T epsilon = IsEqualValue<T>())
    {
        return std::abs(_value - _compare) <= epsilon;
    }

    template<typename T>
    FORCEINLINE static constexpr T NormalizeRadian(T angle)
    {
        angle = std::fmod(angle, static_cast<T>(2 * M_PI));

        if (angle < static_cast<T>(0))
            angle += static_cast<T>(2 * M_PI);

        return angle;
    }

    constexpr float fDeg2Rad{ static_cast<float>(M_PI) / 180.0f };
    constexpr float fRad2Deg{ 57.29578f };

    constexpr double dDeg2Rad{ static_cast<double>(M_PI) / 180.0 };
    constexpr double dRad2Deg{ 57.29578 };


}

#define POWER(x) x * x