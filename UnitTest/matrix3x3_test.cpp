#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;

TEST(Matrix3X3, Identity)
{
	const Matrix3x3<float> m1(Matrix3x3<float>::Identity());

	EXPECT_TRUE(IsEqual(m1[0], 1.f) && IsEqual(m1[1], 0.f) && IsEqual(m1[2], 0.f) &&
		IsEqual(m1[3], 0.f) && IsEqual(m1[4], 1.f) && IsEqual(m1[5], 0.f) &&
		IsEqual(m1[6], 0.f) && IsEqual(m1[7], 0.f) && IsEqual(m1[8], 1.f));
}

TEST(Matrix3X3, Constructor)
{
	
	const Matrix3x3<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

	EXPECT_TRUE(IsEqual(m1[0], 1.f) && IsEqual(m1[1], 2.f) && IsEqual(m1[2], 3.f) &&
		IsEqual(m1[3], 4.f) && IsEqual(m1[4], 5.f) && IsEqual(m1[5], 6.f) &&
		IsEqual(m1[6], 7.f) && IsEqual(m1[7], 8.f) && IsEqual(m1[8], 9.f));

}

TEST(Matrix3X3, Transpose)
{
	const Matrix3x3<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	const Matrix3x3<float> m1T(9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f);

	EXPECT_TRUE(m1.Transpose() == m1T);
}


TEST(Matrix3X3, Multiply)
{
	const Matrix3x3<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	const Matrix3x3<float> m2(10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f);

	const Matrix3x3<float> m1m2C = m1 * m2;
	const Matrix3x3<float> m2m1C = m2 * m1;

	const Matrix3x3<float> m1m2R(102.f,129.f,156.f, 66.f, 84.f,102.f,30.f, 39.f, 48.f);
 	EXPECT_TRUE(m1m2C == m1m2R);

	const Matrix3x3<float> m2m1R(36.f, 30.f, 24.f, 99.f, 84.f, 69.f, 162.f, 138.f, 114.f);
	EXPECT_TRUE(m2m1C == m2m1R);


}

TEST(Matrix3X3, Determinant)
{
	Matrix3x3<float> d(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f);
	float df = d.Determinant();

	EXPECT_TRUE(IsEqual(df, 0.f));

}

TEST(Matrix3X3, Trace)
{
	const Matrix3x3<float> d = Matrix3x3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	float trace[3];
	d.Trace(trace);

	EXPECT_TRUE(IsEqual(trace[0], 1.f) && IsEqual(trace[1], 5.f) && IsEqual(trace[2], 9.f));
}

TEST(Matrix3X3, RotationX)
{
	
}

TEST(Matrix3X3, RotationY)
{

}

TEST(Matrix3X3, RotationZ)
{

}

TEST(Matrix3X3, RotationXYZ)
{

}

TEST(Matrix3X3, RotationQuaternion)
{

}

TEST(Matrix3X3, Scale)
{
}