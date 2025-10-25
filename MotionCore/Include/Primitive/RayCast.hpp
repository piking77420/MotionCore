#pragma once

#include "Math/ToolBoxTypeDef.hpp"

namespace MotionCore
{
	template <typename T>
	struct RayCast
	{
		Tbx::Vector3<T> origin;
		T lenght;
		Tbx::Vector3<T> direction;
	};

	// 0 no hit
	// 1 x1 hit
	// 2 x1, x2 hit
	template <typename T>
	INLINE int RaySphere(const Tbx::Vector3<T>& _rayOrigin, const Tbx::Vector3<T>& _rayNDirection,
		const Tbx::Vector3<T>& _sphereOrigin, T _sphereRadius, T* const _t, Tbx::Vector3<T>* _q)
	{
		const Tbx::Vector3<T> newRayOrigin = _rayOrigin - _sphereOrigin;
		const T b = Tbx::Vector3<T>::DotProduct(newRayOrigin, _rayNDirection);
		const T c = Tbx::Vector3<T>::DotProduct(newRayOrigin, newRayOrigin) - _sphereRadius * _sphereRadius;
		
		if (b > static_cast<T>(0) && c > static_cast<T>(0)) return 0;

		T discriminant = b * b - c * c;

		if (discriminant < static_cast<T>(0))
			return 0;

		*_t = -b - std::sqrt(discriminant);

		if  (*_t < static_cast<T>(0))
			*_t = static_cast<T>(0);

		*_q = _rayOrigin + _rayNDirection * (*_t);
		
		// TO DO
		return false;
	}

	template <typename T>
	INLINE bool RayABBB(const Tbx::Vector3<T>& _rayOrigin, const Tbx::Vector3<T>& _Direction,
		const Tbx::Vector3<T>& _min, const Tbx::Vector3<T>& _max)
	{
		// TO DO
		return false;
	}

	template <typename T>
	INLINE bool RayCapsule(const Tbx::Vector3<T>& _rayOrigin, const Tbx::Vector3<T>& _Direction,
		const Tbx::Vector3<T>& _capsuleOrigin, T _capsuleRadius, T _capsuleHeight)
	{
		// TO DO
		return false;
	}


}