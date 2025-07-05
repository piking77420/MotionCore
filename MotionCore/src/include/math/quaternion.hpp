#pragma once
#include <string>

#include "toolbox_typedef.hpp"
#include "toolbox_typedef.hpp"
#include "vector3.hpp"

namespace Tbx
{

	template <typename T>
	struct Quaternion
	{
		using DataType = T;
		using Vec3 = Vector3<DataType>;

		DataType real;
		Vec3 imaginary;

		constexpr Quaternion() = default;

		explicit constexpr Quaternion(const DataType _real, const Vec3& _vec);

		explicit constexpr Quaternion(const DataType _real, const DataType _x, const DataType _y, const DataType _z);

		~Quaternion() = default;

		template<typename U>
		explicit operator Quaternion<U>() const;

		FORCEINLINE static CONSTEVAL Quaternion Identity();

		FORCEINLINE DataType MagnitudeSquare() const;

		FORCEINLINE DataType Magnitude() const;

		FORCEINLINE Quaternion Conjugate() const;

		FORCEINLINE static constexpr DataType Dot(const Quaternion& q1, const Quaternion& q2);

		FORCEINLINE Quaternion Normalize() const;

		Quaternion Inverse() const;

		// thanks to Vlad
		// https://stackoverflow.com/questions/12088610/conversion-between-euler-quaternion-like-in-unity3d-engine
		static Quaternion<T>::Vec3 ToEulerAngles(const Quaternion& q);

		static Quaternion FromEuler(const Vec3& eulerAngle);

		static Quaternion LookRotation(Vec3 _Nforward, Vec3 _Nupwards);


		static inline void SinCos(const Vector4<T>& angles, Vector4<T>& sinOut, Vector4<T>& cosOut)
		{
			for (int i = 0; i < 4; ++i) {
				sinOut[i] = std::sin(angles[i]);
				cosOut[i] = std::cos(angles[i]);
			}
		}


		static Quaternion FromMatrix(const Matrix3x3<T>& matrix);

		FORCEINLINE static void ToAxisAngle(const Quaternion& _q, Vec3* _axis, T* _angle);

		FORCEINLINE static Quaternion FromAxisAngle(Vec3 _axis, T _angle);

		template<typename U>
		static FORCEINLINE Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, U t);
		
		template<typename U>
		static FORCEINLINE Quaternion Nlerp(const Quaternion& q1, const Quaternion& q2, U t);
		
		FORCEINLINE Quaternion operator+(const Quaternion& _other);

		FORCEINLINE Quaternion operator-(const Quaternion& _other);

		FORCEINLINE Quaternion operator*(const Quaternion& _other) const;

		FORCEINLINE Vec3 operator*(const Vec3& _vec) const;

		FORCEINLINE Quaternion operator+(const Vec3& _vec) const;

		FORCEINLINE Quaternion operator+(T _value);

		FORCEINLINE Quaternion operator-(T _value);

		FORCEINLINE Quaternion operator*(T _value);

		FORCEINLINE Quaternion operator/(T _value);

		FORCEINLINE void operator+=(const Quaternion& _other);

		FORCEINLINE void operator-=(const Quaternion& _other);

		FORCEINLINE void operator*=(const Quaternion& _other);

		FORCEINLINE void operator+=(T _value);

		FORCEINLINE void operator-=(T _value);

		FORCEINLINE void operator*=(T _value);

		FORCEINLINE void operator/=(T _value);

		FORCEINLINE bool operator==(const Quaternion& _other) const;

		FORCEINLINE bool operator!=(const Quaternion& _other) const;

	};

	
}

#include "math/quaternion.inl"