#pragma once

#include "toolbox_typedef.hpp"

namespace Tbx
{
	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix2x2<T> Rotation2x2(T _angle);

	template <typename T>
	static FORCEINLINE Matrix2x2<T> Scale2x2(T _factor);


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

	template <typename T>
	static FORCEINLINE Matrix3x3<T> Scale3x3(T _factorX, T _factorY, T _factorZ);

	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix4x4<T> Rotation4x4(T _angleX, T _angleY, T _angleZ);
}

#include "math/matrix_transformation.inl"