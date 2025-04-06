#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

using namespace Tbx;

TEST(TestVec3, Constructor)
{
	Vector3<float> v = Vector3<float>(1.f, 2.f, 3.f);


	EXPECT_TRUE(IsEqual(v.x, 1.f));
	EXPECT_TRUE(IsEqual(v.y, 2.f));
	EXPECT_TRUE(IsEqual(v.z, 3.f));

}

TEST(TestVec3, Magnitude)
{
	Vector3<float> v = Vector3<float>(1.f, 2.f, 3.f);

	float mag = v.Magnitude();

	EXPECT_TRUE(IsEqual(mag, 3.74165750f));


}

TEST(TestVec3, Normalize)
{
	Vector3<float> v = Vector3<float>(1.f, 0.f, 0.f);

	EXPECT_TRUE(IsEqual(v.Magnitude(), 1.f));

}


TEST(TestVec3, Distance)
{
	{
		Vector3<float> v = Vector3<float>(1.f, 0.f, 0.f);

		Vector3<float> v1 = Vector3<float>(0.f, 1.f, 0.f);

		float distance = Vector3<float>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.f);
		EXPECT_FLOAT_EQ(Vector3<float>::Distance(v, v1), std::sqrt(2.f));

	}
	
	{
		Vector3<double> v = Vector3<double>(1., 0., 0.);

		Vector3<double> v1 = Vector3<double>(0., 1., 0.);

		double distance = Vector3<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.f);
		EXPECT_FLOAT_EQ(Vector3<double>::Distance(v, v1), std::sqrt(2.));
	}

}



TEST(TestVec3, Dot)
{
	float v = Vector3<float>::Dot(Vector3<float>::UnitX(), Vector3<float>::UnitY());
	EXPECT_TRUE(IsEqual(v, 0.f));

	v = Vector3<float>::Dot(Vector3<float>::UnitX(), Vector3<float>::UnitZ());
	EXPECT_TRUE(IsEqual(v, 0.f));

	v = Vector3<float>::Dot(Vector3<float>::UnitX(), Vector3<float>::UnitX());
	EXPECT_TRUE(IsEqual(v, 1.f));
}

TEST(TestVec3, Cross)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();

		Vector3<float> v1 = Vector3<float>::UnitY();

		Vector3<float> unitZ = Vector3<float>::Cross(Vector3<float>::UnitX(), Vector3<float>::UnitY());

		EXPECT_TRUE(unitZ == Vector3<float>::UnitZ());
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();

		Vector3<double> v1 = Vector3<double>::UnitY();

		Vector3<double> unitZ = Vector3<double>::Cross(Vector3<double>::UnitX(), Vector3<double>::UnitY());

		EXPECT_TRUE(unitZ == Vector3<double>::UnitZ());
	}
}

// operator


TEST(TestVec3, operatorAdd)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		Vector3<float> v2 = Vector3<float>::UnitY();

		Vector3<float> expectResult = Vector3<float>(1.f, 1.f, 0.f);

		EXPECT_TRUE(expectResult == v + v2);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		Vector3<double> v2 = Vector3<double>::UnitY();

		Vector3<double> expectResult = Vector3<double>(1., 1., 0.);

		EXPECT_TRUE(expectResult == v + v2);
	}
}

TEST(TestVec3, operatorSub)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		Vector3<float> v2 = Vector3<float>::UnitY();

		Vector3<float> expectResult = Vector3<float>(1.f, -1.f, 0.f);

		EXPECT_TRUE(expectResult == v - v2);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		Vector3<double> v2 = Vector3<double>::UnitY();

		Vector3<double> expectResult = Vector3<double>(1., -1., 0.);

		EXPECT_TRUE(expectResult == v - v2);
	}
}

TEST(TestVec3, operatorScalarAdd)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		float scalar = 2.f;

		Vector3<float> expectResult = Vector3<float>(3.f, 2.f, 2.f);

		EXPECT_TRUE(expectResult == v + scalar);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(3., 2., 2.);

		EXPECT_TRUE(expectResult == v + scalar);
	}
	
}

TEST(TestVec3, operatorScalarSub)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		float scalar = 2.f;

		Vector3<float> expectResult = Vector3<float>(-1.f, -2.f, -2.f);

		EXPECT_TRUE(expectResult == v - scalar);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(-1., -2., -2.);

		EXPECT_TRUE(expectResult == v - scalar);
	}

}

TEST(TestVec3, operatorScalarMul)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		float scalar = 2.f;

		Vector3<float> expectResult = Vector3<float>(2.f, 0.f, 0.f);

		EXPECT_TRUE(expectResult == v * scalar);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(2., 0., 0.);

		EXPECT_TRUE(expectResult == v * scalar);
	}

}


TEST(TestVec3, operatorScalarDiv)
{
	{
		Vector3<float> v = Vector3<float>::UnitX();
		float scalar = 2.f;

		Vector3<float> expectResult = Vector3<float>(0.5f, 0.f, 0.f);

		EXPECT_TRUE(expectResult == v / scalar);
	}

	{
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(0.5, 0., 0.);

		EXPECT_TRUE(expectResult == v / scalar);
	}

}

TEST(TestVec3, operatorBracket)
{
	Vector3<float> vec = Vector3<float>(1.f, 1.f, 1.f);

	uint8_t* ptr = reinterpret_cast<uint8_t*>(&vec.x);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[0]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[0]));
	ptr += sizeof(float);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[1]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[1]));
	ptr += sizeof(float);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[2]);
	EXPECT_TRUE(IsEqual(*(float*)ptr, vec[2]));

}

TEST(TestVec3, operatorEqual)
{
	EXPECT_TRUE(Vector3<float>::UnitX() == Vector3<float>::UnitX());
	EXPECT_FALSE(Vector3<float>::UnitX() == Vector3<float>::UnitY());

	EXPECT_TRUE(Vector3<float>::UnitX() != Vector3<float>::UnitZ());
	EXPECT_FALSE(Vector3<float>::UnitX() != Vector3<float>::UnitX());
}