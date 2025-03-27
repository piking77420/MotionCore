#pragma once

#include "toolbox_headerfile.hpp"

namespace Tbx
{

    template <typename T>
    class Vector2
    {
    public:
        using DataType = T;

        T x = static_cast<T>(0);
        T y = static_cast<T>(0);

        constexpr Vector2() = default;

        constexpr Vector2(DataType valueX, DataType valueY) : x(valueX), y(valueY) {} 
        
        ~Vector2() = default;

        TOOLBOX_INLINE constexpr DataType* GetPtr()
        {
            return &x;
        }

        TOOLBOX_INLINE constexpr const DataType* GetPtr() const
        {
            return &x;
        }
        constexpr static TOOLBOX_INLINE DataType Dot(const Vector2 _v1, const Vector2 _v2)
        {
            return _v1.x * _v2.x + _v1.y * _v2.y;
        }

        TOOLBOX_INLINE DataType MagnitudeSquare() const
        {
            Vector2 v = *this;
            return Dot(v, v);
        }

        TOOLBOX_INLINE DataType Magnitude() const
        {
            return std::sqrt(MagnitudeSquare());
        }

        TOOLBOX_INLINE Vector2 Normalize() const
        {
            const DataType mag = Magnitude();

            if (IsEqual<DataType>(mag, static_cast<T>(1)))
                return *this;

            return { x / mag, y / mag };
        }
        constexpr static TOOLBOX_INLINE DataType DistanceSquare(const Vector2& _a, const Vector2& _b)
        {
            const DataType dx = _a.x - _b.x;
            const DataType dy = _a.y - _b.y;
            const DataType result = (dx * dx + dy * dy);

            return result;
        }

        [[nodiscard]]
        static TOOLBOX_INLINE DataType Distance(const Vector2& _a, const Vector2& _b)
        {
            return std::sqrt(DistanceSquare(_a, _b));
        }

        constexpr static TOOLBOX_INLINE DataType Cross(const Vector2 _v1, const Vector2 _v2)
        {
            return _v1.x * _v2.y - _v1.y * _v2.x;
        }

        TOOLBOX_INLINE Vector2 operator-() const
        {
            return { -x, -y };
        }

        TOOLBOX_INLINE Vector2 operator+(const Vector2 _other) const
        {
            return { x + _other.x, y + _other.y };
        }

        TOOLBOX_INLINE Vector2 operator-(const Vector2 _other) const
        {
            return { x - _other.x, y - _other.y };
        }

        TOOLBOX_INLINE Vector2 operator/(const Vector2 _other) const
        {
            return { x / _other.x, y / _other.y };
        }

        TOOLBOX_INLINE void operator+=(const Vector2 _other)
        {
            x += _other.x;
            y += _other.y;
        }

        TOOLBOX_INLINE void operator-=(const Vector2 _other)
        {
            x -= _other.x;
            y -= _other.y;
        }

        TOOLBOX_INLINE void operator*=(const Vector2 _other)
        {
            x *= _other.x;
            y *= _other.y;
        }

        TOOLBOX_INLINE void operator/=(const Vector2 _other)
        {
            x /= _other.x;
            y /= _other.y;
        }

        TOOLBOX_INLINE Vector2 operator+(DataType _value) const
        {
            return { x + _value , y + _value };
        }

        TOOLBOX_INLINE Vector2 operator-(DataType _value) const
        {
            return { x - _value , y - _value };
        }

        TOOLBOX_INLINE Vector2 operator*(DataType _value) const
        {
            return { x * _value , y * _value };
        }

        TOOLBOX_INLINE Vector2 operator/(DataType _value) const
        {
            return { x / _value , y / _value };
        }


        TOOLBOX_INLINE Vector2& operator+=(DataType _value)
        {
            x += _value;
            y += _value;
            return *this;
        }

        TOOLBOX_INLINE Vector2& operator-=(DataType _value)
        {
            x -= _value;
            y -= _value;
            return *this;
        }
        TOOLBOX_INLINE Vector2& operator*=(DataType _value)
        {
            x *= _value;
            y *= _value;
            return *this;
        }
        TOOLBOX_INLINE Vector2& operator/=(DataType _value)
        {
            x /= _value;
            y /= _value;
            return *this;
        }

        TOOLBOX_INLINE DataType& operator[](size_t index)
        {
            return *static_cast<T*>(&x + index);
        }

        TOOLBOX_INLINE const DataType& operator[](size_t index) const
        {
            return *static_cast<const T*>(&x + index);
        }

        TOOLBOX_INLINE bool operator==(const Vector2& _other) const
        {
            return x == _other.x && y == _other.y;
        }

        TOOLBOX_INLINE bool operator!=(const Vector2& _other) const
        {
            return x != _other.x || y != _other.y;
        }

        std::string ToString() const
        {
            return  "X : " + std::to_string(x) + ", Y : " + std::to_string(y) + '\n';
        }

        TOOLBOX_INLINE static constexpr Vector2 Zero()
        {
            return { static_cast<T>(0), static_cast<T>(0) };
        }

        TOOLBOX_INLINE static constexpr Vector2 UnitX()
        {
            return { static_cast<T>(1), static_cast<T>(0) };
        }

        TOOLBOX_INLINE static constexpr Vector2 UnitY()
        {
            return { static_cast<T>(0), static_cast<T>(1) };
        }

        TOOLBOX_INLINE static constexpr Vector2 One()
        {
            return { static_cast<T>(1), static_cast<T>(1) };
        }

    private:

    };

}
