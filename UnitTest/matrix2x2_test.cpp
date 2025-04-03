#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;

TEST(Matrix2X2, Identity)
{
	Matrix2x2<float> identity = Matrix2x2f::Identity();
	EXPECT_TRUE(IsEqual(identity[0], 1.f) && IsEqual(identity[1], 0.f) && IsEqual(identity[2], 0.f) && IsEqual(identity[3], 1.f));

}

TEST(Matrix2X2, Constructor)
{
	
	{
		float x1 = 0.f;
		float y1 = 1.f;
		float x2 = 2.f;
		float y2 = 3.f;

		Matrix2x2<float> m = Matrix2x2f(x1, y1, x2, y2);

		EXPECT_TRUE(IsEqual(m[0], x1) && IsEqual(m[1], y1) && IsEqual(m[2], x2) && IsEqual(m[3], y2));

	}

	{
		float x1 = 50.f;
		Matrix2x2<float> m = Matrix2x2f(x1);

		EXPECT_TRUE(IsEqual(m[0], x1) && IsEqual(m[1], x1) && IsEqual(m[2], x1) && IsEqual(m[3], x1));
	}


}

TEST(Matrix2X2, Transpose)
{
	{
		float x1 = 0.f;
		float y1 = 1.f;
		float x2 = 2.f;
		float y2 = 3.f;

		Matrix2x2<float> m = Matrix2x2f(x1, y1, x2, y2).Transpose();

		EXPECT_TRUE(IsEqual(m[0], x1) && IsEqual(m[1], x2) && IsEqual(m[2], y1) && IsEqual(m[3], y2));

	}

}


TEST(Matrix2X2, Multiply)
{
	{
		float x1 = 23.f;
		float y1 = 53.f;

		float x2 = 22.f;
		float y2 = -42.f;

		Matrix2x2<float> m = Matrix2x2f(23.f, 53.f, 22.f, -42.f);
		Matrix2x2<float> m2 = Matrix2x2f(43.F, 2.f, 32.f, 23.f);

		Matrix2x2<float> result = m * m2;
		Matrix2x2<float> result2 = m2 * m;

		EXPECT_FALSE(result == result2);
		EXPECT_TRUE(result != result2);


		EXPECT_TRUE(IsEqual(result[0], 1033.f) && IsEqual(result[1], 2195.f) && IsEqual(result[2], 1242.f) && IsEqual(result[3], 730.f));
		EXPECT_TRUE(IsEqual(result2[0], 2685.f) && IsEqual(result2[1], 1265.f) && IsEqual(result2[2], -398.f) && IsEqual(result2[3], -922.f));

	}

}

TEST(Matrix2X2, Determinant)
{
	Matrix2x2<float> m = Matrix2x2f(23.f, 53.f, 22.f, -42.f);
	float v = m.Determinant();

	EXPECT_TRUE(IsEqual(v, -2132.f));
}

TEST(Matrix2X2, Trace)
{
	Matrix2x2<float> id = Matrix2x2<float>::Identity();

	float trace[2];
	id.Trace(trace);

	EXPECT_TRUE(IsEqual(trace[0], 1.f) && IsEqual(trace[1], 1.f));
}

TEST(Matrix2X2, Rotation)
{
	float angle = 1.F;
	Matrix2x2f m = Rotation2x2(angle);
	Matrix2x2f expected = Matrix2x2f(0.54030230586f, -0.8414709848f, 0.8414709848f, 0.54030230586f);
	EXPECT_TRUE(m == expected);
}


TEST(Matrix2X2, Scale)
{
	float scale = 10.F;
	Matrix2x2f m = Scale2x2(scale);
	Matrix2x2f expected = Matrix2x2f(scale, 0.f, 0.f, scale);
	EXPECT_TRUE(m == expected);
}