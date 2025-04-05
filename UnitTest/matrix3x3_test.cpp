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
	const Matrix3x3<float> m1(1.f, 2.f, 3.f, 
		4.f, 5.f, 6.f, 
		7.f, 8.f, 9.f);
	const Matrix3x3<float> m1T(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);

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
	float angleR = 1.f;
	float cosa = 0.54030230586f;
	float sina = 0.8414709848f;

	const Matrix3x3<float> m = Rotation3x3X(angleR);
	const Matrix3x3<float> m2(1.f, 0.f, 0.f, 0.f, cosa, sina, 0.f, -sina, cosa);
	EXPECT_TRUE(m == m2);


}

TEST(Matrix3X3, RotationY)
{
	float angleR = 1.f;
	float cosa = 0.54030230586f;
	float sina = 0.8414709848;

	const Matrix3x3<float> m = Rotation3x3Y(angleR);
	const Matrix3x3<float> m2(cosa, 0.f, -sina, 0.f, 1.f, 0.f, sina, 0.f, cosa);
	EXPECT_TRUE(m == m2);
}

TEST(Matrix3X3, RotationZ)
{
	float angleR = 1.f;
	float cosa = 0.54030230586f;
	float sina = 0.8414709848f;

	const Matrix3x3<float> m = Rotation3x3Z(angleR);
	const Matrix3x3<float> m2(cosa, sina, 0.f, -sina, cosa, 0.f, 0.f, 0.f, 1.f);
	EXPECT_TRUE(m == m2);
}

TEST(Matrix3X3, RotationXYZ)
{
	const Tbx::Vector3f eulerAngle = Tbx::Vector3f(Vector3<float>(45, 45, 45) * fDeg2Rad).Normalize();

	const Matrix3x3<float> m = Rotation3x3(eulerAngle);
	const Matrix3x3<float> rotResult = Matrix3x3<float>(0.702096164f, 0.706954062f, -0.0853042603,
		-0.457336962f, 0.539498627f, 0.706954062f,
		0.545805633f, -0.457336962f, 0.702096164f);

	EXPECT_TRUE(m == rotResult);

}

TEST(Matrix3X3, RotationQuaternion)
{
	const Quaternionf& q = Quaternionf(0.844623208f, 0.191341713f, 0.461939812f, 0.191341713f).Normalize();
	const Matrix3x3<float> m = Rotation3x3(q);
	
	const Matrix3x3<float> result(0.5000000f, 0.5000000f, -0.707106888f,
		-0.146446586f, 0.853553414f, 0.500000000f,
		0.853553474f, -0.146446586f, 0.499999970f);

	EXPECT_TRUE(m == result);

}

TEST(Matrix3X3, Scale)
{
	const Matrix3x3<float> m = Scale3x3(1.f, 2.f, 3.f);

	const Matrix3x3<float> m2(1.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 3.f);

	EXPECT_TRUE(m == m2);

}

TEST(Matrix3X3, Invert)
{
	const Matrix3x3<float> m1(
		2.0f, 5.0f, 7.0f,
		6.0f, 3.0f, 4.0f,
		5.0f, -2.0f, -3.0f
	);

	float determinant = m1.Determinant();

	EXPECT_TRUE(IsEqual(m1.Determinant(), -1.f));

	const Matrix3x3<float> m1Inv = m1.Invert();
	const Matrix3x3<float> m1Invr = Matrix3x3<float>(1, -1, 1,
													-38.f, 41.f, -34.f
													 ,27.f, -29.f, 24.f);

	EXPECT_TRUE(m1Inv == m1Invr);
}
