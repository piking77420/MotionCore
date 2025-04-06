#include "matrix_transformation.hpp"

namespace Tbx
{
	template <typename T>
	Matrix2x2<T> Rotation2x2(T _angle)
	{
		return {

			// m00			 m10
			std::cos(_angle), -std::sin(_angle),
			// m01			 m11
			std::sin(_angle), std::cos(_angle)
		};
	}

	template<typename T>
	Matrix2x2<T> Scale2x2(T _factor)
	{
		return {

			// m00			 m10
			_factor, static_cast<T>(0),
			// m01			 m11
			static_cast<T>(0), _factor
		};
	}

	template<typename T>
	Matrix3x3<T> Trs3x3(const Tbx::Vector2<T>& _translation, T _angle, T _scale)
	{
		Matrix2x2<T> rotScaleMatrix = Rotation2x2(_angle) * Scale2x2(_scale);


		return {

			// m00			 m10			m20
			rotScaleMatrix[0], rotScaleMatrix[1], static_cast<T>(0),
			// m01			 m11			m21
			rotScaleMatrix[2],  rotScaleMatrix[3], static_cast<T>(0),
			// m02			 m12			m22
			_translation[0], _translation[1], static_cast<T>(1),
		};
	}


	template<typename T>
	Matrix3x3<T> Rotation3x3X(T _angleX)
	{
		return {

			// m00			 m10			m20
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			// m01			 m11			m21
			static_cast<T>(0), std::cos(_angleX) , std::sin(_angleX),
			// m02			 m12			m22
			static_cast<T>(0), -std::sin(_angleX) , std::cos(_angleX),
		};
	}

	template<typename T>
	Matrix3x3<T> Rotation3x3Y(T _angleY)
	{
		return {

			// m00			 m10			m20
			std::cos(_angleY), static_cast<T>(0), -std::sin(_angleY),
			// m01			 m11			m21
			static_cast<T>(0), static_cast<T>(1) , static_cast<T>(0),
			// m02			 m12			m22
			std::sin(_angleY), static_cast<T>(0) , std::cos(_angleY),
		};
	}

	template<typename T>
	Matrix3x3<T> Rotation3x3Z(T _angleZ)
	{
		return {

			// m00			 m10			m20
			std::cos(_angleZ), std::sin(_angleZ), static_cast<T>(0),
			// m01			 m11			m21
			-std::sin(_angleZ), std::cos(_angleZ) , static_cast<T>(0),
			// m02			 m12			m22
			static_cast<T>(0), static_cast<T>(0) , static_cast<T>(1),
		};
	}


	template<typename T>
	Matrix3x3<T> Rotation3x3(T _angleX, T _angleY, T _angleZ)
	{
		return Rotation3x3X(_angleX) * Rotation3x3Y(_angleY) * Rotation3x3Z(_angleZ);
	}

	template<typename T>
	Matrix3x3<T> Rotation3x3(const Tbx::Vector3<T>& _eulerAngles)
	{
		return Rotation3x3(_eulerAngles.x, _eulerAngles.y, _eulerAngles.z);
	}

	template <typename T>
	static Matrix3x3<T> Rotation3x3(const Quaternion<T>& _quaternion)
	{	
		const T b = _quaternion.imaginary.x;
		const T c = _quaternion.imaginary.y;
		const T d = _quaternion.imaginary.z;
		const T a = _quaternion.real;

		const T aa = a * a;
		const T bb = b * b;
		const T cc = c * c;
		const T dd = d * d;

		const T bc = b * c;
		const T ad = a * d;
		const T bd = b * d;
		const T ac = a * c;
		const T ab = a * b;
		const T cd = c * d;	


		return
		{
			aa + bb - cc - dd, static_cast<T>(2) * (bc + ad), static_cast<T>(2) * (bd - ac),
			static_cast<T>(2) * (bc - ad), aa - bb + cc - dd, static_cast<T>(2) * (cd + ab),
			static_cast<T>(2)* (bd + ac), static_cast<T>(2) * (cd - ab), aa - bb - cc + dd
		};
	}

	template<typename T>
	Matrix3x3<T> Scale3x3(T _factorX, T _factorY, T _factorZ)
	{
		return {

			// m00			 m10			m20
			_factorX, static_cast<T>(0), static_cast<T>(0),
			// m01			 m11			m21
			static_cast<T>(0), _factorY , static_cast<T>(0),
			// m02			 m12			m22
			static_cast<T>(0), static_cast<T>(0) , _factorZ,
		};
	}

	template<typename T>
	Matrix3x3<T> Scale3x3(const Tbx::Vector3<T>& _factorxyz)
	{
		return Scale3x3(_factorxyz.x, _factorxyz.y, _factorxyz.z);
	}

