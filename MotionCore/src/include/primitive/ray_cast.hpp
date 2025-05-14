
#include "math/toolbox_typedef.hpp"

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
	INLINE int RaySphere(const Tbx::Vector3<T>& _rayOrigin, const Tbx::Vector3<T>& _Direction,
		const Tbx::Vector3<T>& _sphereOrigin, T _sphereRadius, T* x1, T* x2)
	{
		const Tbx::Vector3<T> newRayOrigin = _rayOrigin - _sphereOrigin;

		const T a = _Direction.Magnitude();
		


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