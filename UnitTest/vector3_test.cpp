#include <gtest/gtest.h>

#include "math/toolbox_typedef.hpp"

#include <immintrin.h>


using namespace Tbx;

TEST(TestVec3, Constructor)
{
	Vector3<double> v = Vector3<double>(1., 2., 3.);
}

TEST(TestVec3, Magnitude)
{
	Vector3<double> v = Vector3<double>(1., 2., 3.);

	double mag = v.Magnitude();

	EXPECT_TRUE(IsEqual(mag, 3.74165750));


}

TEST(TestVec3, Normalize)
{
	Vector3<double> v = Vector3<double>(1., 0., 0.);

	EXPECT_TRUE(IsEqual(v.Magnitude(), 1.));

}


TEST(TestVec3, Distance)
{
	{
		Vector3<double> v = Vector3<double>(1., 0., 0.);

		Vector3<double> v1 = Vector3<double>(0., 1., 0.);

		double distance = Vector3<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.);
		EXPECT_FLOAT_EQ(Vector3<double>::Distance(v, v1), std::sqrt(2.));

	}
	
	{
		Vector3<double> v = Vector3<double>(1., 0., 0.);

		Vector3<double> v1 = Vector3<double>(0., 1., 0.);

		double distance = Vector3<double>::DistanceSquare(v, v1);

		EXPECT_FLOAT_EQ(distance, 2.);
		EXPECT_FLOAT_EQ(Vector3<double>::Distance(v, v1), std::sqrt(2.));
	}

}



TEST(TestVec3, Dot)
{
	double v = Vector3<double>::Dot(Vector3<double>::UnitX(), Vector3<double>::UnitY());
	EXPECT_TRUE(IsEqual(v, 0.));

	v = Vector3<double>::Dot(Vector3<double>::UnitX(), Vector3<double>::UnitZ());
	EXPECT_TRUE(IsEqual(v, 0.));

	v = Vector3<double>::Dot(Vector3<double>::UnitX(), Vector3<double>::UnitX());
	EXPECT_TRUE(IsEqual(v, 1.));
}

TEST(TestVec3, Cross)
{
	{
		Vector3<double> v = Vector3<double>::UnitX();

		Vector3<double> v1 = Vector3<double>::UnitY();

		Vector3<double> unitZ = Vector3<double>::Cross(Vector3<double>::UnitX(), Vector3<double>::UnitY());

		EXPECT_TRUE(unitZ == Vector3<double>::UnitZ());
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
		Vector3<double> v = Vector3<double>::UnitX();
		Vector3<double> v2 = Vector3<double>::UnitY();

		Vector3<double> expectResult = Vector3<double>(1., 1., 0.);

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
		Vector3<double> v = Vector3<double>::UnitX();
		Vector3<double> v2 = Vector3<double>::UnitY();

		Vector3<double> expectResult = Vector3<double>(1., -1., 0.);

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
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(3., 2., 2.);

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
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(-1., -2., -2.);

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
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(2., 0., 0.);

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
		Vector3<double> v = Vector3<double>::UnitX();
		double scalar = 2.;

		Vector3<double> expectResult = Vector3<double>(0.5f, 0., 0.);

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
	Vector3<double> vec = Vector3<double>(1., 1., 1.);

	uint8_t* ptr = reinterpret_cast<uint8_t*>(&vec.x);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[0]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[0]));
	ptr += sizeof(double);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[1]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[1]));
	ptr += sizeof(double);

	EXPECT_TRUE(ptr == (uint8_t*)&vec[2]);
	EXPECT_TRUE(IsEqual(*(double*)ptr, vec[2]));

}

TEST(TestVec3, operatorEqual)
{
	EXPECT_TRUE(Vector3<double>::UnitX() == Vector3<double>::UnitX());
	EXPECT_FALSE(Vector3<double>::UnitX() == Vector3<double>::UnitY());

	EXPECT_TRUE(Vector3<double>::UnitX() != Vector3<double>::UnitZ());
	EXPECT_FALSE(Vector3<double>::UnitX() != Vector3<double>::UnitX());
}