

#include "math/toolbox_typedef.hpp"

namespace MotionCore
{
	template <typename T>
	struct Aabb
	{
		Tbx::Vector3<T> min;
		Tbx::Vector3<T> max;

		Aabb(const Tbx::Vector3<T>& _min, const Tbx::Vector3<T>& _max)
			: min(_min), max(_max)
		{}

		Aabb() = default;

		~Aabb() = default;
	};

	template <typename T>
	INLINE bool GetSize(const Tbx::Vector3<T>& _min, const Tbx::Vector3<T>& _max)
	{
		return (_min - _max);
	}
	template <typename T>
	INLINE bool GetSize(const Aabb<T>& _aabb)
	{
		return GetSize(_aabb.min, _aabb.max);
	}

	template <typename T>
	INLINE bool Countain(const Tbx::Vector3<T>& _min, const Tbx::Vector3<T>& _max, const Tbx::Vector3<T>& _point)
	{
		return (_point.x >= _min.x && _point.x <= _max.x) &&
			(_point.y >= _min.y && _point.y <= _max.y) &&
			(_point.z >= _min.z && _point.z <= _max.z);
	}
	template <typename T>
	INLINE bool Countain(const Aabb<T>& _aabb, const Tbx::Vector3<T>& _point)
	{
		return Countain(_aabb.min, _aabb.max, _point);
	}

	// does AABB1 Contain ABBB 2
	template <typename T>
	INLINE bool Countain(const Aabb<T>& _aabb1, const Aabb<T>& _aabb2)
	{
		return Countain(_aabb1, _aabb2.min) && Countain(_aabb1, _aabb2.min);
	}


	// does _aabb1 countain _aabb2 ?
	template <typename T>
	INLINE bool Intersect(const Aabb<T>* _aabb1, const Aabb<T>* _aabb2)
	{
		return _aabb1->min.x <= _aabb2->min.x && _aabb1->min.y <= _aabb2->min.y && _aabb1->min.z <= _aabb2->min.z &&
			_aabb1->max.x >= _aabb2->max.x && _aabb1->max.y >= _aabb2->max.y && _aabb1->max.z >= _aabb2->max.z;
	}

	template <typename T>
	INLINE void Encapsulate(Aabb<T>* _aabb, const Tbx::Vector3<T>& _point)
	{
		// TO DO SIMD
		if (_point.x < _aabb->min.x) _aabb->min.x = _point.x;
		if (_point.y < _aabb->min.y) _aabb->min.y = _point.y;
		if (_point.z < _aabb->min.z) _aabb->min.z = _point.z;

		if (_point.x > _aabb->max.x) _aabb->max.x = _point.x;
		if (_point.y > _aabb->max.y) _aabb->max.y = _point.y;
		if (_point.z > _aabb->max.z) _aabb->max.z = _point.z;
	}

	template <typename T>
	INLINE void Encapsulate(Aabb<T>* _aabb1, Aabb<T>* _aabb2)
	{
		// TO DO SIMD
		if (_aabb2->min.x < _aabb1->min.x) _aabb1->min.x = _aabb2->min.x;
		if (_aabb2->min.y < _aabb1->min.y) _aabb1->min.y = _aabb2->min.y;
		if (_aabb2->min.z < _aabb1->min.z) _aabb1->min.z = _aabb2->min.z;

		if (_aabb2->max.x > _aabb1->max.x) _aabb1->max.x = _aabb2->max.x;
		if (_aabb2->max.y > _aabb1->max.y) _aabb1->max.y = _aabb2->max.y;
		if (_aabb2->max.z > _aabb1->max.z) _aabb1->max.z = _aabb2->max.z;
	}

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> GetExtend(const Aabb<T>& _aabb)
	{
		return (_aabb.max - _aabb.min) * static_cast<T>(0.5);
	}

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> GetCenter(const Aabb<T>& _aabb)
	{
		return _aabb.min + ((_aabb.max - _aabb.min) * static_cast<T>(0.5));
	}

	template <typename T>
	FORCEINLINE std::pair<Tbx::Vector3<T>, Tbx::Vector3<T>> GetCenterAndExtend(const Aabb<T>& _aabb)
	{
		const Tbx::Vector3<T> extend = GetExtend(_aabb);

		return { _aabb.min + (extend * static_cast<T>(0.5)), extend };
	}

	template <typename T>
	INLINE T GetVolume(const Aabb<T>& _aabb)
	{
		// TO DO SIMD
		const T dx = (_aabb.max.x - _aabb.min.x);
		const T dy = (_aabb.max.y - _aabb.min.y);
		const T dz = (_aabb.max.z - _aabb.min.z);

		return dx * dy * dz;
	}

	template <typename T>
	INLINE T GetSurfaceArea(const Aabb<T>& _aabb)
	{
		const Tbx::Vector3<T> size = GetSize(_aabb);
		
		return size.x * (size.y + size.z) + (size.y * size.z);
	}

	template <typename T>
	INLINE Tbx::Vector3<T> ClosestPoint(const Aabb<T>& _aabb, const Tbx::Vector3<T>& _point)
	{
		// TO DO SIMD
		Tbx::Vector3<T> result;

		result.x = std::max(_aabb.min.x, std::min(_point.x, _aabb.max.x));
		result.y = std::max(_aabb.min.y, std::min(_point.y, _aabb.max.y));
		result.z = std::max(_aabb.min.z, std::min(_point.z, _aabb.max.z));

		return result;
	}
}