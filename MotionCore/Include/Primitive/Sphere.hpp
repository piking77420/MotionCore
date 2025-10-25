
#include "Math/ToolBoxTypeDef.hpp"


namespace MotionCore
{
	template <typename T>
	struct Sphere
	{
		T radius;
		Tbx::Vector3<T> position;
	};

	template <typename T>
	FORCEINLINE T GetSize(T radius)
	{
		return radius * static_cast<T>(2);
	}

	template <typename T>
	FORCEINLINE bool Countain(const Tbx::Vector3<T>& _sphere1Pos, T radius1 , 
		const Tbx::Vector3<T>& _point)
	{
		return (_point - _sphere1Pos).MagnitudeSquare() <= POWER(radius1);
	}

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> ClosestPoint(const Tbx::Vector3<T>& _spherePos1, T radius1, const Tbx::Vector3<T>& _point)
	{
		const Tbx::Vector3<T> vecSphereToPoint = (_point - _spherePos1);

		return vecSphereToPoint.Normalize() * radius1;
	}

	template <typename T>
	FORCEINLINE bool Intersect(const Tbx::Vector3<T>& _spherePos1, T _radius1, const Tbx::Vector3<T>& _spherePos2, T _radius2)
	{
		const Tbx::Vector3<T> vec = _spherePos2 - _spherePos1;
		const T radSum = _radius1 + _radius2;

		return vec.MagnitudeSquare() <= POWER(radSum);
	}
}