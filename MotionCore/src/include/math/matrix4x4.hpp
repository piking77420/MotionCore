#pragma once
#include <immintrin.h>
#include <stacktrace>

namespace Tbx
{

    template <typename T>
    struct Matrix4x4
    {
        using DataType = T;
        static constexpr size_t Size = 4;

        constexpr Matrix4x4() = default;

        ~Matrix4x4() = default;

        template <typename U>
        Matrix4x4(const Matrix4x4<U>& other);
        
        constexpr Matrix4x4(DataType _m00, DataType _m10, DataType _m20, DataType _m30,
            DataType _m01, DataType _m11, DataType _m21, DataType _m31,
            DataType _m02, DataType _m12, DataType _m22, DataType _m32,
            DataType _m03, DataType _m13, DataType _m23, DataType _m33);

        constexpr Matrix4x4(DataType _value);

        FORCEINLINE constexpr static Matrix4x4 Identity();

        FORCEINLINE T& Get(uint32_t _colom, uint32_t _row);

        FORCEINLINE const T& Get(uint32_t _colom, uint32_t _row) const;

        FORCEINLINE const T& operator[](size_t _offset) const;

        FORCEINLINE T& operator[](size_t _offset);

        FORCEINLINE constexpr const DataType* GetPtr() const noexcept;

        FORCEINLINE constexpr DataType* GetPtr() noexcept;

        FORCEINLINE Matrix4x4 operator*(const Matrix4x4& RESTRICT _other) const;

        Matrix4x4 operator*(T _scalar) const;

        Matrix4x4 Transpose() const;

        T Determinant() const;


        FORCEINLINE bool operator==(const Matrix4x4& _other) const;

        FORCEINLINE bool operator!=(const Matrix4x4& _other) const;

        void operator*=(const Matrix4x4& _other);

    private:
        T m_Data[Size * Size];

    };
   
}

#include "math/matrix4x4.inl"