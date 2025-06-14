#pragma once
#include "toolbox_headerfile.hpp"

namespace Tbx
{
    template <typename T>
    class Vector3
    {
    public:
        T x;
        T y;
        T z;

        using DataType = T;

        constexpr Vector3() = default;

        explicit constexpr Vector3(DataType valueX, DataType valueY, DataType valueZ);

        template<typename U>
        operator Vector3<U>() const;

        ~Vector3() = default;

        FORCEINLINE constexpr DataType* GetPtr();

        FORCEINLINE constexpr const DataType* GetPtr() const;

        FORCEINLINE DataType MagnitudeSquare() const;

        FORCEINLINE DataType Magnitude() const;

        FORCEINLINE Vector3 Normalize() const;

        FORCEINLINE constexpr static DataType Dot(const Vector3& _v1, const Vector3& _v2);

        FORCEINLINE constexpr static Vector3 Cross(Vector3 _v1, Vector3 _v2);

        constexpr static FORCEINLINE DataType DistanceSquare(const Vector3& _a, const Vector3& _b);

        FORCEINLINE static DataType Distance(const Vector3& _a, const Vector3& _b);

        FORCEINLINE static Vector3 NormalizeRadianVec3(Vector3 _randians);

        FORCEINLINE Vector3 operator-() const;

        FORCEINLINE Vector3 operator+(const Vector3& other) const;

        FORCEINLINE Vector3 operator-(const Vector3& other) const;

        FORCEINLINE Vector3 operator*(const Vector3& other) const;

        FORCEINLINE Vector3 operator/(const Vector3& other) const;

        FORCEINLINE constexpr void operator+=(const Vector3& _Row1) noexcept;

        FORCEINLINE constexpr void operator-=(const Vector3& _Row1) noexcept;

        FORCEINLINE constexpr void operator*=(const Vector3& _Row1) noexcept;

        FORCEINLINE constexpr void operator/=(const Vector3& _Row1) noexcept;

        FORCEINLINE Vector3 operator+(DataType value) const;

        FORCEINLINE Vector3 operator-(DataType value) const;

        FORCEINLINE Vector3 operator*(DataType value) const;

        FORCEINLINE void operator*=(DataType value);

        FORCEINLINE Vector3 operator/(DataType value) const;

        FORCEINLINE void operator/=(DataType value) const;

        FORCEINLINE DataType& operator[](size_t _offset);

        FORCEINLINE const DataType& operator[](size_t _offset) const;

        FORCEINLINE bool operator==(const Vector3& _other) const;

        FORCEINLINE bool operator!=(const Vector3& _other);

        FORCEINLINE static CONSTEVAL Vector3 Zero() { return Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

        FORCEINLINE static CONSTEVAL Vector3 UnitX() { return Vector3(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

        FORCEINLINE static CONSTEVAL Vector3 UnitY() { return Vector3(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

        FORCEINLINE static CONSTEVAL Vector3 UnitZ() { return Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

        FORCEINLINE static CONSTEVAL Vector3 UnitOne() { return Vector3(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)); }
    private:
    };
  
}

#include "math/vector3.inl"