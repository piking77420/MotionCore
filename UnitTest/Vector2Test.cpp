#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;

TEST(TestVec2, OperatorAdd)
{
	// operator+
	{
		Vector2i vec1i = Vector2i( -2, 10 );
		Vector2i vec2i = Vector2i( 2, -10 );
		EXPECT_EQ(vec1i + vec2i, Vector2i::Zero());


		Vector2f vec1f = Vector2f( -2.f, 10.f );
		Vector2f vec2f = Vector2f( 2.f, -10.f );
		EXPECT_EQ(vec1f + vec2f, Vector2f::Zero());

		Vector2d vec1d = Vector2d( -2, 10 );
		Vector2d vec2d = Vector2d( 2, -10 );
		EXPECT_EQ(vec1d + vec2d, Vector2d::Zero());
	}


	// operator +=
	{
		Vector2i vec1i = Vector2i(- 2, 10 );
		vec1i += Vector2i( 2, -10 );
		EXPECT_EQ(vec1i, Vector2i::Zero());

		Vector2f vec1f = { -2.f, 10.f };
		vec1f += { 2.f, -10.f };
		EXPECT_EQ(vec1f, Vector2f::Zero());

		Vector2d vec1d = { -2, 10 };
		vec1d += { 2, -10 };
		EXPECT_EQ(vec1d, Vector2d::Zero());

	}



}
TEST(TestVec2, OperatorSub)
{

	{
		Vector2i vec1i = { 2, 10 };
		Vector2i vec2i = { 2, 10 };
		EXPECT_EQ(vec1i - vec2i, Vector2i::Zero());

		Vector2f vec1f = { 2.f, 10.f };
		Vector2f vec2f = { 2.f, 10.f };
		EXPECT_EQ(vec1f - vec2f, Vector2f::Zero());

		Vector2d vec1d = { 2, 10 };
		Vector2d vec2d = { 2, 10 };
		EXPECT_EQ(vec1d - vec2d, Vector2d::Zero());
	}

	{
		// operator -=
		Vector2i vec1i = { 2, 10 };
		vec1i -= vec1i;
		EXPECT_EQ(vec1i, Vector2i::Zero());

		Vector2f vec1f = { 2.f, 10.f };
		vec1f -= vec1f;
		EXPECT_EQ(vec1f, Vector2f::Zero());

		Vector2d vec1d = { 2, 10 };
		vec1d -= vec1d;
		EXPECT_EQ(vec1d, Vector2d::Zero());
	}

}

TEST(TestVec2, OperatorMul)
{

	{

		Vector2i vec1i = { 2, 10 };
		vec1i = vec1i * 2;
		EXPECT_EQ(vec1i, Vector2i(4, 20));

		Vector2f vec1f = { 2.f, 10.f };
		vec1f = vec1f * 2.f;
		EXPECT_EQ(vec1f, Vector2f(4.f, 20.f));

		Vector2d vec1d = { 2, 10 };
		vec1d = vec1d * (double)2;
		EXPECT_EQ(vec1d, Vector2d(4, 20));
	}
	{
		Vector2i vec1i = { 2, 10 };
		vec1i *= 2;
		EXPECT_EQ(vec1i, Vector2i(4, 20));

		Vector2f vec1f = { 2.f, 10.f };
		vec1f *= 2.f;
		EXPECT_EQ(vec1f, Vector2f(4.f, 20.f));

		Vector2d vec1d = { 2, 10 };
		vec1d *= 2;
		EXPECT_EQ(vec1d, Vector2d(4, 20));
	}
}

