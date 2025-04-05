
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
}