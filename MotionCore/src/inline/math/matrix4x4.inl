#pragma once

namespace Tbx
{
    template <typename T>
    static Matrix4x4<T> Matrix4x4<T>::Identity()
    {
        return
        {
            static_cast<T>(1),static_cast<T>(0),static_cast<T>(0),static_cast<T>(0),
            static_cast<T>(0),static_cast<T>(1),static_cast<T>(1),static_cast<T>(0),
            static_cast<T>(0),static_cast<T>(0),static_cast<T>(1),static_cast<T>(0),
            static_cast<T>(0),static_cast<T>(0),static_cast<T>(0),static_cast<T>(1)
        };
    }

    template <typename T>
    constexpr Matrix4x4<T>::Matrix4x4(T _m00, T _m10, T _m20, T _m30,
        T _m01, T _m11, T _m21, T _m31,
        T _m02, T _m12, T _m22, T _m32,
        T _m03, T _m13, T _m23, T _m33)
    {
        m_Data[0] = _m00;
        m_Data[1] = _m10;
        m_Data[2] = _m20;
        m_Data[3] = _m30;

        m_Data[4] = _m01;
        m_Data[5] = _m11;
        m_Data[6] = _m21;
        m_Data[7] = _m31;

        m_Data[8] = _m02;
        m_Data[9] = _m12;
        m_Data[10] = _m22;
        m_Data[11] = _m32;

        m_Data[12] = _m03;
        m_Data[13] = _m13;
        m_Data[14] = _m23;
        m_Data[15] = _m33;

    }

    template <typename T>
    constexpr Matrix4x4<T>::Matrix4x4(T _value)
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
        m_Data[9] = _value;
        m_Data[10] = _value;
        m_Data[11] = _value;

