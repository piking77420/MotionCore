#pragma once

#include "toolbox_typedef.hpp"

namespace Tbx
{
	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix2x2<T> Rotation2x2(T _angle);

	template <typename T>
	static FORCEINLINE Matrix2x2<T> Scale2x2(T _factor);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Trs3x3(const Tbx::Vector2<T>& _translation, T _angle ,T _scale);

	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3X(T _angleX);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3Y(T _angleY);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3Z(T _angleZ);

	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3(T _angleX, T _angleY, T _angleZ);

	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3(const Tbx::Vector3<T>& _eulerAngles);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Rotation3x3(const Quaternion<T>& _quaternion);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Scale3x3(T _factorX, T _factorY, T _factorZ);

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Scale3x3(const Tbx::Vector3<T>& _factorxyz);

	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix4x4<T> Rotation4x4(T _angleX, T _angleY, T _angleZ);

	template <typename T>
	static FORCEINLINE Matrix4x4<T> Rotation4x4(const Quaternion<T>& _quaternion);

	template <typename T>
	static FORCEINLINE Matrix4x4<T> Scale4x4(T _factorX, T _factorY, T _factorZ);

	template <typename T>
	static FORCEINLINE Matrix4x4<T> Trs4x4(const Tbx::Vector3<T>& _translation, const Tbx::Vector3<T>& _eulerAngles, const Tbx::Vector3<T>& _scale);

	template <typename T>
	static FORCEINLINE Matrix4x4<T> Trs4x4(const Tbx::Vector3<T>& _translation, const Quaternion<T>& _rotation, const Tbx::Vector3<T>& _scale);
}

#include "math/matrix_transformation.inl"