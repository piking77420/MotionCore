
namespace Tbx
{
	template <typename T>
	Matrix2x2<T> Rotation(T _angle)
	{
		return {

			// m00			 m01
			std::cos(_angle), -std::sin(_angle),
			// m10			 m11
			std::sin(_angle), std::cos(_angle)
		};
	}

	template<typename T>
	Matrix2x2<T> Tbx::Scale(T _factor)
	{
		return {

			// m00			 m01
			_factor, static_cast<T>(0),
			// m10			 m11
			static_cast<T>(0), _factor
		};
	}
}