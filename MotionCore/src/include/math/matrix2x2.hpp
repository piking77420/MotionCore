#pragma once
#include "toolbox_headerfile.hpp"

namespace Tbx
{
    template <typename T>
    struct Matrix2x2 
    {
        using DataType = T;
        static constexpr uint32_t Size = 2;

        FORCEINLINE static constexpr Matrix2x2 Identity();

        constexpr Matrix2x2() = default;

        ~Matrix2x2() = default;

        constexpr Matrix2x2(DataType m00, DataType m10, DataType m01, DataType m11);

        constexpr Matrix2x2(DataType _value);

        FORCEINLINE T& Get(uint32_t _colom, uint32_t _row);

        FORCEINLINE const T& Get(uint32_t _colom, uint32_t _row) const;

        FORCEINLINE T& operator[](uint32_t _offset);

        FORCEINLINE const T& operator[](uint32_t _offset) const;

        // Sould not be use to compute this*this
        Matrix2x2 operator*(const Matrix2x2& RESTRICT _other);

        Matrix2x2 operator*(DataType _value);

        void operator*=(DataType type);

        void operator*=(Matrix2x2 _m2);
      
        FORCEINLINE bool operator==(const Matrix2x2& _other) const;

        FORCEINLINE bool operator!=(const Matrix2x2& _other) const;

        Matrix2x2 Transpose() const;

        FORCEINLINE void Trace(T* array) const;

        FORCEINLINE constexpr T Determinant() const;

    private:
        T m_Data[Size * Size];
    };
}

#include "math/matrix2x2.inl"