#pragma once
namespace Tbx
{
    template <typename T>
    struct Matrix3x3
    {
        static constexpr size_t Size = 3;

        constexpr Matrix3x3() = default;

        ~Matrix3x3() = default;

        constexpr Matrix3x3(T m00, T m10, T m20,
            T m01, T m11, T m21,
            T m02, T m12, T m22);

        constexpr Matrix3x3(T _value);

        FORCEINLINE constexpr static Matrix3x3 Identity();

        FORCEINLINE T& Get(uint32_t _colom, uint32_t _row);

        FORCEINLINE const T& Get(uint32_t _colom, uint32_t _row) const;

        FORCEINLINE T& operator[](uint32_t _offset);

        FORCEINLINE const T& operator[](uint32_t _offset) const;

        Matrix3x3 operator*(const Matrix3x3& RESTRICT _other) const;

        Matrix3x3 operator*(const T _scalar) const;

        void operator*=(const Matrix3x3& RESTRICT _other);

        FORCEINLINE bool operator==(const Matrix3x3& RESTRICT _other) const;

        FORCEINLINE bool operator!=(const Matrix3x3& RESTRICT _other) const;

        FORCEINLINE void Trace(T* _trace) const;

        constexpr T Determinant() const;

        FORCEINLINE Matrix3x3 Transpose() const;

        Matrix3x3 AdjoinMatrix() const;

        Matrix3x3 Invert() const;

        void ExtractEulerAngleXYZ(T* _xyz);
    private:
        T m_Data[Size * Size];
    };
}
    

#include "math/matrix3x3.inl"