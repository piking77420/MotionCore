#pragma once
#include "toolbox_headerfile.hpp"



constexpr uint32_t TBX_PERMUTE_0X = 0;
constexpr uint32_t TBX_PERMUTE_0Y = 1;
constexpr uint32_t TBX_PERMUTE_0Z = 2;
constexpr uint32_t TBX_PERMUTE_0W = 3;
constexpr uint32_t TBX_PERMUTE_1X = 4;
constexpr uint32_t TBX_PERMUTE_1Y = 5;
constexpr uint32_t TBX_PERMUTE_1Z = 6;
constexpr uint32_t TBX_PERMUTE_1W = 7;


namespace Tbx
{

    template <typename T>
    class Vector4
    {
    public:
        using DataType = T;

        T x;
        T y;
        T z;
        T w;

        constexpr Vector4() = default;

        constexpr Vector4(DataType valueX, DataType valueY, DataType valueZ, DataType valueW);
        
        ~Vector4() = default;

        constexpr DataType* GetPtr();

        constexpr const DataType* GetPtr() const;

        DataType Magnitude() const;

        Vector4<DataType> Normalize() const;

        FORCEINLINE constexpr static float Dot(const Vector4& _v1, const Vector4& _v2);

        FORCEINLINE constexpr static DataType DistanceSquare(const Vector4& _a, const Vector4& _b);

        FORCEINLINE constexpr static DataType Distance(const Vector4& _a, const Vector4& _b);

        constexpr Vector4 operator-()
        {
            return { -x, -y, -z, -w };
        }

        constexpr Vector4 operator+(const Vector4& _other)
        {
            return { x + _other.x , y + _other.y, z + _other.z, w + _other.w };
        }

        constexpr Vector4 operator-(const Vector4& _other)
        {
            return { x - _other.x , y - _other.y, z - _other.z, w - _other.w };
        }

        constexpr Vector4 operator*(const Vector4& _other)
        {
            return { x * _other.x , y * _other.y, z * _other.z, w * _other.w };
        }

        constexpr Vector4 operator/(const Vector4& _other)
        {
            return { x / _other.x , y / _other.y, z / _other.z,  w / _other.w };
        }

        constexpr FORCEINLINE void operator+= (const Vector4& _other) noexcept
        {
            x += _other.x;
            y += _other.y;
            z += _other.z;
            w += _other.w;
        }

        constexpr FORCEINLINE void operator-= (const Vector4& _other) noexcept
        {
            x -= _other.x;
            y -= _other.y;
            z -= _other.z;
            w -= _other.w;
        }

        constexpr FORCEINLINE void operator*= (const Vector4& _other) noexcept
        {
            x *= _other.x;
            y *= _other.y;
            z *= _other.z;
            w *= _other.w;
        }

        constexpr FORCEINLINE void operator/= (const Vector4& _other) noexcept
        {
            x /= _other.x;
            y /= _other.y;
            z /= _other.z;
            w /= _other.w;
        }

        constexpr Vector4 operator+(DataType value)
        {
            return { x + value , y + value, z + value, w + value };
        }

        constexpr Vector4 operator-(DataType value)
        {
            return { x - value , y - value, z - value, w - value };
        }

        constexpr Vector4 operator*(DataType value)
        {
            return { x * value , y * value, z * value, w * value };
        }

        constexpr Vector4 operator/(DataType value)
        {
            return { x / value , y / value, z / value, w / value };
        }

        constexpr Vector4& operator+=(DataType value)
        {
            this->x += value;
            this->y += value;
            this->z += value;
            this->w += value;

            return *this;
        }

        constexpr Vector4& operator-=(DataType value)
        {
            this->x -= value;
            this->y -= value;
            this->z -= value;
            this->w -= value;

            return *this;
        }


        constexpr Vector4& operator*=(DataType value)
        {
            this->x *= value;
            this->y *= value;
            this->z *= value;
            this->w *= value;

            return *this;
        }

        constexpr Vector4& operator/=(DataType value)
        {
            this->x /= value;
            this->y /= value;
            this->z /= value;
            this->w /= value;

            return *this;
        }


        FORCEINLINE DataType& operator[](size_t index)
        {
            return *static_cast<T*>(&x + index);
        }

        FORCEINLINE const DataType& operator[](size_t index) const
        {
            return *static_cast<const T*>(&x + index);
        }

        FORCEINLINE bool operator==(const Vector4& _other) const
        {
            return x == _other.x && y == _other.y && z == _other.z && w == _other.w;
        }

        FORCEINLINE bool operator!=(const Vector4& _other)
        {
            return !(this == _other);
        }

        FORCEINLINE static CONSTEVAL Vector4 Zero() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); };

        FORCEINLINE static CONSTEVAL Vector4 UnitX() { return { static_cast<T>(1), static_cast<T>(0) ,static_cast<T>(0) }; };

        FORCEINLINE static CONSTEVAL Vector4 UnitY() { return { static_cast<T>(0), static_cast<T>(1) ,static_cast<T>(0) }; };

        FORCEINLINE static CONSTEVAL Vector4 UnitZ() { return { static_cast<T>(0), static_cast<T>(0) ,static_cast<T>(1) }; };

        FORCEINLINE static CONSTEVAL Vector4 UnitW() { return { static_cast<T>(0), static_cast<T>(0) ,static_cast<T>(1) , static_cast<T>(1) }; };
    };

    template <typename T, uint32_t PermuteX, uint32_t PermuteY, uint32_t PermuteZ, uint32_t PermuteW>
    static Vector4<T> Permute(const Vector4<T>& _vec1, const Vector4<T>& _vec2)
    {
        auto selectComponent = [&](uint32_t index) -> T {
            if (index < 4)
                return _vec1[index];
            if (index < 8)
                return _vec2[index - 4];
            throw std::exception("Invalid permutation index");
            };

        const T x = selectComponent(PermuteX);
        const T y = selectComponent(PermuteY);
        const T z = selectComponent(PermuteZ);
        const T w = selectComponent(PermuteW);

        return { x, y, z, w };
    }
}
