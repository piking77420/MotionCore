#include "matrix3x3.hpp"
#pragma once

namespace Tbx
{
    template<typename T>
    constexpr Matrix3x3<T>::Matrix3x3(T m00, T m10, T m20,
        T m01, T m11, T m21,
        T m02, T m12, T m22)
    {
        m_Data[0] = m00;
        m_Data[1] = m10;
        m_Data[2] = m20;

        m_Data[3] = m01;
        m_Data[4] = m11;
        m_Data[5] = m21;

        m_Data[6] = m02;
        m_Data[7] = m12;
        m_Data[8] = m22;
    }

    template<typename T>
    inline constexpr Matrix3x3<T>::Matrix3x3(const Vector3<T>& _vec1, const Vector3<T>& _vec2, const Vector3<T>& _vec3)
    {
        m_Data[0] = _vec1.x;
        m_Data[1] = _vec1.y;
        m_Data[2] = _vec1.z;

        m_Data[3] = _vec2.x;
        m_Data[4] = _vec2.y;
        m_Data[5] = _vec2.z;

        m_Data[6] = _vec3.x;
        m_Data[7] = _vec3.y;
        m_Data[8] = _vec3.z;
    }

    template<typename T>
    constexpr Matrix3x3<T>::Matrix3x3(T _value)
    {
        m_Data[0] = _value;
        m_Data[1] = _value;
        m_Data[2] = _value;

        m_Data[3] = _value;
        m_Data[4] = _value;
        m_Data[5] = _value;

        m_Data[6] = _value;
        m_Data[7] = _value;
        m_Data[8] = _value;
    }

    template<typename T>
    constexpr Matrix3x3<T> Matrix3x3<T>::Identity()
    {
        return
        {
            static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
            static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
        };
    }

    template<typename T>
    T& Matrix3x3<T>::Get(uint32_t _colom, uint32_t _row)
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template<typename T>
    const T& Matrix3x3<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template<typename T>
    T& Matrix3x3<T>::operator[](uint32_t _offset)
    {
        assert(_offset < (Size * Size), "out of bounds");

        return m_Data[_offset];
    }

