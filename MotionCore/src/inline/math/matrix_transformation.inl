
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
		return {

			// m00			 m10			m20
			_factor, static_cast<T>(0), static_cast<T>(0),
			// m01			 m11			m21
			static_cast<T>(0), _factor , static_cast<T>(0),
			// m02			 m12			m22
			static_cast<T>(0), static_cast<T>(0) , _factor,
		};
	}

	template<typename T>
	Matrix3x3<T> Scale3x3(T _factorX, T _factorY, T _factorZ)
	{
		return {

			// m00			 m10			m20
			_factor, static_cast<T>(0), static_cast<T>(0),
			// m01			 m11			m21
			static_cast<T>(0), _factor , static_cast<T>(0), 
			// m02			 m12			m22
			static_cast<T>(0), static_cast<T>(0) , _factor,
		};
	}

	template <typename T>
	Matrix4x4<T> Rotation4x4(T _angleX, T _angleY, T _angleZ)
	{
		return {};
	}
}