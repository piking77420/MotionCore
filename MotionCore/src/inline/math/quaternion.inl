
namespace Tbx
{
	template <typename T>
	constexpr Quaternion<T>::Quaternion(const DataType _real, const Vec3& _vec) : real(_real), imaginary(_vec)
	{

	}

	template <typename T>
	constexpr Quaternion<T>::Quaternion(const DataType _real, const DataType _x, const DataType _y, const DataType _z) : imaginary(Vec3(_x, _y, _z)), real(_real)
	{

	}

	template<typename T>
	template<typename U>
	Quaternion<T>::operator Quaternion<U>() const
	{
		return Quaternion<U>(static_cast<U>(real), static_cast<Vector3<U>>(imaginary));
	}
	

	template<typename T>
	FORCEINLINE CONSTEVAL Quaternion<T> Quaternion<T>::Identity() 
	{
		return Quaternion(static_cast<DataType>(1), Vec3::Zero());
	}

	template<typename T>
	FORCEINLINE T Quaternion<T>::MagnitudeSquare() const
	{
		return imaginary.MagnitudeSquare() + real * real;
	}

	template<typename T>
	FORCEINLINE T Quaternion<T>::Magnitude() const
	{
		return std::sqrt(MagnitudeSquare());
	}

	template<typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::Conjugate() const
	{
		return Quaternion(real, -imaginary);
	}

