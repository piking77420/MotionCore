
#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;


TEST(TestVec4, Constructor)
{
	Vector4<double> v = Vector4<double>(1., 2., 3., 4.);


	EXPECT_TRUE(IsEqual(v.x, 1.));
	EXPECT_TRUE(IsEqual(v.y, 2.));
	EXPECT_TRUE(IsEqual(v.z, 3.));
	EXPECT_TRUE(IsEqual(v.w, 4.));
}

TEST(TestVec4, Magnitude)
{
	Vector4<double> v = Vector4<double>(1., 2., 3., 4.);

	double magSquare = v.MagnitudeSquare();

	EXPECT_FLOAT_EQ(magSquare, 30.);

	double mag = v.Magnitude();

	EXPECT_FLOAT_EQ(mag ,std::sqrt(magSquare));
}

TEST(TestVec4, Normalize)
{
	Vector4<double> v = Vector4<double>(1., 0., 0., 0.);

	EXPECT_TRUE(IsEqual(v.Magnitude(), 1.));

}


TEST(TestVec4, Distance)
{
	{
		Vector4<double> v = Vector4<double>(1., 0., 0., 0.);

		Vector4<double> v1 = Vector4<double>(0., 1., 0., 0.);

		double distance = Vector4<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.);
		EXPECT_FLOAT_EQ(Vector4<double>::Distance(v, v1), std::sqrt(2.));

	}

	{
		Vector4<double> v = Vector4<double>(1., 0., 0., 0.);

		Vector4<double> v1 = Vector4<double>(0., 1., 0., 0.);

		double distance = Vector4<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.);
		EXPECT_FLOAT_EQ(Vector4<double>::Distance(v, v1), std::sqrt(2.));
	}

}



TEST(TestVec4, Dot)
{
	double v = Vector4<double>::Dot(Vector4<double>::UnitX(), Vector4<double>::UnitY());
	EXPECT_TRUE(IsEqual(v, 0.));

	v = Vector4<double>::Dot(Vector4<double>::UnitX(), Vector4<double>::UnitZ());
	EXPECT_TRUE(IsEqual(v, 0.));

	v = Vector4<double>::Dot(Vector4<double>::UnitX(), Vector4<double>::UnitW());
	EXPECT_TRUE(IsEqual(v, 0.));

	v = Vector4<double>::Dot(Vector4<double>::UnitX(), Vector4<double>::UnitX());
	EXPECT_TRUE(IsEqual(v, 1.));

}


// operator
TEST(TestVec4, operatorAdd)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		Vector4<double> v2 = Vector4<double>::UnitY();

		Vector4<double> expectResult = Vector4<double>(1., 1., 0., 0.);

		EXPECT_TRUE(expectResult == v + v2);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		Vector4<double> v2 = Vector4<double>::UnitY();

		Vector4<double> expectResult = Vector4<double>(1., 1., 0., 0.);

		EXPECT_TRUE(expectResult == v + v2);
	}
}

TEST(TestVec4, operatorSub)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		Vector4<double> v2 = Vector4<double>::UnitY();

		Vector4<double> expectResult = Vector4<double>(1., -1., 0., 0.);

		EXPECT_TRUE(expectResult == v - v2);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		Vector4<double> v2 = Vector4<double>::UnitY();

		Vector4<double> expectResult = Vector4<double>(1., -1., 0., 0.);

		EXPECT_TRUE(expectResult == v - v2);
	}
}

TEST(TestVec4, operatorScalarAdd)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(3., 2., 2., 2.);

		EXPECT_TRUE(expectResult == v + scalar);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(3., 2., 2., 2.);

		EXPECT_TRUE(expectResult == v + scalar);
	}

}

TEST(TestVec4, operatorScalarSub)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(-1., -2., -2., -2.);

		EXPECT_TRUE(expectResult == v - scalar);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(-1., -2., -2., -2.);

		EXPECT_TRUE(expectResult == v - scalar);
	}

}

TEST(TestVec4, operatorScalarMul)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(2., 0., 0., 0.);

		EXPECT_TRUE(expectResult == v * scalar);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(2., 0., 0., 0.);

		EXPECT_TRUE(expectResult == v * scalar);
	}

}


TEST(TestVec4, operatorScalarDiv)
{
	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(0.5f, 0., 0., 0.);

		EXPECT_TRUE(expectResult == v / scalar);
	}

	{
		Vector4<double> v = Vector4<double>::UnitX();
		double scalar = 2.;

		Vector4<double> expectResult = Vector4<double>(0.5, 0., 0., 0.);

		EXPECT_TRUE(expectResult == v / scalar);
	}

}

TEST(TestVec4, operatorBracket)
{
	Vector4<double> vec = Vector4<double>(1., 1., 1., 1.);

	uint8_t* ptr = reinterpret_cast<uint8_t*>(&vec.x);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[0]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[0]));
	ptr += sizeof(double);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[1]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[1]));
	ptr += sizeof(double);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[2]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[2]));
	ptr += sizeof(double);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[3]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[3]));
}

TEST(TestVec4, operatorEqual)
{
	EXPECT_TRUE(Vector4<double>::UnitX() == Vector4<double>::UnitX());
	EXPECT_FALSE(Vector4<double>::UnitX() == Vector4<double>::UnitY());

	EXPECT_TRUE(Vector4<double>::UnitX() != Vector4<double>::UnitZ());
	EXPECT_FALSE(Vector4<double>::UnitX() != Vector4<double>::UnitX());
}