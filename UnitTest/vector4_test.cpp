
#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;


TEST(TestVec4, Constructor)
{
	Vector4<float> v = Vector4<float>(1.f, 2.f, 3.f, 4.f);


	EXPECT_TRUE(IsEqual(v.x, 1.f));
	EXPECT_TRUE(IsEqual(v.y, 2.f));
	EXPECT_TRUE(IsEqual(v.z, 3.f));
	EXPECT_TRUE(IsEqual(v.w, 4.f));
}

TEST(TestVec4, Magnitude)
{
	Vector4<float> v = Vector4<float>(1.f, 2.f, 3.f, 4.f);

	float magSquare = v.MagnitudeSquare();

	EXPECT_FLOAT_EQ(magSquare, 30.f);

	float mag = v.Magnitude();

	EXPECT_FLOAT_EQ(mag ,std::sqrt(magSquare));
}

TEST(TestVec4, Normalize)
{
	Vector4<float> v = Vector4<float>(1.f, 0.f, 0.f, 0.f);

	EXPECT_TRUE(IsEqual(v.Magnitude(), 1.f));

}


TEST(TestVec4, Distance)
{
	{
		Vector4<float> v = Vector4<float>(1.f, 0.f, 0.f, 0.f);

		Vector4<float> v1 = Vector4<float>(0.f, 1.f, 0.f, 0.f);

		float distance = Vector4<float>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.f);
		EXPECT_FLOAT_EQ(Vector4<float>::Distance(v, v1), std::sqrt(2.f));

	}

	{
		Vector4<double> v = Vector4<double>(1., 0., 0., 0.);

		Vector4<double> v1 = Vector4<double>(0., 1., 0., 0.);

		double distance = Vector4<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.f);
		EXPECT_FLOAT_EQ(Vector4<double>::Distance(v, v1), std::sqrt(2.));
	}

}



TEST(TestVec4, Dot)
{
	float v = Vector4<float>::Dot(Vector4<float>::UnitX(), Vector4<float>::UnitY());
	EXPECT_TRUE(IsEqual(v, 0.f));

	v = Vector4<float>::Dot(Vector4<float>::UnitX(), Vector4<float>::UnitZ());
	EXPECT_TRUE(IsEqual(v, 0.f));

	v = Vector4<float>::Dot(Vector4<float>::UnitX(), Vector4<float>::UnitW());
	EXPECT_TRUE(IsEqual(v, 0.f));

	v = Vector4<float>::Dot(Vector4<float>::UnitX(), Vector4<float>::UnitX());
	EXPECT_TRUE(IsEqual(v, 1.f));

}


// operator
TEST(TestVec4, operatorAdd)
{
	{
		Vector4<float> v = Vector4<float>::UnitX();
		Vector4<float> v2 = Vector4<float>::UnitY();

		Vector4<float> expectResult = Vector4<float>(1.f, 1.f, 0.f, 0.f);

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
		Vector4<float> v = Vector4<float>::UnitX();
		Vector4<float> v2 = Vector4<float>::UnitY();

		Vector4<float> expectResult = Vector4<float>(1.f, -1.f, 0.f, 0.f);

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
		Vector4<float> v = Vector4<float>::UnitX();
		float scalar = 2.f;

		Vector4<float> expectResult = Vector4<float>(3.f, 2.f, 2.f, 2.f);

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
		Vector4<float> v = Vector4<float>::UnitX();
		float scalar = 2.f;

		Vector4<float> expectResult = Vector4<float>(-1.f, -2.f, -2.f, -2.f);

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
		Vector4<float> v = Vector4<float>::UnitX();
		float scalar = 2.f;

		Vector4<float> expectResult = Vector4<float>(2.f, 0.f, 0.f, 0.f);

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
		Vector4<float> v = Vector4<float>::UnitX();
		float scalar = 2.f;

		Vector4<float> expectResult = Vector4<float>(0.5f, 0.f, 0.f, 0.f);

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
	Vector4<float> vec = Vector4<float>(1.f, 1.f, 1.f, 1.f);

	uint8_t* ptr = reinterpret_cast<uint8_t*>(&vec.x);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[0]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[0]));
	ptr += sizeof(float);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[1]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[1]));
	ptr += sizeof(float);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[2]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[2]));
	ptr += sizeof(float);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[3]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[3]));
}

TEST(TestVec4, operatorEqual)
{
	EXPECT_TRUE(Vector4<float>::UnitX() == Vector4<float>::UnitX());
	EXPECT_FALSE(Vector4<float>::UnitX() == Vector4<float>::UnitY());

	EXPECT_TRUE(Vector4<float>::UnitX() != Vector4<float>::UnitZ());
	EXPECT_FALSE(Vector4<float>::UnitX() != Vector4<float>::UnitX());
}