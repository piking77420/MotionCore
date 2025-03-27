#pragma once

#include <math/toolbox.hpp>

// By convention all collision is been see from body1
namespace MotionCore
{
	using numeric = double;

	using Vec2 = Tbx::Vector2<numeric>;
	using Vec3 = Tbx::Vector3<numeric>;
	using Vec4 = Tbx::Vector4<numeric>;

	using Quat = Tbx::Quaternion<numeric>;
}