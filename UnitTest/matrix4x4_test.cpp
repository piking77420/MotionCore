#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

#include <print>

using namespace Tbx;

TEST(Matrix4X4, Identity)
{
	const Matrix4x4<float> m = Matrix4x4<float>::Identity();
	const Matrix4x4<float> result(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	EXPECT_TRUE(m == result);
}

TEST(Matrix4X4, Constructor)
{
	const Matrix4x4<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f,
		16.f);

	EXPECT_TRUE(IsEqual(m1[0], 1.f) && IsEqual(m1[1], 2.f) && IsEqual(m1[2], 3.f) && IsEqual(m1[3], 4.f) 
		&& IsEqual(m1[4], 5.f) && IsEqual(m1[5], 6.f) && IsEqual(m1[6], 7.f) && IsEqual(m1[7], 8.f) 
		&& IsEqual(m1[8], 9.f) && IsEqual(m1[9], 10.f) && IsEqual(m1[10], 11.f) && IsEqual(m1[11], 12.f)
		&& IsEqual(m1[12], 13.f) && IsEqual(m1[13], 14.f) && IsEqual(m1[14], 15.f) && IsEqual(m1[15], 16.f));
}

TEST(Matrix4X4, Transpose)
{
	const Matrix4x4<float> m1 = Matrix4x4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f,
		16.f).Transpose();

	EXPECT_TRUE(IsEqual(m1[0], 1.f) && IsEqual(m1[1], 5.f) && IsEqual(m1[2], 9.f) && IsEqual(m1[3], 13.f)
		&& IsEqual(m1[4], 2.f) && IsEqual(m1[5], 6.f) && IsEqual(m1[6], 10.f) && IsEqual(m1[7], 14.f)
		&& IsEqual(m1[8], 3.f) && IsEqual(m1[9], 7.f) && IsEqual(m1[10], 11.f) && IsEqual(m1[11], 15.f)
		&& IsEqual(m1[12], 4.f) && IsEqual(m1[13], 8.f) && IsEqual(m1[14], 12.f) && IsEqual(m1[15], 16.f));

}


TEST(Matrix4X4, Multiply)
{
	const Matrix4x4<float> m1 = Matrix4x4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f,
		16.f);
	const Matrix4x4<float> m1T = m1.Transpose();

	const Matrix4x4<float> m1m1T = m1 * m1T;
	const Matrix4x4<float> m1Tm1= m1T * m1;

	EXPECT_TRUE(m1m1T != m1Tm1);

	const Matrix4x4<float> m1m1Tr = Matrix4x4<float>(30.f, 70.f, 110.f, 150.f,
		70.f, 174.f, 278.f, 382.f,
		110.f, 278.f, 446.f, 614.f,
		150.f, 382.f, 614.f, 846.f);
	EXPECT_TRUE(m1m1T != m1m1Tr);

	const Matrix4x4<float> m1Tm1r = Matrix4x4<float>(276.f, 304.f, 332.f, 360.f,
		304.f, 336.f, 368.f, 400.f,
		332.f, 368.f, 404.f, 440.f,
		360.f, 400.f, 440.f, 480.f);

	EXPECT_TRUE(m1Tm1 != m1Tm1r);

}

TEST(Matrix4X4, Determinant)
{
	const Matrix4x4<float> m1(
		3.2f, 7.8f, 1.5f, 9.6f,
		4.3f, 8.1f, 2.7f, 6.5f,
		5.9f, 0.4f, 3.3f, 7.2f,
		1.8f, 9.0f, 4.6f, 2.1f
	);

	const float value = m1.Determinant();

	EXPECT_TRUE(  IsEqual(value, 631.821533f));
}

TEST(Matrix4X4, Trace)
{
	float trace[4];
	const Matrix4x4<float> m1 = Matrix4x4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f,
		16.f);

	m1.Trace(trace);

	EXPECT_TRUE(IsEqual(trace[0], 1.f) && IsEqual(trace[1], 6.f) && IsEqual(trace[2], 11.f) && IsEqual(trace[3], 16.f));
}

TEST(Matrix4X4, RotationXYZ)
{
	const Tbx::Vector3f eulerAngle = Tbx::Vector3f( 1.f, 2.f, 3.f );
	const Matrix4x4<float> rot = Rotation4x4(eulerAngle.x, eulerAngle.y, eulerAngle.z);

	const Matrix4x4<float> rotResult = Matrix4x4<float>(0.411982268f, -0.681242704f, 0.605127215f, 0.f,
		0.0587266423f, -0.642872810f, -0.763718367f, 0.f,
		0.909297407f, 0.350175470f, -0.224845082f, 0.f, 
		0.f, 0.f, 0.f, 1.f);
	EXPECT_TRUE(rotResult == rot);
}

TEST(Matrix4X4, RotationQuaternion)
{
	const Quaternionf& q = Quaternionf(2.f, 3.f, 4.f, 1.f).Normalize();
	const Matrix4x4<float> rot = Rotation4x4(q);
	const Matrix4x4<float> rotResult = Matrix4x4<float>(-0.666667f, 0.666667f, 0.733333f, 0.f,
														0.666667f, -0.333333f, 0.533333f, 0.f,
														0.333333f, 0.666667f, 0.133333f, 0.f,
															0.f, 0.f, 0.f, 1.f);

	EXPECT_TRUE(rot == rotResult);
}


TEST(Matrix4X4, Scale)
{
	const Matrix4x4<float> scalem = Scale4x4(1.f, 2.f, 3.f);

	EXPECT_TRUE(IsEqual(scalem[0], 1.f) && IsEqual(scalem[5], 2.f) && IsEqual(scalem[10], 3.f));
}

TEST(Matrix4X4, TrsEuler)
{
	const Tbx::Vector3f translation = Tbx::Vector3f( 10.f, 9.f, 8.f );
	const Tbx::Vector3f eulerAngle = Tbx::Vector3f(1.f, 2.f, 3.f );
	const Tbx::Vector3f scale = Tbx::Vector3f(1.f, 2.f, 3.f);

	const Matrix4x4<float> trs = Trs4x4(translation, eulerAngle, scale);
	const Matrix4x4<float> trsResult = Matrix4x4<float>
		(0.411982268f, -0.681242704, 0.605127215, 0.f,
			0.117453285, -1.28574562, -1.52743673, 0.f,
			2.72789216, 1.05052638, -0.674535275, 0.f,
			10.0000000, 9.00000000, 8.00000000, 1.f);

	EXPECT_TRUE(trs == trsResult);
}

TEST(Matrix4X4, TrsQ)
{
	const Tbx::Vector3f translation = Tbx::Vector3f( 10.f, 9.f, 8.f );
	const Quaternionf q = Quaternionf(2.f, 3.f, 4.f, 1.f).Normalize();
	const Tbx::Vector3f scale = Tbx::Vector3f( 1.f, 2.f, 3.f );

	const Matrix4x4<float> trs = Trs4x4(translation, q, scale);
	const Matrix4x4<float> trsResult = Matrix4x4<float>
		(-0.666666627, 0.666666627, 0.733333290, 0.f,
			1.33333325, -0.666666567, 1.06666672, 0.f,
			0.999999940, 2.00000000, 0.399999887, 0.f,
			10.0000000, 9.00000000, 8.00000000, 1.f);


	EXPECT_TRUE(trs == trsResult);

}