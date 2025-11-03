#pragma once
#include "Math/ToolBoxTypeDef.hpp"

namespace MotionCore
{
	template <typename T>
	struct Triangle
	{
		Tbx::Vector3<T> points[3];
	};

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> GetNormal(const Triangle<T>& _triangle)
	{
		return Tbx::Vector3<T>::Cross(_triangle[1] - _triangle[0], _triangle[2] - _triangle[0])
	}

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> GetNormalNormalize(const Triangle<T>& triangle)
	{
		return GetNormal(_triangle).Normalize()
	}

	template <typename T>
	FORCEINLINE Tbx::Vector3<T> GetArea(const Triangle<T>& _triangle)
	{
		return GetNormal(_triangle) * static_cast<T>(0.5);
	}

	// TO DO BARYCENTER

}