	template<typename T>
	static void ToAxisAngle(const Matrix3x3<T>& _m, Tbx::Vector3<T>* _axis, T* _angle)
	{
		Tbx::Vector3<T> trace;
		_m.Trace(trace.GetPtr());

		const T traceV = trace.x + trace.y + trace.z;
		const T angle = (std::acos(traceV) - static_cast<T>(1)) * static_cast<T>(0.5);


		const T m57 = (_m[5] - _m[7]);
		const T m67 = (_m[6] - _m[2]);
		const T m13 = (_m[1] - _m[3]);

		const T invN = static_cast<T>(1) / std::sin(angle) * static_cast<T>(0.5);

		*_axis = Tbx::Vector3<T>(m57 * invN, m67 * invN, m13 * invN);
		*_angle = angle;
	}

	template <typename T>
	Matrix4x4<T> Rotation4x4(T _angleX, T _angleY, T _angleZ)
	{
		const Matrix3x3<T> rotation3x3 = Rotation3x3(_angleX, _angleY, _angleZ);

		return 
		{
			// m00			 m10					m20                m30
			rotation3x3[0], rotation3x3[1], rotation3x3[2], static_cast<T>(0),
			// m01			 m11					m21				   m31
			rotation3x3[3], rotation3x3[4] , rotation3x3[5], static_cast<T>(0),
			// m02			 m12					m22				   m32
			rotation3x3[6], rotation3x3[7] , rotation3x3[8], static_cast<T>(0),
			// m03			 m13					m23				   m33
			static_cast<T>(0), static_cast<T>(0) , static_cast<T>(0), static_cast<T>(1)
		};
	}


	template <typename T>
	Matrix4x4<T> Rotation4x4(const Quaternion<T>& _quaternion)
	{
		const Matrix3x3<T> rotation3x3 = Rotation3x3(_quaternion);
		return 
		{
			// m00			 m10					m20                m30
			rotation3x3[0], rotation3x3[1], rotation3x3[2], static_cast<T>(0),
			// m01			 m11					m21				   m31
			rotation3x3[3], rotation3x3[4] , rotation3x3[5], static_cast<T>(0),
			// m02			 m12					m22				   m32
			rotation3x3[6], rotation3x3[7] , rotation3x3[8], static_cast<T>(0),
			// m03			 m13					m23				   m33
			static_cast<T>(0), static_cast<T>(0) , static_cast<T>(0), static_cast<T>(1)
		};
	}

	template <typename T>
	Matrix4x4<T> Scale4x4(T _factorX, T _factorY, T _factorZ)
	{
		return
		{
			// m00			 m10					m20                m30
			_factorX, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
			// m01			 m11					m21				   m31
			static_cast<T>(0), _factorY , static_cast<T>(0), static_cast<T>(0),
			// m02			 m12					m22				   m32
			static_cast<T>(0), static_cast<T>(0) ,_factorZ, static_cast<T>(0),
			// m03			 m13					m23				   m33
			static_cast<T>(0), static_cast<T>(0) , static_cast<T>(0), static_cast<T>(1)
		};
	}
	template<typename T>
	Matrix4x4<T> Trs4x4(const Tbx::Vector3<T>& _translation, const Tbx::Vector3<T>& _eulerAngles, const Tbx::Vector3<T>& _scale)
	{
		const Matrix3x3<T> rotScaleMatrix = Rotation3x3(_eulerAngles) * Scale3x3(_scale);

		return
		{
			// m00			 m10					m20                m30
			rotScaleMatrix[0], rotScaleMatrix[1], rotScaleMatrix[2], static_cast<T>(0),
			// m01			 m11					m21				   m31
			rotScaleMatrix[3], rotScaleMatrix[4] , rotScaleMatrix[5], static_cast<T>(0),
			// m02			 m12					m22				   m32
			rotScaleMatrix[6], rotScaleMatrix[7] , rotScaleMatrix[8], static_cast<T>(0),
			// m03			 m13					m23				   m33
			_translation[0], _translation[1] , _translation[2], static_cast<T>(1)
		};
	}
	template<typename T>
	Matrix4x4<T> Trs4x4(const Tbx::Vector3<T>& _translation, const Quaternion<T>& _rotation, const Tbx::Vector3<T>& _scale)
	{
		const Matrix3x3<T> rotScaleMatrix = Rotation3x3(_rotation) * Scale3x3(_scale);

		return
		{
			// m00			 m10					m20                m30
			rotScaleMatrix[0], rotScaleMatrix[1], rotScaleMatrix[2], static_cast<T>(0),
			// m01			 m11					m21				   m31
			rotScaleMatrix[3], rotScaleMatrix[4] , rotScaleMatrix[5], static_cast<T>(0),
			// m02			 m12					m22				   m32
			rotScaleMatrix[6], rotScaleMatrix[7] , rotScaleMatrix[8], static_cast<T>(0),
			// m03			 m13					m23				   m33
			_translation[0], _translation[1] , _translation[2], static_cast<T>(1)
		};
	}

