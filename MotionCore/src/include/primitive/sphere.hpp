
#include "math/toolbox_typedef.hpp"

namespace MotionCore
{
	template <typename T>
	struct Sphere
	{
		Tbx::Vector3<T> center;
		T radius;
	};

	template <typename T>
	FORCEINLINE bool GetSize(const Sphere<T>& _sphere)
	{
		return _sphere.radius * static_cast<T>(2);
	}

	template <typename T>
	FORCEINLINE bool Countain(const Sphere<T>& _sphere, const Tbx::Vector3<T>& _point)
	{
		return (_point - _sphere.center).MagnitudeSquare() <= POWER(_sphere.radius);
	}

	template <typename T>
	FORCEINLINE const Tbx::Vector3<T> ClosestPoint(const Sphere<T>& _sphere, const Tbx::Vector3<T>& _point)
	{
		const Tbx::Vector3<T> vecSphereToPoint = (_point - _sphere.center);

		return vecSphereToPoint.Normalize() * vecSphereToPoint.Magnitude();
	}

	template <typename T>
	FORCEINLINE bool Intersect(const Sphere<T>& _sphere1, const Sphere<T>& _sphere2)
	{
		const Tbx::Vector3<T> vec = _sphere2 - _sphere1;
		const T radSum = _sphere1.radius + _sphere2.radius;

		return vec.MagnitudeSquare() <= POWER(radSum);
	}
}