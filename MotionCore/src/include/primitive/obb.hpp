
#include "math/toolbox_typedef.hpp"

namespace MotionCore
{
	template <typename T>
	struct Obb
	{
		// right up forward
		Tbx::Matrix3x3<T> orientation;
	};
}