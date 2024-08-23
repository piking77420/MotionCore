#pragma once

#include <math/toolbox.hpp>

// By convention all collision is been see from body1

#if defined(MOTIONCORE_EXPORT)
#define MOTION_CORE __declspec(dllexport)
#else
#define MOTION_CORE __declspec(dllimport)
#endif

#define FORCEINLINE __forceinline

#if defined(ASFREY_IMPORT)
#define ASFREY
#endif

namespace MotionCore
{
	using numeric = double;
	static_assert(std::is_floating_point_v<numeric>,"T must be a floating-point type");
	
	constexpr numeric NUMERICAL_ONE = static_cast<numeric>(1.f);  
	constexpr numeric NUMERICAL_ZERO = static_cast<numeric>(0.f);
	constexpr numeric NUMERICAL_MAX = std::numeric_limits<numeric>::max();
	constexpr numeric ESPILON = std::is_same_v<numeric,float> ? FLT_EPSILON : DBL_EPSILON;

	using Vec2 = Tbx::Vector2<numeric>;
	using Vec3 = Tbx::Vector3<numeric>;
	using Vec4 = Tbx::Vector4<numeric>;

	using Quat = Tbx::Quaternion<numeric>;
}