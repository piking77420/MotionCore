#pragma once
#include "ToolBoxHeaderFile.hpp"

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

        explicit constexpr Vector4(DataType valueX, DataType valueY, DataType valueZ, DataType valueW);
        
        ~Vector4() = default;

        constexpr DataType* GetPtr();

        constexpr const DataType* GetPtr() const;

        DataType MagnitudeSquare() const;

        DataType Magnitude() const;

        Vector4<DataType> Normalize() const;

        FORCEINLINE constexpr static float Dot(const Vector4& _v1, const Vector4& _v2);

        FORCEINLINE constexpr static DataType DistanceSquare(const Vector4& _a, const Vector4& _b);

        FORCEINLINE constexpr static DataType Distance(const Vector4& _a, const Vector4& _b);

        constexpr Vector4 operator-();
        constexpr Vector4 operator+(const Vector4& _other);

        constexpr Vector4 operator-(const Vector4& _other);

        constexpr Vector4 operator*(const Vector4& _other);

        constexpr Vector4 operator/(const Vector4& _other);

        constexpr FORCEINLINE void operator+= (const Vector4& _other) noexcept;

        constexpr FORCEINLINE void operator-= (const Vector4& _other) noexcept;

        constexpr FORCEINLINE void operator*= (const Vector4& _other) noexcept;

        constexpr FORCEINLINE void operator/= (const Vector4& _other) noexcept;

        constexpr Vector4 operator+(DataType value);

        constexpr Vector4 operator-(DataType value);

        constexpr Vector4 operator*(DataType value);

        constexpr Vector4 operator/(DataType value);

        constexpr Vector4& operator+=(DataType value);

        constexpr Vector4& operator-=(DataType value);

        constexpr Vector4& operator*=(DataType value);

        constexpr Vector4& operator/=(DataType value);

        FORCEINLINE DataType& operator[](size_t index);

        FORCEINLINE const DataType& operator[](size_t index) const;

        FORCEINLINE bool operator==(const Vector4& _other) const;

        FORCEINLINE bool operator!=(const Vector4& _other);

        FORCEINLINE static CONSTEVAL Vector4 Zero() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); };

        FORCEINLINE static CONSTEVAL Vector4 UnitX() { return Vector4(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); };

        FORCEINLINE static CONSTEVAL Vector4 UnitY() { return Vector4(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); };

        FORCEINLINE static CONSTEVAL Vector4 UnitZ() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); };

        FORCEINLINE static CONSTEVAL Vector4 UnitW() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); };
    };

   
}

#include "math/vector4.inl"