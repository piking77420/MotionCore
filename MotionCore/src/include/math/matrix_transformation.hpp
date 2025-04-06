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

	template <typename T>
	static Matrix4x4<T> LookAtRH(const Vector3<T>& _eye, const Vector3<T>& _center, const Vector3<T>& _up);

    template <typename T>
	static Matrix4x4<T> PerspectiveMatrix(const T fov, const T aspect, const T Near, const T Far);

    template <typename T>
	Matrix4x4<T> PerspectiveMatrixFlipYAxis(const T fov, const T aspect, const T Near, const T Far);

    template <class T>
	constexpr static Matrix4x4<T> OrthoGraphicMatrix(T left, T right, T bottom, T top, T zNear, T zFar);


	// operator

	template<typename T>
	Vector2<T> operator*(const Matrix2x2<T>& RESTRICT _m, const Vector2<T>& RESTRICT _vec);

	template<typename T>
	Vector3<T> operator*(const Matrix3x3<T>& RESTRICT _m, const Vector3<T>& RESTRICT _vec);

	template<typename T>
	Vector4<T> operator*(const Matrix4x4<T>& RESTRICT _m, const Vector4<T>& RESTRICT _vec);
}

#include "math/matrix_transformation.inl"