TEST(TestVec2, OperatorDiv)
{

	{
		Vector2i vec1i = { 2, 10 };
		vec1i = vec1i / 2;
		EXPECT_EQ(vec1i, Vector2i(1, 5));

		Vector2f vec1f = { 2.f, 10.f };
		vec1f = vec1f / 2.f;
		EXPECT_EQ(vec1f, Vector2f(1.f, 5.f));

		Vector2d vec1d = { 2, 10 };
		vec1d = vec1d / 2;
		EXPECT_EQ(vec1d, Vector2d(1, 5));
	}

	{
		Vector2i vec1i = { 2, 10 };
		vec1i /= 2;
		EXPECT_EQ(vec1i, Vector2i(1, 5));

		Vector2f vec1f = { 2.f, 10.f };
		vec1f /= 2.f;
		EXPECT_EQ(vec1f, Vector2f(1.f, 5.f));

		Vector2d vec1d = { 2, 10 };
		vec1d /= 2;
		EXPECT_EQ(vec1d, Vector2d(1, 5));
	}
}

TEST(TestVec2, OperatorEquals)
{
	{	// float
		Vector2f vec1 = { 1.f, 1.f };
		Vector2f vec2 = { 1.f, 1.f };
		EXPECT_TRUE(vec1 == vec2);
	}

	{
		// double
		Vector2d vec1 = { 1, 1 };
		Vector2d vec2 = { 1, 1 };
		EXPECT_TRUE(vec1 == vec2);
	}
}



TEST(TestVec2, MagnitudeSquare)
{
	{	// float
		Vector2f vec1 = { 5.f, 5.f };
		EXPECT_EQ(vec1.MagnitudeSquare(), 50.f);
	}

	{	// double
		Vector2d vec1 = { 5., 5. };
		EXPECT_EQ(vec1.MagnitudeSquare(), 50.);
	}
}

TEST(TestVec2, Magnitude)
{
	{	// float
		Vector2f vec1 = { 10.f, 10.f };
		EXPECT_EQ(vec1.Magnitude(), 14.1421356f);
	}

	{	// double
		Vector2d vec1 = { 10., 10. };
		EXPECT_EQ(vec1.Magnitude(), 14.142135623730951);
	}
}

TEST(TestVec2, Normalize)
{
	{	// float
		Vector2f vec1 = { 10.f, 10.f };
		EXPECT_NEAR(vec1.Normalize().Magnitude(), 1., EPSILON);
	}

	{	// double
		Vector2d vec1 = { 10., 10. };
		double value = vec1.Normalize().Magnitude();
		EXPECT_NEAR(vec1.Normalize().Magnitude(), 1., EPSILON);
	}
}


TEST(TestVec2, DistanceSqr)
{
	{	// float
		Vector2f vec1 = { 1.f, 0.f };
		Vector2f vec2 = { 0.f, 1.f };

		EXPECT_NEAR(Vector2f::DistanceSquare(vec1, vec2), 2.f, EPSILON);
	}

	{
		// double
		Vector2d vec1 = { 1., 0. };
		Vector2d vec2 = { 0., 1. };

		EXPECT_NEAR(Vector2d::DistanceSquare(vec1, vec2), 2., EPSILON);
	}
}


TEST(TestVec2, Distance)
{
	{	// float
		Vector2f vec1 = { 1.f, 0.f };
		Vector2f vec2 = { 0.f, 1.f };

		EXPECT_NEAR(Vector2f::Distance(vec1, vec2), 1.414213f, EPSILON);
	}

	{
		// double
		Vector2d vec1 = { 1., 0. };
		Vector2d vec2 = { 0., 1. };

		EXPECT_NEAR(Vector2d::Distance(vec1, vec2), 1.414213, EPSILON);
	}
}

TEST(TestVec2, Cross)
{
	{	// float
		Vector2f vec1 = { 1.f, 0.f };
		Vector2f vec2 = { 0.f, 1.f };
		EXPECT_NEAR(Vector2f::Cross(vec1, vec2), 1.f, EPSILON);
	}

	{
		// double
		Vector2d vec1 = { 1., 0. };
		Vector2d vec2 = { 0., 1. };
		EXPECT_NEAR(Vector2d::Cross(vec1, vec2), 1., EPSILON);
	}
}