	template<typename T>
	FORCEINLINE constexpr T Quaternion<T>::Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.imaginary.x * q2.imaginary.x + q1.imaginary.y * q2.imaginary.y + q1.imaginary.z * q2.imaginary.z + q1.real * q2.real;
	}

	template<typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::Normalize() const
	{
		const DataType mag = Magnitude();

		if (IsEqual<DataType>(mag, static_cast<T>(1)))
			return *this;

		const DataType InvMagnitude = static_cast<T>(1) / mag;

		return  Quaternion(real * InvMagnitude, imaginary * InvMagnitude);
	}

	template<typename T>
	Vector3<T> Quaternion<T>::ToEulerAngles(const Quaternion& q)
	{
		const Matrix3x3<T> m = Rotation3x3(q);

		T T1 = std::atan2(m[7], m[8]);
		T C2 = std::sqrt(m[0] * m[0] + m[3] * m[3]);
		T T2 = std::atan2(-m[6], C2);
		T S1 = std::sin(T1);
		T C1 = std::cos(T1);
		T T3 = std::atan2(S1 * m[2] - C1 * m[1], C1 * m[4] - S1 * m[5]);

		return Vec3(-T1, -T2, -T3);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::Inverse() const
	{
		return Conjugate() / MagnitudeSquare();
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::FromEuler(const Vec3& eulerAngle)
	{
		const T halfAngleX = eulerAngle.x * static_cast<T>(0.5);
		const T halfAngleY = eulerAngle.y * static_cast<T>(0.5);
		const T halfAngleZ = eulerAngle.z * static_cast<T>(0.5);

		const T cX = std::cos(halfAngleX), sX = std::sin(halfAngleX);
		const T cY = std::cos(halfAngleY), sY = std::sin(halfAngleY);
		const T cZ = std::cos(halfAngleZ), sZ = std::sin(halfAngleZ);

		const T w = cX * cY * cZ + sX * sY * sZ;
		const T x = sX * cY * cZ - cX * sY * sZ;
		const T y = cX * sY * cZ + sX * cY * sZ;
		const T z = cX * cY * sZ - sX * sY * cZ;

		return Quaternion(w, Vec3(x, y, z));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::LookRotation(Vec3 _Nforward, Vec3 _Nupwards)
	{
		// Calculate right vector
		const Vec3 r = Vec3::Cross(_Nupwards, _Nforward).Normalize();

		// Recalculate orthogonal up vector
		const Vec3 orthoUp = Vec3::Cross(_Nforward, r);

		// Create rotation matrix
		// | r.x orthoUp.x f.x |
		// | r.y orthoUp.y f.y |
		// | r.z orthoUp.z f.z |

		T m00 = r.x, m01 = orthoUp.x, m02 = _Nforward.x;
		T m10 = r.y, m11 = orthoUp.y, m12 = _Nforward.y;
		T m20 = r.z, m21 = orthoUp.z, m22 = _Nforward.z;

		T trace = m00 + m11 + m22;

		Quaternion q;

		if (trace > static_cast<T>(0))
		{
			T s = std::sqrt(trace + static_cast<T>(1)) * static_cast<T>(0.5);
			T invS = static_cast<T>(0.25) / s;

			q.real = s;
			q.imaginary.x = (m21 - m12) * invS;
			q.imaginary.y = (m02 - m20) * invS;
			q.imaginary.z = (m10 - m01) * invS;
		}
		else
		{
			if (m00 > m11 && m00 > m22)
			{
				T s = std::sqrt(static_cast<T>(1) + m00 - m11 - m22) * static_cast<T>(0.5);
				T invS = static_cast<T>(0.25) / s;

				q.real = (m21 - m12) * invS;
				q.imaginary.x = s;
				q.imaginary.y = (m01 + m10) * invS;
				q.imaginary.z = (m02 + m20) * invS;
			}
			else if (m11 > m22)
			{
				T s = std::sqrt(static_cast<T>(1) + m11 - m00 - m22) * static_cast<T>(0.5);
				T invS = static_cast<T>(0.25) / s;

				q.real = (m02 - m20) * invS;
				q.imaginary.x = (m01 + m10) * invS;
				q.imaginary.y = s;
				q.imaginary.z = (m12 + m21) * invS;
			}
			else
			{
				T s = std::sqrt(static_cast<T>(1) + m22 - m00 - m11) * static_cast<T>(0.5);
				T invS = static_cast<T>(0.25) / s;

				q.real = (m10 - m01) * invS;
				q.imaginary.x = (m02 + m20) * invS;
				q.imaginary.y = (m12 + m21) * invS;
				q.imaginary.z = s;
			}
		}

		return q.Normalize();
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::FromMatrix(const Matrix3x3<T>& matrix)
	{
		Quaternion<T> q;
		const T trace = matrix[0] + matrix[4] + matrix[8];  // Trace of the matrix


		if (trace > static_cast<T>(0))
		{
			T s = std::sqrt(trace + static_cast<T>(1)) * static_cast<T>(0.5);
			q.real = s;
			s = q.real * static_cast<T>(4);
			q.imaginary.x = (matrix[5] - matrix[7]) / s;
			q.imaginary.y = (matrix[6] - matrix[2]) / s;
			q.imaginary.z = (matrix[1] - matrix[3]) / s;
		}
		else
		{
			assert(false && "TO DO HANDLE EDGE CASE");
		}


		return q;
	}


	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::FromAxisAngle(Vector3<T> _axis, T _angle)
	{
		_axis = _axis.Normalize();
		const T halfAngle = _angle * static_cast<T>(0.5);

		const T cos = std::cos(halfAngle);
		const T sin = std::sin(halfAngle);

		return Quaternion<T>(cos, _axis * sin);
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::ToAxisAngle(const Quaternion& _q, Vec3* _axis, T* _angle)
	{
		assert(_axis != nullptr && _angle != nullptr && "_axis or _angle is nullptr");

		T angle = static_cast<T>(2) * std::acos(_q.real);
		T invFactor = static_cast<T>(1) / std::sqrt(static_cast<T>(1) - _q.real * _q.real);

		*_axis = _q.imaginary * invFactor;
		*_angle = angle;
	}

	template <typename T>
	template<typename U>
	FORCEINLINE Quaternion<T> Quaternion<T>::Slerp(const Quaternion& q1, const Quaternion& q2, U t)
	{
		T cosOmega = Dot(q1, q2);

		bool flip = false;

		if (cosOmega < -Epsilon<T>())
		{
			flip = true;
			cosOmega = -cosOmega;
		}

		T s1, s2;

		if (cosOmega > (static_cast<T>(1.0f) - Epsilon<T>()))
		{
			// Too close, do straight linear interpolation.
			s1 = 1.0f - t;
			s2 = (flip) ? -t : t;
		}
		else
		{
			T omega = std::cos(cosOmega);
			T invSinOmega = 1.f / std::sin(omega);

			s1 = std::sin((1.0f - t) * omega) * invSinOmega;
			s2 = (flip)
				? -std::sin(t * omega) * invSinOmega
				: std::sin(t * omega) * invSinOmega;
		}

		Quaternion ans;
		ans.imaginary.x = s1 * q1.imaginary.x + s2 * q2.imaginary.x;
		ans.imaginary.y = s1 * q1.imaginary.y + s2 * q2.imaginary.y;
		ans.imaginary.z = s1 * q1.imaginary.z + s2 * q2.imaginary.z;
		ans.real = s1 * q1.real + s2 * q2.real;

		return ans.Normalize();
	}

	template <typename T>
	template<typename U>
	FORCEINLINE Quaternion<T> Quaternion<T>::Nlerp(const Quaternion& q1, const Quaternion& q2, U t)
	{
		T cosOmega = Dot(q1, q2);

		bool flip = false;

		// If the dot product is negative, flip the sign of q2 to take the shortest path
		if (cosOmega < static_cast<T>(0))
		{
			flip = true;
			cosOmega = -cosOmega;
		}

		T s1, s2;

		// If the quaternions are very close, use linear interpolation directly
		if (cosOmega > (static_cast<T>(1.0f) - Epsilon<T>()))
		{
			s1 = static_cast<T>(1.0f) - t;
			s2 = flip ? -t : t;
		}
		else
		{
			// Otherwise, perform a standard linear interpolation between q1 and q2
			T omega = std::acos(cosOmega);  // Angle between the quaternions
			T invSinOmega = static_cast<T>(1.0f) / std::sin(omega);  // Inverse of sine of omega

			s1 = std::sin((static_cast<T>(1.0f) - t) * omega) * invSinOmega;
			s2 = flip ? -std::sin(t * omega) * invSinOmega : std::sin(t * omega) * invSinOmega;
		}

		// Perform the interpolation and construct the resulting quaternion
		Quaternion<T> result;
		result.real = s1 * q1.real + s2 * q2.real;
		result.imaginary.x = s1 * q1.imaginary.x + s2 * q2.imaginary.x;
		result.imaginary.y = s1 * q1.imaginary.y + s2 * q2.imaginary.y;
		result.imaginary.z = s1 * q1.imaginary.z + s2 * q2.imaginary.z;

		// Normalize the result to ensure it's a unit quaternion
		return result.Normalize();
	}
	

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator+(const Quaternion& _other)
	{
		return Quaternion(real + _other.real, imaginary + _other.imaginary);
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator-(const Quaternion& _other)
	{
		return Quaternion(real - _other.real, imaginary - _other.imaginary);
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator*(const Quaternion& _other) const
	{
		const DataType newReal = real * _other.real
			- Vec3::Dot(imaginary, _other.imaginary);

		const DataType i = imaginary.x * _other.real + real * _other.imaginary.x
			- imaginary.z * _other.imaginary.y + imaginary.y * _other.imaginary.z;

		const DataType j = imaginary.y * _other.real + imaginary.z * _other.imaginary.x
			+ real * _other.imaginary.y - imaginary.x * _other.imaginary.z;

		const DataType k = imaginary.z * _other.real - imaginary.y * _other.imaginary.x
			+ imaginary.x * _other.imaginary.y + real * _other.imaginary.z;

		return Quaternion(newReal, Vector3<T>(i, j, k));
	}

	template <typename T>
	FORCEINLINE Vector3<T> Quaternion<T>::operator*(const Vec3& _vec) const
	{
		Quaternion vecQuat(static_cast<T>(0), _vec.x, _vec.y, _vec.z);
		Quaternion resQuat = Conjugate() * vecQuat * (*this);
		return resQuat.imaginary;
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator+(const Vec3& _vec) const
	{
		Quaternion result = *this;

		Quaternion q(static_cast<T>(0), _vec);
		q *= result;

		result.real += q.real * static_cast<T>(0.5);
		result.imaginary.x += q.imaginary.x * static_cast<T>(0.5);
		result.imaginary.y += q.imaginary.y * static_cast<T>(0.5);
		result.imaginary.z += q.imaginary.z * static_cast<T>(0.5);

		return result;
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator+(T _value)
	{
		return Quaternion(real + _value, imaginary + _value);
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator-(T _value)
	{
		return Quaternion(real - _value, imaginary - _value);
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator*(T _value)
	{
		return Quaternion(real * _value, imaginary * _value);
	}

	template <typename T>
	FORCEINLINE Quaternion<T> Quaternion<T>::operator/(T _value)
	{
		const DataType invv = static_cast<T>(1) / _value;

		return Quaternion(real * invv, imaginary * invv);
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator-=(const Quaternion& _other)
	{
		*this = *this - _other;
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator*=(const Quaternion& _other)
	{
		*this = *this * _other;
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator+=(T _value)
	{
		*this = *this + _value;
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator-=(T _value)
	{
		*this = *this - _value;
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator*=(T _value)
	{
		*this = *this * _value;
	}

	template <typename T>
	FORCEINLINE void Quaternion<T>::operator/=(T _value)
	{
		*this = *this / _value;
	}

	template <typename T>
	FORCEINLINE bool Quaternion<T>::operator==(const Quaternion& _other) const
	{
		return IsEqual(real, _other.real) && IsEqual(imaginary.x, _other.imaginary.x) && IsEqual(imaginary.y, _other.imaginary.y) && IsEqual(imaginary.z, _other.imaginary.z);
	}


	template <typename T>
	FORCEINLINE bool Quaternion<T>::operator!=(const Quaternion& _other) const
	{
		return !(*this == _other);
	}

}