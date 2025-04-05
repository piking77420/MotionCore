#pragma once
#include <string>

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
		operator Quaternion<U>() const;

		FORCEINLINE static CONSTEVAL Quaternion Identity();

		FORCEINLINE DataType MagnitudeSquare() const;

		FORCEINLINE DataType Magnitude() const;

		FORCEINLINE Quaternion Conjugate() const;

		FORCEINLINE static constexpr DataType Dot(const Quaternion& q1, const Quaternion& q2);

		FORCEINLINE Quaternion Normalize() const;

		Quaternion Inverse() const;

		// thanks to Vlad
		// https://stackoverflow.com/questions/12088610/conversion-between-euler-quaternion-like-in-unity3d-engine
		static Vec3 ToEulerAngles(const Quaternion& q);

		static Quaternion FromEuler(const Vec3& eulerAngle);

		static Quaternion LookRotation(Vec3 _Nforward, Vec3 _Nupwards);


		static inline void SinCos(const Vector4<T>& angles, Vector4<T>& sinOut, Vector4<T>& cosOut)
		{
			for (int i = 0; i < 4; ++i) {
				sinOut[i] = std::sin(angles[i]);
				cosOut[i] = std::cos(angles[i]);
			}
		}

		/*
		static Quaternion FromEuler(const Vector4<T>& _vector4) // <Pitch, Yaw, Roll, 0>
		{
			constexpr Vector4<T>  Sign = { 1.0f, -1.0f, -1.0f, 1.0f };

			// Half the angles
			Vector4<T> halfAngles = {_vector4[0] * 0.5f, _vector4[1] * 0.5f, _vector4[2] * 0.5f, _vector4[3] * 0.5f};

			// Calculate sine and cosine of half-angles
			Vector4<T> sinAngles, cosAngles;
			SinCos(halfAngles, sinAngles, cosAngles);

			Vector4<T> P0 = Permute<T,TBX_PERMUTE_0X, TBX_PERMUTE_1X, TBX_PERMUTE_1X, TBX_PERMUTE_1X>(sinAngles, cosAngles);
			Vector4<T> Y0 = Permute<T,TBX_PERMUTE_1Y, TBX_PERMUTE_0Y, TBX_PERMUTE_1Y, TBX_PERMUTE_1Y>(sinAngles, cosAngles);
			Vector4<T> R0 = Permute<T,TBX_PERMUTE_1Z, TBX_PERMUTE_1Z, TBX_PERMUTE_0Z, TBX_PERMUTE_1Z>(sinAngles, cosAngles);

			Vector4<T> P1 = Permute<T,TBX_PERMUTE_0X, TBX_PERMUTE_1X, TBX_PERMUTE_1X, TBX_PERMUTE_1X>(cosAngles, sinAngles);
			Vector4<T> Y1 = Permute<T,TBX_PERMUTE_1Y, TBX_PERMUTE_0Y, TBX_PERMUTE_1Y, TBX_PERMUTE_1Y>(cosAngles, sinAngles);
			Vector4<T> R1 = Permute<T,TBX_PERMUTE_1Z, TBX_PERMUTE_1Z, TBX_PERMUTE_0Z, TBX_PERMUTE_1Z>(cosAngles, sinAngles);

			// Compute quaternions
			Vector4<T> Q1 = P1 * Sign;
			Vector4<T> Q0 = P0 * Y0;
			Q1 = Q1 * Y1;
			Q0 = Q0 * R0;
			const Vector4<T> Q = (Q1 * R1)  + Q0;

			return {Q.x, Q.y, Q.z, Q.w};
		}*/

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