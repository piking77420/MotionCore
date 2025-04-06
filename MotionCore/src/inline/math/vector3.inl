
namespace Tbx
{
	
	template <typename T>
	constexpr Vector3<T>::Vector3(T valueX, T valueY, T valueZ) : x(valueX), y(valueY), z(valueZ)
	{
	}

	template<typename T>
	template<typename U>
	Vector3<T>::operator Vector3<U>() const
	{
		return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
	}

	template<typename T>
	constexpr T* Vector3<T>::GetPtr()
	{
		return &x;
	}

	template<typename T>
	constexpr const T* Vector3<T>::GetPtr() const
	{
		return &x;
	}

    template<typename T>
    FORCEINLINE T Vector3<T>::MagnitudeSquare() const
    {
        return POWER(x) + POWER(y) + POWER(z);
    }

    template<typename T>
    FORCEINLINE T Vector3<T>::Magnitude() const
    {
        return std::sqrt(MagnitudeSquare());
    }

    template<typename T>
    FORCEINLINE  Vector3<T> Vector3<T>::Normalize() const
    {
        const T mag = Magnitude();

        if (IsEqual<DataType>(mag, static_cast<T>(1)))
            return *this;

        const T InvMagnitude = static_cast<T>(1) / mag;

        return Vector3<T>(x * InvMagnitude, y * InvMagnitude, z * InvMagnitude);
    }

    template<typename T>
    FORCEINLINE constexpr T Vector3<T>::Dot(const Vector3& _v1, const Vector3& _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
    }

    template<typename T>
    FORCEINLINE constexpr Vector3<T> Vector3<T>::Cross(Vector3<T> _v1, Vector3<T> _v2)
    {
        return Vector3<T>(_v1.y * _v2.z - _v1.z * _v2.y,
            _v1.z * _v2.x - _v1.x * _v2.z,
            _v1.x * _v2.y - _v1.y * _v2.x);
    }

    template<typename T>
    constexpr FORCEINLINE T Vector3<T>::DistanceSquare(const Vector3<T>& _a, const Vector3<T>& _b)
    {
        const DataType dx = _a.x - _b.x;
        const DataType dy = _a.y - _b.y;
        const DataType dz = _a.z - _b.z;
        const DataType result = (dx * dx + dy * dy + dz * dz);

        return result;
    }

    
    template<typename T>
    FORCEINLINE T Vector3<T>::Distance(const Vector3<T>& _a, const Vector3<T>& _b)
    {
        return std::sqrt(DistanceSquare(_a, _b));
    }

    template<typename T>
    FORCEINLINE Vector3<T> Vector3<T>::NormalizeRadianVec3(Vector3 _randians)
    {
        return Vector3
        (
            NormalizeRadian<T>(_randians.x),
            NormalizeRadian<T>(_randians.y),
            NormalizeRadian<T>(_randians.z)
        );
    }
    
    template<typename T>
    FORCEINLINE Vector3<T>  Vector3<T>::operator-() const
    {
        return Vector3<T>(-x, -y, -z);
    }

    template<typename T>
    FORCEINLINE Vector3<T> Vector3<T>::operator+(const Vector3& other) const
    {
        return Vector3<T>(x + other.x, y + other.y, z + other.z);
    }

    template<typename T>
    FORCEINLINE Vector3<T>Vector3<T>::operator-(const Vector3& other) const
    {
        return Vector3<T>(x - other.x, y - other.y, z - other.z);
    }

    template<typename T>
    FORCEINLINE Vector3<T>Vector3<T>::operator*(const Vector3& other) const
    {
        return Vector3<T>(x * other.x, y * other.y, z * other.z);
    }

    template<typename T>
    FORCEINLINE Vector3<T>Vector3<T>::operator/(const Vector3& other) const
    {
        return Vector3<T>(x / other.x, y / other.y, z / other.z);
    }

    template<typename T>
    FORCEINLINE constexpr void Vector3<T>::operator+=(const Vector3& _Row1) noexcept
    {
        x += _Row1.x;
        y += _Row1.y;
        z += _Row1.z;
    }

    template<typename T>
    FORCEINLINE constexpr void Vector3<T>::operator-=(const Vector3& _Row1) noexcept
    {
        x -= _Row1.x;
        y -= _Row1.y;
        z -= _Row1.z;
    }

    template<typename T>
    FORCEINLINE constexpr void Vector3<T>::operator*=(const Vector3& _Row1) noexcept
    {
        x *= _Row1.x;
        y *= _Row1.y;
        z *= _Row1.z;
    }

    template<typename T>
    FORCEINLINE constexpr void Vector3<T>::operator/=(const Vector3& _Row1) noexcept
    {
        x /= _Row1.x;
        y /= _Row1.y;
        z /= _Row1.z;
    }

    template<typename T>
    FORCEINLINE Vector3<T> Vector3<T>::operator+(DataType value) const
    {
        return Vector3<T>(x + value, y + value, z + value);
    }
    

    template<typename T>
    FORCEINLINE Vector3<T>Vector3<T>::operator-(DataType value) const
    {
        return Vector3<T>(x - value, y - value, z - value );
    }

    template<typename T>
    FORCEINLINE Vector3<T> Vector3<T>::operator*(DataType value) const
    {
        return Vector3<T>(x * value, y * value, z * value );
    }

    template<typename T>
    FORCEINLINE void Vector3<T>::operator*=(DataType value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    template<typename T>
    FORCEINLINE Vector3<T> Vector3<T>::operator/(DataType value) const
    {
        return Vector3<T>(x / value, y / value, z / value );
    }


    template<typename T>
    FORCEINLINE void Vector3<T>::operator/=(DataType value) const
    {
        x /= value;
        y /= value;
        z /= value;
    }

    template<typename T>
    T& Vector3<T>::operator[](size_t _offset)
    {
        assert(_offset < 3 && "Out of bounds");

        return *(&x + _offset);
    }

    template<typename T>
    const T& Vector3<T>::operator[](size_t _offset) const
    {
        assert(_offset < 3 && "Out of bounds");

        return *(&x + _offset);
    }

    template<typename T>
    bool Vector3<T>::operator==(const Vector3& _other) const
    {
        return IsEqual(x, _other.x) && IsEqual(y, _other.y) && IsEqual(z, _other.z);
    }

    template<typename T>
    bool Vector3<T>::operator!=(const Vector3& _other)
    {
        return !(*this == _other);
    }

  

}

