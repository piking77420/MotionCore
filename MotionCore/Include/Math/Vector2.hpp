#pragma once
#include "ToolBoxHeaderFile.hpp"

namespace Tbx
{

    template <typename T>
    struct Vector2
    {
        using DataType = T;

        T x;
        T y;

        constexpr Vector2() = default;

        constexpr Vector2(DataType valueX, DataType valueY);
        
        // TO DO
        //explicit constexpr Vector2(DataType valueX, DataType valueY);

        ~Vector2() = default;

         constexpr FORCEINLINE DataType* GetPtr();

        constexpr FORCEINLINE const DataType* GetPtr() const;

        constexpr static FORCEINLINE DataType Dot(const Vector2 _v1, const Vector2 _v2);

        FORCEINLINE DataType MagnitudeSquare() const;

        FORCEINLINE DataType Magnitude() const;

        FORCEINLINE Vector2 Normalize() const;

        constexpr static FORCEINLINE DataType DistanceSquare(Vector2 _a, Vector2 _b);

        static FORCEINLINE DataType Distance(Vector2 _a, Vector2 _b);

        constexpr static FORCEINLINE DataType Cross(const Vector2 _v1, const Vector2 _v2);

        FORCEINLINE Vector2 operator-() const;

        FORCEINLINE Vector2 operator+(const Vector2 _other) const;

        FORCEINLINE Vector2 operator-(const Vector2 _other) const;

        FORCEINLINE Vector2 operator/(const Vector2 _other) const;

        FORCEINLINE void operator+=(const Vector2 _other);

        FORCEINLINE void operator-=(const Vector2 _other);

        FORCEINLINE void operator*=(const Vector2 _other);

        FORCEINLINE void operator/=(const Vector2 _other);

        FORCEINLINE Vector2 operator+(DataType _value) const;

        FORCEINLINE Vector2 operator-(DataType _value) const;

        FORCEINLINE Vector2 operator*(DataType _value) const;

        FORCEINLINE Vector2 operator/(DataType _value) const;

        FORCEINLINE Vector2& operator+=(DataType _value);

        FORCEINLINE Vector2& operator-=(DataType _value);

        FORCEINLINE Vector2& operator*=(DataType _value);

        FORCEINLINE Vector2& operator/=(DataType _value);

        FORCEINLINE DataType& operator[](size_t index);

        FORCEINLINE const DataType& operator[](size_t index) const;

        FORCEINLINE bool operator==(const Vector2& _other) const;

        FORCEINLINE bool operator!=(const Vector2& _other) const;

        FORCEINLINE static CONSTEVAL Vector2 Zero();

        FORCEINLINE static CONSTEVAL Vector2 UnitX();

        FORCEINLINE static CONSTEVAL Vector2 UnitY();

        FORCEINLINE static CONSTEVAL Vector2 One();

    };


   
}

#include "math/vector2.inl"