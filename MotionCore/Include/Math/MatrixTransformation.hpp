#pragma once

#include "ToolBoxTypeDef.hpp"

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

	template<typename T>
	Matrix4x4<T> ToMatrix4x4(const Matrix3x3<T>& _M3)
	{
		Matrix4x4<T> m4;

		m4[0] = _M3[0];
		m4[1] = _M3[1];
		m4[2] = _M3[2];
		m4[3] = static_cast<T>(0);

		m4[4] = _M3[3];
		m4[5] = _M3[4];
		m4[6] = _M3[5];
		m4[7] = static_cast<T>(0);

		m4[8] = _M3[6];
		m4[9] = _M3[7];
		m4[10] = _M3[8];
		m4[11] = static_cast<T>(0);

		m4[12] = static_cast<T>(0);
		m4[13] = static_cast<T>(0);
		m4[14] = static_cast<T>(0);
		m4[15] = static_cast<T>(0);

		return m4;
	}

	template<typename T>
	Matrix3x3<T> ToMatrix3x3(const Matrix4x4<T>& _M4)
	{
		return Matrix3x3<T>(
			Tbx::Vector3<T>(_M4[0], _M4[1], _M4[2]),
			Tbx::Vector3<T>(_M4[4], _M4[5], _M4[6]),
			Tbx::Vector3<T>(_M4[8], _M4[9], _M4[10]));
	}

}

#include "Math/MatrixTransformation.inl"