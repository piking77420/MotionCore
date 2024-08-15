#pragma once

#include <math/toolbox.hpp>

// By convention all collision is been see from body1

#if defined(MOTIONCORE_EXPORT)
#define MOTION_CORE __declspec(dllexport)
#else
#define MOTION_CORE __declspec(dllimport)
#endif

namespace MotionCore
{
	using numeric = float;

	using Vec2 = Tbx::Vector2<numeric>;
	using Vec3 = Tbx::Vector3<numeric>;
	using Vec4 = Tbx::Vector4<numeric>;

	using Quat = Tbx::Quaternion<numeric>;
}