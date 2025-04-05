
#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;

static_assert(offsetof(Quaternion<float>, real) == 0, "invalid Offset");
static_assert(offsetof(Quaternion<float>, imaginary) == sizeof(float) && offsetof(Quaternion<float>, imaginary.x) == sizeof(float), "invalid Offset");
static_assert(offsetof(Quaternion<float>, imaginary.y) == sizeof(float) * 2, "invalid Offset");
static_assert(offsetof(Quaternion<float>, imaginary.z) == sizeof(float) * 3 , "invalid Offset");

TEST(Quaternion, Constructor)
{
	Quaternion<float> quaternion = Quaternion<float>(4.f, 1.f, 2.f, 3.f);

	EXPECT_TRUE(IsEqual(quaternion.imaginary.x, 1.f) && IsEqual(quaternion.imaginary.y, 2.f)
	&& IsEqual(quaternion.imaginary.z, 3.f) && IsEqual(quaternion.real, 4.f));

	quaternion = Quaternion<float>(4.f, Vector3f(1.f, 2.f, 3.f));

	EXPECT_TRUE(IsEqual(quaternion.imaginary.x, 1.f) && IsEqual(quaternion.imaginary.y, 2.f)
		&& IsEqual(quaternion.imaginary.z, 3.f) && IsEqual(quaternion.real, 4.f));

}

TEST(Quaternion, Identity)
{
	constexpr Quaternion<float> identity = Quaternion<float>::Identity();

	EXPECT_TRUE(IsEqual(identity.real, 1.f) && IsEqual(identity.imaginary.x, 0.f) && IsEqual(identity.imaginary.x, 0.f) && IsEqual(identity.imaginary.x, 0.f));
}

TEST(Quaternion, Conjugate)
{

	const Quaternion<float> quaternion = Quaternion<float>(4.f, 1.f, 2.f, 3.f);
	const Quaternion<float> quaternionR = Quaternion<float>(4.f ,-1.f, -2.f, -3.f);

	EXPECT_TRUE(quaternion.Conjugate() == quaternionR);
}

TEST(Quaternion, Magnitude)
{
	Quaternion<float> q(0.0f, 0.70710678f, 0.0f, 0.70710678f);

	EXPECT_TRUE(IsEqual(q.Magnitude(), 1.f));
}

TEST(Quaternion, Normalize)
{
	const Quaternion<float> q = Quaternion<float>(1.f, 2.f, 3.f, 4.f).Normalize();

	EXPECT_TRUE(IsEqual(q.Magnitude(), 1.f));
}

TEST(Quaternion, Dot)
{
	const Quaternion<float> q = Quaternion<float>(1.f, 2.f, 3.f, 4.f);
	const Quaternion<float> q2 = Quaternion<float>(4.f, 5.f, 6.f, 4.f);

	float result = Quaternion<float>::Dot(q, q2);

	EXPECT_TRUE(IsEqual(result, 48.f));
}

TEST(Quaternion, Inv)
{
	const Quaternion<float> q = Quaternion<float>(4.f, 1.f, 2.f, 3.f).Inverse();
	Quaternion<float> qInv(0.133333333f, -0.033333333f, -0.066666667f, -0.1f);

	EXPECT_NEAR(q.real, qInv.real, IsEqualValue<float>());
	EXPECT_NEAR(q.imaginary.x, qInv.imaginary.x, IsEqualValue<float>());
	EXPECT_NEAR(q.imaginary.y, qInv.imaginary.y, IsEqualValue<float>());
	EXPECT_NEAR(q.imaginary.z, qInv.imaginary.z, IsEqualValue<float>());

}

TEST(Quaternion, ToEulerAngle)
{
	Vector3<float> eulerAngles = Quaternion<float>::ToEulerAngles(Quaternion<float>(0.730296731, 0.182574183, 0.365148365, 0.547722578));

	const Vector3<float> expectedEulerAngles(-0.1973956f, 0.823212f, 1.3734008f);


	EXPECT_NEAR(expectedEulerAngles.x, eulerAngles.x, IsEqualValue<float>());
	EXPECT_NEAR(expectedEulerAngles.y, eulerAngles.y, IsEqualValue<float>());
	EXPECT_NEAR(expectedEulerAngles.z, eulerAngles.z, IsEqualValue<float>());

	// TO DO VERIFY WITH GRAPHICS
}

TEST(Quaternion, FromEuler)
{
	const Vector3<float> euler(-0.1973956f, 0.823212f, 1.3734008f);
	const Quaternion<float> qeuler = Quaternion<float>::FromEuler(euler);

	EXPECT_NEAR(qeuler.real, 0.680309057f, IsEqualValue<float>());
	EXPECT_NEAR(qeuler.imaginary.x, -0.322251707f, IsEqualValue<float>());
	EXPECT_NEAR(qeuler.imaginary.y, 0.250640213f, IsEqualValue<float>());
	EXPECT_NEAR(qeuler.imaginary.z, 0.608697653f, IsEqualValue<float>());
	
}

TEST(Quaternion, LookAt)
{
	Vector3<float> forward = Vector3<float>(0.2f, 0.2f, 0).Normalize();

	Quaternion<float> q1 = Quaternion<float>::LookRotation(Vector3<float>::UnitZ(), Vector3<float>::UnitY());

	EXPECT_TRUE(q1 == Quaternion<float>::Identity());

	Vector3<float> forward2 = Vector3<float>(0.2f, 0.2f, 0);
	Quaternion<float> q2 = Quaternion<float>::LookRotation(forward2.Normalize(), Vector3<float>(0.5f, 0.f, 0.5f).Normalize());

	EXPECT_NEAR(q2.real, 0.0600030012, IsEqualValue<float>());
	EXPECT_NEAR(q2.imaginary.x, 0.455767989f, IsEqualValue<float>());
	EXPECT_NEAR(q2.imaginary.y, 0.540625036f, IsEqualValue<float>());
	EXPECT_NEAR(q2.imaginary.z, 0.704556346f, IsEqualValue<float>());

}

TEST(Quaternion, Slerp)
{
	Quaternion<float> q1(1, 0, 0, 0);  // Identity rotation (no rotation)
	Quaternion<float> q2(0, 1, 0, 0);  // 180 degrees rotation around X axis

	float t = 0.5f;
	Quaternion<float> slerp = Quaternion<float>::Slerp(q1, q2, t);

	Quaternion<float> rslerp(0.7071f, 0.7071f, 0.0f, 0.0f); // Halfway between q1 and q2

	EXPECT_TRUE(slerp == rslerp);

}

TEST(Quaternion, NLerp)
{
	Quaternion<float> q1(1, 0, 0, 0);  
	Quaternion<float> q2(0, 1, 0, 0);  

	float t = 0.5f;

	Quaternion<float> nlerp = Quaternion<float>::Nlerp(q1, q2, t);

	Quaternion<float> expectedNlerp(0.7071f, 0.7071f, 0.0f, 0.0f);  // Halfway between q1 and q2

	EXPECT_TRUE(nlerp == expectedNlerp);
}

TEST(Quaternion, FromMatrix)
{
	Quaternion<float> q1 = Quaternion<float>::FromEuler(Vector3<float>(45, 45, 45) * fDeg2Rad).Normalize();
	Quaternion<float> qfm = Quaternion<float>::FromMatrix(Rotation3x3(q1));

	EXPECT_TRUE(q1 == qfm);

}



// opeator