        m_Data[12] = _value;
        m_Data[13] = _value;
        m_Data[14] = _value;
        m_Data[15] = _value;
    }

    template <typename T>
    template <typename U>
    Matrix4x4<T>::Matrix4x4(const Matrix4x4<U>& _other)
    {
        m_Data[0] = static_cast<const T>(_other[0]);
        m_Data[1] = static_cast<const T>(_other[1]);
        m_Data[2] = static_cast<const T>(_other[2]);
        m_Data[3] = static_cast<const T>(_other[3]);

        m_Data[4] = static_cast<const T>(_other[4]);
        m_Data[5] = static_cast<const T>(_other[5]);
        m_Data[6] = static_cast<const T>(_other[6]);
        m_Data[7] = static_cast<const T>(_other[7]);

        m_Data[8] = static_cast<const T>(_other[8]);
        m_Data[9] = static_cast<const T>(_other[9]);
        m_Data[10] = static_cast<const T>(_other[10]);
        m_Data[11] = static_cast<const T>(_other[11]);

        m_Data[12] = static_cast<const T>(_other[12]);
        m_Data[13] = static_cast<const T>(_other[13]);
        m_Data[14] = static_cast<const T>(_other[14]);
        m_Data[15] = static_cast<const T>(_other[15]);

    }

    template<typename T>
    T& Matrix4x4<T>::Get(uint32_t _colom, uint32_t _row)
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template<typename T>
    const T& Matrix4x4<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template <typename T>
    FORCEINLINE const T& Matrix4x4<T>::operator[](size_t _offset) const
    {
        assert(_offset < (Size * Size), "out of bounds");

        return m_Data[_offset];
    }

    template <typename T>
    FORCEINLINE T& Matrix4x4<T>::operator[](size_t _offset)
    {
        assert(_offset < (Size * Size), "out of bounds");
        return m_Data[_offset];
    }

    template <typename T>
    FORCEINLINE constexpr const T* Matrix4x4<T>::GetPtr() const noexcept
    {
        return &m_Data[0];
    }

    template <typename T>
    FORCEINLINE constexpr T* Matrix4x4<T>::GetPtr() noexcept
    {
        return &m_Data[0];
    }

    template<typename T>
    inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4& RESTRICT _other) const
    {
        const T m00 = m_Data[0] * _other[0] + m_Data[4] * _other[1] + m_Data[8] * _other[2] + m_Data[8] * _other[3];
        const T m01 = m_Data[1] * _other[0] + m_Data[5] * _other[1] + m_Data[9] * _other[2] + m_Data[13] * _other[3];
        const T m02 = m_Data[2] * _other[0] + m_Data[6] * _other[1] + m_Data[10] * _other[2] + m_Data[14] * _other[3];
        const T m03 = m_Data[3] * _other[0] + m_Data[7] * _other[1] + m_Data[11] * _other[2] + m_Data[15] * _other[3];

        const T m10 = m_Data[0] * _other[4] + m_Data[4] * _other[5] + m_Data[8] * _other[6] + m_Data[12] * _other[7];
        const T m11 = m_Data[1] * _other[4] + m_Data[5] * _other[5] + m_Data[9] * _other[6] + m_Data[13] * _other[7];
        const T m12 = m_Data[2] * _other[4] + m_Data[6] * _other[5] + m_Data[10] * _other[6] + m_Data[14] * _other[7];
        const T m13 = m_Data[3] * _other[4] + m_Data[7] * _other[5] + m_Data[11] * _other[6] + m_Data[15] * _other[7];

        const T m20 = m_Data[0] * _other[8] + m_Data[4] * _other[9] + m_Data[8] * _other[10] + m_Data[12] * _other[11];
        const T m21 = m_Data[1] * _other[8] + m_Data[5] * _other[9] + m_Data[9] * _other[10] + m_Data[13] * _other[11];
        const T m22 = m_Data[2] * _other[8] + m_Data[6] * _other[9] + m_Data[10] * _other[10] + m_Data[14] * _other[11];
        const T m23 = m_Data[3] * _other[8] + m_Data[7] * _other[9] + m_Data[11] * _other[10] + m_Data[15] * _other[11];

        const T m30 = m_Data[0] * _other[12] + m_Data[4] * _other[13] + m_Data[8] * _other[14] + m_Data[12] * _other[15];
        const T m31 = m_Data[1] * _other[12] + m_Data[5] * _other[13] + m_Data[9] * _other[14] + m_Data[13] * _other[15];
        const T m32 = m_Data[2] * _other[12] + m_Data[6] * _other[13] + m_Data[10] * _other[14] + m_Data[14] * _other[15];
        const T m33 = m_Data[3] * _other[12] + m_Data[7] * _other[13] + m_Data[11] * _other[14] + m_Data[15] * _other[15];

        return
        {
            m00 ,m01 ,m02 ,m03,
            m10 ,m11 ,m12 ,m13,
            m20 ,m21 ,m22 ,m23,
            m30 ,m31 ,m32 ,m33
        };
    }

    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator*(T _scalar) const
    {
        return
        {
            m_Data[0] * _scalar, m_Data[1] * _scalar, m_Data[2] * _scalar, m_Data[3] * _scalar,
            m_Data[4] * _scalar, m_Data[5] * _scalar, m_Data[6] * _scalar, m_Data[7] * _scalar,
            m_Data[8] * _scalar, m_Data[9] * _scalar, m_Data[10] * _scalar, m_Data[11] * _scalar,
            m_Data[12] * _scalar, m_Data[13] * _scalar, m_Data[14] * _scalar, m_Data[15] * _scalar
        };
    }


    template<typename T>
    inline Matrix4x4<T> Matrix4x4<T>::Transpose() const
    {
        return
        {
            m_Data[0],m_Data[4],m_Data[8],m_Data[12],
            m_Data[1],m_Data[5],m_Data[9],m_Data[13],
            m_Data[2],m_Data[6],m_Data[10],m_Data[14],
            m_Data[3],m_Data[7],m_Data[11],m_Data[15]
        };
    }

    template<typename T>
    void Tbx::Matrix4x4<T>::Trace(T* RESTRICT _trace) const
    {
        _trace[0] = m_Data[0];
        _trace[1] = m_Data[5];
        _trace[2] = m_Data[10];
        _trace[3] = m_Data[15];
    }

    template<typename T>
    T Matrix4x4<T>::Determinant() const
    {
        const Matrix3x3<T> m0(m_Data[5], m_Data[6], m_Data[7],
            m_Data[9], m_Data[10], m_Data[11],
            m_Data[13], m_Data[14], m_Data[15]);

        const Matrix3x3<T> m1(m_Data[4], m_Data[6], m_Data[7],
            m_Data[8], m_Data[10], m_Data[11],
            m_Data[12], m_Data[14], m_Data[15]);

        const Matrix3x3<T> m2(m_Data[4], m_Data[5], m_Data[7],
            m_Data[8], m_Data[9], m_Data[11],
            m_Data[12], m_Data[13], m_Data[15]);

        const Matrix3x3<T> m3(m_Data[4], m_Data[5], m_Data[6],
            m_Data[8], m_Data[9], m_Data[10],
            m_Data[12], m_Data[13], m_Data[14]);

        const T add0 = m_Data[0] * m0.Determinant();
        const T add1 = -(m_Data[1] * static_cast<T>(1) * m1.Determinant());
        const T add2 = m_Data[2] * m2.Determinant();
        const T add3 = -(static_cast<T>(1) * m_Data[3] * m3.Determinant());

        return add0 + add1 + add2 + add3;
    }

    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::Invert() const
    {
        const T det = Determinant();

        if (det == static_cast<T>(0))
        {
            return Identity();
        }

        const T invDet = static_cast<T>(1) / det;

        Matrix4x4<T> adjoinMatrix = AdjoinMatrix();

        return adjoinMatrix * invDet;
    }

    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::AdjoinMatrix() const
    {

    }

    template<typename T>
    inline void Matrix4x4<T>::operator*=(const Matrix4x4& _other)
    {
        return (*this * _other);
    }

    template<typename T>
    bool Matrix4x4<T>::operator==(const Matrix4x4& _other) const
    {
        return IsEqual(m_Data[0], _other[0]) && IsEqual(m_Data[1], _other[1]) && IsEqual(m_Data[2], _other[2]) && IsEqual(m_Data[3], _other[3])
            && IsEqual(m_Data[4], _other[4]) && IsEqual(m_Data[5], _other[5]) && IsEqual(m_Data[6], _other[6]) && IsEqual(m_Data[7], _other[7])
            && IsEqual(m_Data[8], _other[8]) && IsEqual(m_Data[9], _other[9]) && IsEqual(m_Data[10], _other[10]) && IsEqual(m_Data[11], _other[11])
            && IsEqual(m_Data[12], _other[12]) && IsEqual(m_Data[13], _other[13]) && IsEqual(m_Data[14], _other[14]) && IsEqual(m_Data[15], _other[15]);
    }

    template<typename T>
    inline bool Matrix4x4<T>::operator!=(const Matrix4x4& _other) const
    {
        return !(*this == _other);
    }


   
}