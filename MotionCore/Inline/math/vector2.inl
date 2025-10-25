
namespace Tbx
{
    template<typename T>
    constexpr T* Vector2<T>::GetPtr()
    {
        return &x;
    }

    template<typename T>
    constexpr const T* Vector2<T>::GetPtr() const
    {
        return &x;
    }

    template<typename T>
    constexpr FORCEINLINE T Vector2<T>::Dot(const Vector2<T> _v1, const Vector2<T> _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y;
    }

    template<typename T>
    FORCEINLINE T Vector2<T>::MagnitudeSquare() const
    {
        Vector2<T> v = *this;
        return Dot(v, v);
    }

    template<typename T>
    FORCEINLINE T Vector2<T>::Magnitude() const
    {
        return std::sqrt(MagnitudeSquare());
    }


    template<typename T>
    FORCEINLINE Vector2<T> Vector2<T>::Normalize() const
    {
        const T mag = Magnitude();

        if (IsEqual<T>(mag, static_cast<T>(1)))
            return *this;

        const T inv = 1 / mag;

        return { x * inv, y * inv };
    }

    template<typename T>
    constexpr FORCEINLINE T Vector2<T>::DistanceSquare(Vector2<T> _a, Vector2<T> _b)
    {
        const T dx = _a.x - _b.x;
        const T dy = _a.y - _b.y;
        const T result = (POWER(dx) + POWER(dy));

        return result;
    }

    template<typename T>
    FORCEINLINE T Vector2<T>::Distance(Vector2<T>_a, const Vector2<T> _b)
    {
        return std::sqrt(DistanceSquare(_a, _b));
    }

    template<typename T>
    constexpr FORCEINLINE T Vector2<T>::Cross(const Vector2 _v1, const Vector2 _v2)
    {
        return _v1.x * _v2.y - _v1.y * _v2.x;
    }


    template<typename T>
    constexpr Vector2<T>::Vector2(T valueX, T valueY) : x(valueX), y(valueY)
    {

    }

    template<typename T> Vector2<T> Vector2<T>::operator-() const
    {
        return Vector2<T>(-x, -y);
    }

    template<typename T> Vector2<T> Vector2<T>::operator+(const Vector2 _other) const
    {
        return { x + _other.x, y + _other.y };
    }

    template<typename T> Vector2<T> Vector2<T>::operator-(const Vector2 _other) const
    {
        return { x - _other.x, y - _other.y };
    }

    template<typename T> Vector2<T> Vector2<T>::operator/(const Vector2 _other) const
    {
        return { x / _other.x, y / _other.y };
    }

    template<typename T> void Vector2<T>::operator+=(const Vector2 _other)
    {
        x += _other.x;
        y += _other.y;
    }

    template<typename T> void Vector2<T>::operator-=(const Vector2 _other)
    {
        x -= _other.x;
        y -= _other.y;
    }

    template<typename T> void Vector2<T>::operator*=(const Vector2 _other)
    {
        x *= _other.x;
        y *= _other.y;
    }

    template<typename T> void Vector2<T>::operator/=(const Vector2 _other)
    {
        x /= _other.x;
        y /= _other.y;
    }

    template<typename T> Vector2<T> Vector2<T>::operator+(T _value) const
    {
        return { x + _value , y + _value };
    }

    template<typename T> Vector2<T> Vector2<T>::operator-(T _value) const
    {
        return { x - _value , y - _value };
    }

    template<typename T> Vector2<T> Vector2<T>::operator*(T _value) const
    {
        return { x * _value , y * _value };
    }

    template<typename T> Vector2<T> Vector2<T>::operator/(T _value) const
    {
        return { x / _value , y / _value };
    }


    template<typename T> Vector2<T>& Vector2<T>::operator+=(T _value)
    {
        x += _value;
        y += _value;
        return *this;
    }

    template<typename T> Vector2<T>& Vector2<T>::operator-=(T _value)
    {
        x -= _value;
        y -= _value;
        return *this;
    }
    template<typename T> Vector2<T>& Vector2<T>::operator*=(T _value)
    {
        x *= _value;
        y *= _value;
        return *this;
    }
    template<typename T> Vector2<T>& Vector2<T>::operator/=(T _value)
    {
        x /= _value;
        y /= _value;
        return *this;
    }

    template<typename T> T& Vector2<T>::operator[](size_t index)
    {
        return *static_cast<T*>(&x + index);
    }

    template<typename T> const T& Vector2<T>::operator[](size_t index) const
    {
        return *static_cast<const T*>(&x + index);
    }

    template<typename T> bool Vector2<T>::operator==(const Vector2<T>& _other) const
    {
        return x == _other.x && y == _other.y;
    }

    template<typename T> bool Vector2<T>::operator!=(const Vector2<T>& _other) const
    {
        return x != _other.x || y != _other.y;
    }

    template<typename T>
    FORCEINLINE CONSTEVAL Vector2<T> Vector2<T>::Zero()
    {
        return { static_cast<T>(0), static_cast<T>(0) };
    }

    template<typename T>
    FORCEINLINE CONSTEVAL Vector2<T> Vector2<T>::UnitX()
    {
        return { static_cast<T>(1), static_cast<T>(0) };
    }

    template<typename T>
    FORCEINLINE CONSTEVAL Vector2<T> Vector2<T>::UnitY()
    {
        return { static_cast<T>(0), static_cast<T>(1) };
    }

    template<typename T>
    FORCEINLINE CONSTEVAL Vector2<T> Vector2<T>::One()
    {
        return { static_cast<T>(1), static_cast<T>(1) };
    }
}
