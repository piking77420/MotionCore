#include "matrix2x2.hpp"

namespace Tbx
{
	// angle in radians
	template <typename T>
	static FORCEINLINE Matrix2x2<T> Rotation(T _angle);

	template <typename T>
	static FORCEINLINE Matrix2x2<T> Scale(T _factor);
}

#include "math/matrix2X2_transformation.inl"