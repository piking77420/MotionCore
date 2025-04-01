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
        assert(_offset < 4, "out of bounds");

        return m_Data[_offset];
    }

    template<typename T>
    const T& Matrix3x3<T>::operator[](uint32_t _offset) const
    {
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
            m_Data[8], m_Data[7], m_Data[6],
            m_Data[5], m_Data[4], m_Data[3],
            m_Data[2], m_Data[1], m_Data[0]
        };
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