    template<typename T>
    const T& Matrix3x3<T>::operator[](uint32_t _offset) const
    {
        assert(_offset < (Size * Size), "out of bounds");

        return m_Data[_offset];
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& RESTRICT _other) const
    {
        const T m00 = m_Data[0] * _other[0] + m_Data[3] * _other[1] + m_Data[6] * _other[2];
        const T m01 = m_Data[1] * _other[0] + m_Data[4] * _other[1] + m_Data[7] * _other[2];
        const T m02 = m_Data[2] * _other[0] + m_Data[5] * _other[1] + m_Data[8] * _other[2];

        const T m10 = m_Data[0] * _other[3] + m_Data[3] * _other[4] + m_Data[6] * _other[5];
        const T m11 = m_Data[1] * _other[3] + m_Data[4] * _other[4] + m_Data[7] * _other[5];
        const T m12 = m_Data[2] * _other[3] + m_Data[5] * _other[4] + m_Data[8] * _other[5];

        const T m20 = m_Data[0] * _other[6] + m_Data[3] * _other[7] + m_Data[6] * _other[8];
        const T m21 = m_Data[1] * _other[6] + m_Data[4] * _other[7] + m_Data[7] * _other[8];
        const T m22 = m_Data[2] * _other[6] + m_Data[5] * _other[7] + m_Data[8] * _other[8];

        return
        {
            m00, m01, m02,
            m10, m11, m12,
            m20, m21, m22
        };
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::operator*(const T _scalar) const
    {
         return
        {
            m_Data[0] * _scalar, m_Data[1] * _scalar, m_Data[2] * _scalar,
            m_Data[3] * _scalar, m_Data[4] * _scalar, m_Data[5] * _scalar,
            m_Data[6] * _scalar, m_Data[7] * _scalar, m_Data[8] * _scalar
        };
    }


    template<typename T>
    void Matrix3x3<T>::operator*=(const Matrix3x3& RESTRICT _other)
    {
        return (*this * _other);
    }

    template<typename T>
    bool Matrix3x3<T>::operator==(const Matrix3x3& RESTRICT _other) const
    {
        return IsEqual(m_Data[0], _other[0]) && IsEqual(m_Data[1], _other[1]) && IsEqual(m_Data[2], _other[2])
            && IsEqual(m_Data[3], _other[3]) && IsEqual(m_Data[4], _other[4]) && IsEqual(m_Data[5], _other[5])
            && IsEqual(m_Data[6], _other[6]) && IsEqual(m_Data[7], _other[7]) && IsEqual(m_Data[8], _other[8]);
    }

    template<typename T>
    bool Matrix3x3<T>::operator!=(const Matrix3x3& RESTRICT _other) const
    {
        return !(*this == _other);
    }

    template<typename T>
    void Matrix3x3<T>::Trace(T* _trace) const
    {
        _trace[0] = m_Data[0];
        _trace[1] = m_Data[4];
        _trace[2] = m_Data[8];
    }

    template<typename T>
    constexpr T Matrix3x3<T>::Determinant() const
    {
        const T m0 = m_Data[0] * Matrix2x2<T>(m_Data[4], m_Data[5], m_Data[7], m_Data[8]).Determinant();
        const T m1 = -m_Data[1] * Matrix2x2<T>(m_Data[3], m_Data[5], m_Data[6], m_Data[8]).Determinant();
        const T m2 =  m_Data[2] * Matrix2x2<T>(m_Data[3], m_Data[4], m_Data[6], m_Data[7]).Determinant();

        return m0 + m1 + m2;
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::Transpose() const
    {
        return
        {
            m_Data[0], m_Data[3], m_Data[6],
            m_Data[1], m_Data[4], m_Data[7],
            m_Data[2], m_Data[5], m_Data[8]
        };
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::AdjoinMatrix() const
    {
        using Vector2 = Vector2<T>;

        const Vector2 vec78 = Vector2(m_Data[7], m_Data[8]);
        const Vector2 vec68 = Vector2(m_Data[6], m_Data[8]);
        const Vector2 vec67 = Vector2(m_Data[6], m_Data[7]);

        const Vector2 vec01 = Vector2(m_Data[0], m_Data[1]);
        const Vector2 vec02 = Vector2(m_Data[0], m_Data[2]);
        const Vector2 vec12 = Vector2(m_Data[1], m_Data[2]);

        const Vector2 vec34 = Vector2(m_Data[3], m_Data[4]);
        const Vector2 vec45 = Vector2(m_Data[4], m_Data[5]);
        const Vector2 vec35 = Vector2(m_Data[3], m_Data[5]);


        const T m00 = Matrix2x2<T>(vec45.x, vec45.y, vec78.x, vec78.y).Determinant();
        const T m10 = Matrix2x2<T>(vec35.x, vec35.y, vec68.x, vec68.y).Determinant();
        const T m20 = Matrix2x2<T>(vec34.x, vec34.y, vec67.x, vec67.y).Determinant();

        const T m01 = Matrix2x2<T>(vec12.x, vec12.y, vec78.x, vec78.y).Determinant();
        const T m11 = Matrix2x2<T>(vec02.x, vec02.y, vec68.x, vec68.y).Determinant();
        const T m21 = Matrix2x2<T>(vec01.x, vec01.y, vec67.x, vec67.y).Determinant();


        const T m02 = Matrix2x2<T>(vec12.x, vec12.y, vec45.x, vec45.y).Determinant();
        const T m12 = Matrix2x2<T>(vec02.x, vec02.y, vec35.x, vec35.y).Determinant();
        const T m22 = Matrix2x2<T>(vec01.x, vec01.y, vec34.x, vec34.y).Determinant();

        // Transposed already
        return
        {
                m00, -m01, m02,
                -m10, m11, -m12,
                m20, -m21, m22
        }
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::Invert() const
    {
        const T det = Determinant();

        if (std::abs(det) < static_cast<T>(EPSILON))
        {
            return Identity();
        }

        const T invDet = static_cast<T>(1) / det;

        return (AdjoinMatrix()) * invDet;
    }

  

    template<typename T>
    void Matrix3x3<T>::ExtractEulerAngleXYZ(T* _xyz)

    {
        const T T1 = std::atan2(m_Data[6], m_Data[8]);
        const T C2 = std::sqrt(m_Data[0] * m_Data[0] + m_Data[3] * m_Data[3]);
        const T T2 = std::atan2(-m_Data[6], C2);
        const T S1 = std::sin(T1);
        const T C1 = std::cos(T1);
        const T T3 = std::atan2(S1 * m_Data[2] - C1 * m_Data[1], C1 * m_Data[4] - S1 * m_Data[5]);

        _xyz[0] = -T1;
        _xyz[1] = -T2;
        _xyz[2] = -T3;
    }

}