	template<typename T>
	Matrix4x4<T> LookAtRH(const Vector3<T>& _eye, const Vector3<T>& _center, const Vector3<T>& _up)
	{
		Vector3<T> f = (_center - _eye).Normalize();
		Vector3<T> s = Vector3<T>::Cross(f, _up).Normalize();
		Vector3<T> u = Vector3<T>::Cross(s, f);

		Matrix4x4<T> result = Matrix4x4<T>::Identity();
		result[0] = s.x;
		result[4] = s.y;
		result[8] = s.z;
		result[1] = u.x;
		result[5] = u.y;
		result[9] = u.z;
		result[2] = -f.x;
		result[5] = -f.y;
		result[10] = -f.z;

		// Apply translation to the matrix (dot products for camera position)
		result[12] = -Vector3<T>::Dot(s, _eye);
		result[13] = -Vector3<T>::Dot(u, _eye);
		result[14] = Vector3<T>::Dot(f, _eye);

		return result;
	}

	template<typename T>
	Matrix4x4<T> PerspectiveMatrix(const T fov, const T aspect, const T Near, const T Far)
	{
		const T fFovRad = static_cast<T>(1) / std::tanf(fov / static_cast<T>(2.f));
		const T zdiff = Near - Far;

		const T r00 = fFovRad / aspect;
		const T r11 = fFovRad;

		const T r22 = (Far + Near) / zdiff;
		const T r32 = (static_cast<T>(2) * Far * Near) / zdiff;

		return
			Matrix4x4<T>
			(
				r00, 0.f, 0.f, 0.f,
				0.f, r11, 0.f, 0.f,
				0.f, 0.f, r22, static_cast<T>(-1.0),
				0, 0, r32, 0.f
			);
	
	}
	template<typename T>
	Matrix4x4<T> PerspectiveMatrixFlipYAxis(const T fov, const T aspect, const T Near, const T Far)
	{
		const T fFovRad = static_cast<T>(1) / std::tanf(fov / static_cast<T>(2.f));
		const T zdiff = Near - Far;

		const T r00 = fFovRad / aspect;
		const T r11 = fFovRad;

		const T r22 = (Far + Near) / zdiff;
		const T r32 = (static_cast<T>(2) * Far * Near) / zdiff;

		return Matrix4x4<T>
			(
			r00, 0.f, 0.f, 0.f,
			0.f, -r11, 0.f, 0.f,
			0.f, 0.f, r22, static_cast<T>(-1.0),
			0, 0, r32, 0.f
			);
	}
	template<class T>
	constexpr Matrix4x4<T> OrthoGraphicMatrix(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		T topBottomDiff = top - bottom;
		T rightLeftDiff = right - left;
		T farMinusNear = zFar - zNear;

		T r00 = static_cast<T>(2) / rightLeftDiff;
		T r11 = static_cast<T>(2) / topBottomDiff;
		T r22 = -static_cast<T>(2) / farMinusNear;

		T r03 = -(right + left) / rightLeftDiff;
		T r13 = -(top + bottom) / topBottomDiff;
		T r23 = -(zFar + zNear) / farMinusNear;

		return Matrix4x4<T>
			(
				r00, 0.f, 0.f, 0.f,
				0.f, r11, 0.f, 0.f,
				0.f, 0.f, r22, 0.f,
				r03, r13, r23, 1.f
			);
		
	}

	template<typename T>
	Vector2<T> operator*(const Matrix2x2<T>& RESTRICT _m, const Vector2<T>& RESTRICT _vec)
	{
		const T x = _m[0] * _vec.x + _m[2] * _vec.y;
		const T y = _m[1] * _vec.x + _m[3] * _vec.y;

		return 	Vector2<T>(x, y);
	}

	template<typename T>
	Vector3<T> operator*(const Matrix3x3<T>& RESTRICT _m, const Vector3<T>& RESTRICT _vec)
	{
		const T x = _m[0] * _vec.x + _m[3] * _vec.y + _m[6] * _vec.z;
		const T y = _m[1] * _vec.x + _m[4] * _vec.y + _m[7] * _vec.z;
		const T z = _m[2] * _vec.x + _m[5] * _vec.y + _m[8] * _vec.z;

		return Vector3<T>(x, y, z);
	}

	template<typename T>
	Vector4<T> operator*(const Matrix4x4<T>& RESTRICT _m, const Vector4<T>& RESTRICT _vec)
	{
		const T x = _m[0] * _vec.x + _m[4] * _vec.y + _m[8] * _vec.z + _m[12] * _vec.w;
		const T y = _m[1] * _vec.x + _m[5] * _vec.y + _m[9] * _vec.z + _m[13] * _vec.w;
		const T z = _m[2] * _vec.x + _m[6] * _vec.y + _m[10] * _vec.z + _m[14] * _vec.w;
		const T w = _m[3] * _vec.x + _m[7] * _vec.y + _m[11] * _vec.z + _m[15] * _vec.w;

		return Vector4<T>(x, y, z, w);
	}
	
	
	
}