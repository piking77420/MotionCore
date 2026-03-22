#pragma once
#include "Math/ToolBoxTypeDef.hpp"

namespace MotionCore
{
	template <typename T>
	struct Aabb
	{
		Tbx::Vector3<T> min;
		Tbx::Vector3<T> max;

		void FromCenterExtend(const Tbx::Vector3<T>& Center, const Tbx::Vector3<T>& Extend)
		{
			min = Center - Extend;
			max = Center + Extend;
		}

		Tbx::Vector3<T> GetSize() const
		{
			return (min - max);
		}

		Tbx::Vector3<T> GetExtend() const
		{
			return (max - min) * static_cast<T>(0.5);
		}

		Tbx::Vector3<T> GetCenter() const
		{
			return (min + max) * static_cast<T>(0.5);
		}

		bool Countain(const Tbx::Vector3<T>& _point) const
		{
			return (_point.x >= min.x && _point.x <= max.x) &&
				(_point.y >= min.y && _point.y <= max.y) &&
				(_point.z >= min.z && _point.z <= max.z);
		}

		bool Countain(const Aabb<T>& _right) const
		{
			return Countain(_right.min) && Countain(_right.max);
		}

		Aabb GetTransformed(const Tbx::Matrix4x4<T>& Matrix) const
		{
			const Tbx::Vector3 Center = GetCenter();
			const Tbx::Vector3 Extend = GetExtend();
			const Tbx::Vector4 Center4 = Matrix * Tbx::Vector4(Center.x, Center.y, Center.z, 1.0);
			const Tbx::Vector3 GlobalCenter = Tbx::Vector3(Center4.x, Center4.y, Center4.z);

			const Tbx::Vector3 Right = Tbx::Vector3(Matrix[0], Matrix[1], Matrix[2]) * Extend.x;
			const Tbx::Vector3 Up = Tbx::Vector3(Matrix[4], Matrix[5], Matrix[6]) * Extend.y;
			const Tbx::Vector3 Forward = Tbx::Vector3(Matrix[8], Matrix[9], Matrix[10]) * Extend.z;

			const double newIi =
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitX(), Right)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitX(), Up)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitX(), Forward));

			const double newIj =
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitY(), Right)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitY(), Up)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitY(), Forward));

			const double newIk =
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitZ(), Right)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitZ(), Up)) +
				std::abs(Tbx::Vector3<T>::Dot(Tbx::Vector3<T>::UnitZ(), Forward));

			Aabb AABB; 
			AABB.FromCenterExtend(GlobalCenter, Tbx::Vector3(newIi, newIj, newIk));
			return AABB;
		}
		
		Aabb(const Tbx::Vector3<T>& _min, const Tbx::Vector3<T>& _max) : min(_min), max(_max)
		{}

		Aabb() = default;

		~Aabb() = default;
	};


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
	INLINE void Encapsulate(Aabb<T>* _aabb1, const Aabb<T>* _aabb2)
	{
		if (_aabb2->min.x < _aabb1->min.x) _aabb1->min.x = _aabb2->min.x;
		if (_aabb2->min.y < _aabb1->min.y) _aabb1->min.y = _aabb2->min.y;
		if (_aabb2->min.z < _aabb1->min.z) _aabb1->min.z = _aabb2->min.z;

		if (_aabb2->max.x > _aabb1->max.x) _aabb1->max.x = _aabb2->max.x;
		if (_aabb2->max.y > _aabb1->max.y) _aabb1->max.y = _aabb2->max.y;
		if (_aabb2->max.z > _aabb1->max.z) _aabb1->max.z = _aabb2->max.z;
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