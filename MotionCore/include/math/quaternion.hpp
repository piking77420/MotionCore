#pragma once
#include <string>

#include "toolbox_typedef.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace Tbx
{

	template <typename T>
	class Quaternion
	{
	public:
		using DataType = T;
		using Vec3 = Vector3<DataType>;

		Vec3 imaginary = Vec3::Zero();
		DataType real = static_cast<T>(0);

		Quaternion() = default;

		Quaternion(const Vec3& _vec, const DataType _real) : imaginary(_vec), real(_real)
		{

		}

		Quaternion(const DataType _x, const DataType _y, const DataType _z, const DataType _real) : imaginary({ _x, _y, _z }), real(_real)
		{

		}

		template<typename U>
		operator Quaternion<U>() const {
			return Quaternion<U>(static_cast<Vector3<U>>(imaginary), static_cast<U>(real));
		}

		~Quaternion() = default;

		constexpr static TOOLBOX_INLINE Quaternion Identity() { return { Vec3::Zero(), static_cast<DataType>(1) }; }

		TOOLBOX_INLINE DataType MagnitudeSquare() const
		{
			return imaginary.MagnitudeSquare() + real * real;
		}

		TOOLBOX_INLINE DataType Magnitude() const
		{
			return std::sqrt(MagnitudeSquare());
		}

		TOOLBOX_INLINE Quaternion Conjugate() const
		{
			return { -imaginary, real };
		}

		TOOLBOX_INLINE static constexpr DataType DotProduct(const Quaternion& q1, const Quaternion& q2)
		{
			return q1.imaginary.x * q2.imaginary.x + q1.imaginary.y * q2.imaginary.y + q1.imaginary.z * q2.imaginary.z + q1.real * q2.real;
		}

		TOOLBOX_INLINE Quaternion Normalize() const
		{
			const DataType mag = Magnitude();

			if (IsEqualTo<DataType>(mag, static_cast<T>(1)))
				return *this;

			const DataType InvMagnitude = static_cast<T>(1) / mag;

			return { imaginary.x * InvMagnitude, imaginary.y * InvMagnitude, imaginary.z * InvMagnitude, real * InvMagnitude };
		}

		Quaternion Inverse() const
		{
			return Conjugate() / MagnitudeSquare();
		}

		Quaternion LookAt(Vec3 _sourcePoint, Vec3 _destPoint, const Vec3 forward) const
		{
			Vec3 forwardVector = (_destPoint - _sourcePoint).Normalize();

			Vec3 rotAxis = Vec3::Cross(forward, forwardVector);
			DataType dot = Vec3::Dot(forward, forwardVector);

			Quaternion q;
			q.imaginary.x = rotAxis.x;
			q.imaginary.y = rotAxis.y;
			q.imaginary.z = rotAxis.z;
			q.real = dot + static_cast<DataType>(1);

			return { rotAxis, dot + 1 };
		}

		TOOLBOX_INLINE Quaternion operator+(const Quaternion& _other)
		{
			return { imaginary + _other.imaginary, real + _other.real };
		}

		TOOLBOX_INLINE Quaternion operator-(const Quaternion& _other)
		{
			return { imaginary - _other.imaginary, real - _other.real };
		}

		TOOLBOX_INLINE Quaternion operator*(const Quaternion& _other) const
		{
			const DataType newReal = real * _other.real
				- Vec3::Dot(imaginary, _other.imaginary);

			const DataType i = imaginary.x * _other.real + real * _other.imaginary.x
				- imaginary.z * _other.imaginary.y + imaginary.y * _other.imaginary.z;

			const DataType j = imaginary.y * _other.real + imaginary.z * _other.imaginary.x
				+ real * _other.imaginary.y - imaginary.x * _other.imaginary.z;

			const DataType k = imaginary.z * _other.real - imaginary.y * _other.imaginary.x
				+ imaginary.x * _other.imaginary.y + real * _other.imaginary.z;

			return { { i, j, k}, newReal };
		}

		TOOLBOX_INLINE Vec3 operator*(const Vec3& _vec) const
		{
			Quaternion vecQuat(_vec.x, _vec.y, _vec.z, 0.f);
			Quaternion resQuat = Conjugate() * vecQuat * (*this);
			return resQuat.imaginary;
		}

		TOOLBOX_INLINE Quaternion operator+(const Vec3& _vec) const
		{
			Quaternion result = *this;

			Quaternion q(_vec, static_cast<T>(0));
			q *= result;

			result.real += q.real * static_cast<T>(0.5);
			result.imaginary.x += q.imaginary.x * static_cast<T>(0.5);
			result.imaginary.y += q.imaginary.y * static_cast<T>(0.5);
			result.imaginary.z += q.imaginary.z * static_cast<T>(0.5);

			return result;
		}

		TOOLBOX_INLINE Quaternion operator+(T _value)
		{
			return { imaginary + _value, real + _value };
		}

		TOOLBOX_INLINE Quaternion operator-(T _value)
		{
			return { imaginary - _value, real - _value };
		}

		TOOLBOX_INLINE Quaternion operator*(T _value)
		{
			return { imaginary * _value, real * _value };
		}

		TOOLBOX_INLINE Quaternion operator/(T _value)
		{
			return { imaginary / _value, real / _value };
		}

		TOOLBOX_INLINE void operator+=(const Quaternion& _other)
		{
			*this = *this + _other;
		}

		TOOLBOX_INLINE void operator-=(const Quaternion& _other)
		{
			*this = *this - _other;
		}

		TOOLBOX_INLINE void operator*=(const Quaternion& _other)
		{
			*this = *this * _other;
		}

		TOOLBOX_INLINE void operator+=(T _value)
		{
			*this = *this + _value;
		}

		TOOLBOX_INLINE void operator-=(T _value)
		{
			*this = *this - _value;
		}

		TOOLBOX_INLINE void operator*=(T _value)
		{
			*this = *this * _value;
		}

		TOOLBOX_INLINE void operator/=(T _value)
		{
			*this = *this / _value;
		}

		TOOLBOX_INLINE void operator+=(const Vec3 _vec)
		{
			*this = *this + _vec;
		}

		TOOLBOX_INLINE bool operator==(const Quaternion& _other) const
		{
			return IsEqualTo(imaginary.x, _other.imaginary.x) && IsEqualTo(imaginary.y, _other.imaginary.y) && IsEqualTo(imaginary.z, _other.imaginary.z)
				&& IsEqualTo(real, _other.real);
		}
		Vec3 ToEulerAngles() const
		{
			T roll = atan2f(2 * imaginary.x * real - 2 * imaginary.y * imaginary.z,
			                    1 - 2 * imaginary.x * imaginary.x - 2 * imaginary.z * imaginary.z);
			T pitch = atan2f(2 * imaginary.y * real - 2 * imaginary.x * imaginary.z,
			                     1 - 2 * imaginary.y * imaginary.y - 2 * imaginary.z * imaginary.z);
			T yaw = asinf(2 * imaginary.x * imaginary.y + 2 * imaginary.z * real);


			return { roll, pitch, yaw };
		}

		static Quaternion FromEuler(const Vec3& eulerAngle)
		{
			Vec3 c, s;

			Vec3 halfAngle = eulerAngle * static_cast<T>(0.5);
			c = Vec3(std::cos(halfAngle.x), std::cos(halfAngle.y), std::cos(halfAngle.z));
			s = Vec3(std::sin(halfAngle.x), std::sin(halfAngle.y), std::sin(halfAngle.z));

			T w = c.x * c.y * c.z + s.x * s.y * s.z;
			T i = s.x * c.y * c.z - c.x * s.y * s.z;
			T j = c.x * s.y * c.z + s.x * c.y * s.z;
			T k = c.x * c.y * s.z - s.x * s.y * c.z;

			return Quaternion(i, j, k, w);
		}

		static inline void SinCos(const Vector4<T>& angles, Vector4<T>& sinOut, Vector4<T>& cosOut)
		{
			for (int i = 0; i < 4; ++i) {
				sinOut[i] = std::sin(angles[i]);
				cosOut[i] = std::cos(angles[i]);
			}
		}

		/*
		static Quaternion FromEuler(const Vector4<T>& _vector4) // <Pitch, Yaw, Roll, 0>
		{
			constexpr Vector4<T>  Sign = { 1.0f, -1.0f, -1.0f, 1.0f };

			// Half the angles
			Vector4<T> halfAngles = {_vector4[0] * 0.5f, _vector4[1] * 0.5f, _vector4[2] * 0.5f, _vector4[3] * 0.5f};

			// Calculate sine and cosine of half-angles
			Vector4<T> sinAngles, cosAngles;
			SinCos(halfAngles, sinAngles, cosAngles);

			Vector4<T> P0 = Permute<T,TBX_PERMUTE_0X, TBX_PERMUTE_1X, TBX_PERMUTE_1X, TBX_PERMUTE_1X>(sinAngles, cosAngles);
			Vector4<T> Y0 = Permute<T,TBX_PERMUTE_1Y, TBX_PERMUTE_0Y, TBX_PERMUTE_1Y, TBX_PERMUTE_1Y>(sinAngles, cosAngles);
			Vector4<T> R0 = Permute<T,TBX_PERMUTE_1Z, TBX_PERMUTE_1Z, TBX_PERMUTE_0Z, TBX_PERMUTE_1Z>(sinAngles, cosAngles);

			Vector4<T> P1 = Permute<T,TBX_PERMUTE_0X, TBX_PERMUTE_1X, TBX_PERMUTE_1X, TBX_PERMUTE_1X>(cosAngles, sinAngles);
			Vector4<T> Y1 = Permute<T,TBX_PERMUTE_1Y, TBX_PERMUTE_0Y, TBX_PERMUTE_1Y, TBX_PERMUTE_1Y>(cosAngles, sinAngles);
			Vector4<T> R1 = Permute<T,TBX_PERMUTE_1Z, TBX_PERMUTE_1Z, TBX_PERMUTE_0Z, TBX_PERMUTE_1Z>(cosAngles, sinAngles);

			// Compute quaternions
			Vector4<T> Q1 = P1 * Sign;
			Vector4<T> Q0 = P0 * Y0;
			Q1 = Q1 * Y1;
			Q0 = Q0 * R0;
			const Vector4<T> Q = (Q1 * R1)  + Q0;

			return {Q.x, Q.y, Q.z, Q.w};
		}*/

		static Quaternion FromMatrix(const Matrix3x3<T>& matrix)
		{
			Quaternion q;
			q.real = std::sqrt(static_cast<T>(1) + matrix[0][0] + matrix[1][1] + matrix[2][2]) / static_cast<T>(2);
			q.imaginary.x = (matrix[2][1] - matrix[1][2]) / static_cast<T>(4) * q.real;
			q.imaginary.y = (matrix[0][2] - matrix[2][0]) / static_cast<T>(4) * q.real;
			q.imaginary.z = (matrix[1][0] - matrix[0][1]) / static_cast<T>(4) * q.real;

			return q;
		}

		template<typename U>
		[[nodiscard]] static TOOLBOX_INLINE Quaternion Slerp(const Quaternion& t1, const Quaternion& t2, U t)
		{
			float cosOmega = DotProduct(t1, t2);

			bool flip = false;

			if (cosOmega < -std::numeric_limits<U>::epsilon())
			{
				flip = true;
				cosOmega = -cosOmega;
			}

			float s1, s2;

			if (cosOmega > (1.0f - std::numeric_limits<U>::epsilon()))
			{
				// Too close, do straight linear interpolation.
				s1 = 1.0f - t;
				s2 = (flip) ? -t : t;
			}
			else
			{
				float omega = std::cos(cosOmega);
				float invSinOmega = 1.f / std::sin(omega);

				s1 = std::sin((1.0f - t) * omega) * invSinOmega;
				s2 = (flip)
					? -std::sin(t * omega) * invSinOmega
					: std::sin(t * omega) * invSinOmega;
			}

			Quaternion ans;
			ans.imaginary.x = s1 * t1.imaginary.x + s2 * t2.imaginary.x;
			ans.imaginary.y = s1 * t1.imaginary.y + s2 * t2.imaginary.y;
			ans.imaginary.z = s1 * t1.imaginary.z + s2 * t2.imaginary.z;
			ans.real = s1 * t1.real + s2 * t2.real;

			return ans;
		}

		[[nodiscard]]
		std::string ToString() const
		{
			return "X : " + std::to_string(imaginary.x) + ", Y : " + std::to_string(imaginary.y) + ", Z : " + std::to_string(imaginary.z) + ", W : " + std::to_string(real) + '\n';
		}


	};

	
}