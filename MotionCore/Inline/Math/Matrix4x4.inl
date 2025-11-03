


namespace Tbx
{
    template <typename T>
    CONSTEVAL Matrix4x4<T> Matrix4x4<T>::Identity()
    {
        return
        {
            static_cast<T>(1),static_cast<T>(0),static_cast<T>(0),static_cast<T>(0),
            static_cast<T>(0),static_cast<T>(1),static_cast<T>(0),static_cast<T>(0),
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
        data[0] = _m00;
        data[1] = _m10;
        data[2] = _m20;
        data[3] = _m30;

        data[4] = _m01;
        data[5] = _m11;
        data[6] = _m21;
        data[7] = _m31;

        data[8] = _m02;
        data[9] = _m12;
        data[10] = _m22;
        data[11] = _m32;

        data[12] = _m03;
        data[13] = _m13;
        data[14] = _m23;
        data[15] = _m33;

    }

    template <typename T>
    constexpr Matrix4x4<T>::Matrix4x4(T _value)
    {
        data[0] = _value;
        data[1] = _value;
        data[2] = _value;
        data[3] = _value;

        data[4] = _value;
        data[5] = _value;
        data[6] = _value;
        data[7] = _value;

        data[8] = _value;
        data[9] = _value;
        data[10] = _value;
        data[11] = _value;

        data[12] = _value;
        data[13] = _value;
        data[14] = _value;
        data[15] = _value;
    }

    template <typename T>
    template <typename U>
    Matrix4x4<T>::Matrix4x4(const Matrix4x4<U>& _other)
    {
        data[0] = static_cast<const T>(_other[0]);
        data[1] = static_cast<const T>(_other[1]);
        data[2] = static_cast<const T>(_other[2]);
        data[3] = static_cast<const T>(_other[3]);

        data[4] = static_cast<const T>(_other[4]);
        data[5] = static_cast<const T>(_other[5]);
        data[6] = static_cast<const T>(_other[6]);
        data[7] = static_cast<const T>(_other[7]);

        data[8] = static_cast<const T>(_other[8]);
        data[9] = static_cast<const T>(_other[9]);
        data[10] = static_cast<const T>(_other[10]);
        data[11] = static_cast<const T>(_other[11]);

        data[12] = static_cast<const T>(_other[12]);
        data[13] = static_cast<const T>(_other[13]);
        data[14] = static_cast<const T>(_other[14]);
        data[15] = static_cast<const T>(_other[15]);

    }

    template<typename T>
    T& Matrix4x4<T>::Get(uint32_t _colom, uint32_t _row)
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return data[(_row * Size) + _colom];
    }

    template<typename T>
    const T& Matrix4x4<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return data[(_row * Size) + _colom];
    }

    template <typename T>
    FORCEINLINE const T& Matrix4x4<T>::operator[](size_t _offset) const
    {
        assert(_offset < (Size * Size) && "out of bounds");

        return data[_offset];
    }

    template <typename T>
    FORCEINLINE T& Matrix4x4<T>::operator[](size_t _offset)
    {
        assert(_offset < (Size * Size) && "out of bounds");
        return data[_offset];
    }

    template <typename T>
    FORCEINLINE constexpr const T* Matrix4x4<T>::GetPtr() const noexcept
    {
        return &data[0];
    }

    template <typename T>
    FORCEINLINE constexpr T* Matrix4x4<T>::GetPtr() noexcept
    {
        return &data[0];
    }

    template<typename T>
    inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4& RESTRICT _other) const
    {
        const T m00 = data[0] * _other[0] + data[4] * _other[1] + data[8] * _other[2] + data[8] * _other[3];
        const T m01 = data[1] * _other[0] + data[5] * _other[1] + data[9] * _other[2] + data[13] * _other[3];
        const T m02 = data[2] * _other[0] + data[6] * _other[1] + data[10] * _other[2] + data[14] * _other[3];
        const T m03 = data[3] * _other[0] + data[7] * _other[1] + data[11] * _other[2] + data[15] * _other[3];

        const T m10 = data[0] * _other[4] + data[4] * _other[5] + data[8] * _other[6] + data[12] * _other[7];
        const T m11 = data[1] * _other[4] + data[5] * _other[5] + data[9] * _other[6] + data[13] * _other[7];
        const T m12 = data[2] * _other[4] + data[6] * _other[5] + data[10] * _other[6] + data[14] * _other[7];
        const T m13 = data[3] * _other[4] + data[7] * _other[5] + data[11] * _other[6] + data[15] * _other[7];

        const T m20 = data[0] * _other[8] + data[4] * _other[9] + data[8] * _other[10] + data[12] * _other[11];
        const T m21 = data[1] * _other[8] + data[5] * _other[9] + data[9] * _other[10] + data[13] * _other[11];
        const T m22 = data[2] * _other[8] + data[6] * _other[9] + data[10] * _other[10] + data[14] * _other[11];
        const T m23 = data[3] * _other[8] + data[7] * _other[9] + data[11] * _other[10] + data[15] * _other[11];

        const T m30 = data[0] * _other[12] + data[4] * _other[13] + data[8] * _other[14] + data[12] * _other[15];
        const T m31 = data[1] * _other[12] + data[5] * _other[13] + data[9] * _other[14] + data[13] * _other[15];
        const T m32 = data[2] * _other[12] + data[6] * _other[13] + data[10] * _other[14] + data[14] * _other[15];
        const T m33 = data[3] * _other[12] + data[7] * _other[13] + data[11] * _other[14] + data[15] * _other[15];

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
            data[0] * _scalar, data[1] * _scalar, data[2] * _scalar, data[3] * _scalar,
            data[4] * _scalar, data[5] * _scalar, data[6] * _scalar, data[7] * _scalar,
            data[8] * _scalar, data[9] * _scalar, data[10] * _scalar, data[11] * _scalar,
            data[12] * _scalar, data[13] * _scalar, data[14] * _scalar, data[15] * _scalar
        };
    }


    template<typename T>
    inline Matrix4x4<T> Matrix4x4<T>::Transpose() const
    {
        return
        {
            data[0],data[4],data[8],data[12],
            data[1],data[5],data[9],data[13],
            data[2],data[6],data[10],data[14],
            data[3],data[7],data[11],data[15]
        };
    }

    template<typename T>
    void Tbx::Matrix4x4<T>::Trace(T* RESTRICT _trace) const
    {
        _trace[0] = data[0];
        _trace[1] = data[5];
        _trace[2] = data[10];
        _trace[3] = data[15];
    }

    template<typename T>
    T Matrix4x4<T>::Determinant() const
    {
        const Matrix3x3<T> m0(data[5], data[6], data[7],
            data[9], data[10], data[11],
            data[13], data[14], data[15]);

        const Matrix3x3<T> m1(data[4], data[6], data[7],
            data[8], data[10], data[11],
            data[12], data[14], data[15]);

        const Matrix3x3<T> m2(data[4], data[5], data[7],
            data[8], data[9], data[11],
            data[12], data[13], data[15]);

        const Matrix3x3<T> m3(data[4], data[5], data[6],
            data[8], data[9], data[10],
            data[12], data[13], data[14]);

        const T add0 = data[0] * m0.Determinant();
        const T add1 = -(data[1] * static_cast<T>(1) * m1.Determinant());
        const T add2 = data[2] * m2.Determinant();
        const T add3 = -(static_cast<T>(1) * data[3] * m3.Determinant());

        return add0 + add1 + add2 + add3;
    }


    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::AdjoinMatrix() const
    {
        using Vector3 = Vector3<T>;

        const Vector3 vec1_2_3(data[1], data[2], data[3]);
        const Vector3 vec0_2_3(data[0], data[2], data[3]);
        const Vector3 vec0_1_3(data[0], data[1], data[3]);
        const Vector3 vec0_1_2(data[0], data[1], data[2]);

        const Vector3 vec5_6_7(data[5], data[6], data[7]);
        const Vector3 vec4_6_7(data[4], data[6], data[7]);
        const Vector3 vec4_5_7(data[4], data[5], data[7]);
        const Vector3 vec4_5_6(data[4], data[5], data[6]);

        const Vector3 vec9_10_11(data[9], data[10], data[11]);
        const Vector3 vec8_10_11(data[8], data[10], data[11]);
        const Vector3 vec8_9_11(data[8], data[9], data[11]);
        const Vector3 vec8_9_10(data[8], data[9], data[10]);

        const Vector3 vec13_14_15(data[13], data[14], data[15]);
        const Vector3 vec12_14_15(data[12], data[14], data[15]);
        const Vector3 vec12_13_15(data[12], data[13], data[15]);
        const Vector3 vec12_13_14(data[12], data[13], data[14]);

        const T m00 = Matrix3x3<T>(vec5_6_7, vec9_10_11, vec13_14_15).Determinant();
        const T m10 = Matrix3x3<T>(vec4_6_7, vec8_10_11, vec12_14_15).Determinant();
        const T m20 = Matrix3x3<T>(vec4_5_7, vec8_9_11, vec12_13_15).Determinant();
        const T m30 = Matrix3x3<T>(vec4_5_6, vec8_9_10, vec12_13_14).Determinant();

        const T m01 = Matrix3x3<T>(vec1_2_3, vec9_10_11, vec13_14_15).Determinant();
        const T m11 = Matrix3x3<T>(vec0_2_3, vec8_10_11, vec12_14_15).Determinant();
        const T m21 = Matrix3x3<T>(vec0_1_3, vec8_9_11, vec12_13_15).Determinant();
        const T m31 = Matrix3x3<T>(vec0_1_2, vec8_9_10, vec12_13_14).Determinant();

        const T m02 = Matrix3x3<T>(vec1_2_3, vec5_6_7, vec13_14_15).Determinant();
        const T m12 = Matrix3x3<T>(vec0_2_3, vec4_6_7, vec12_14_15).Determinant();
        const T m22 = Matrix3x3<T>(vec0_1_3, vec4_5_7, vec12_13_15).Determinant();
        const T m32 = Matrix3x3<T>(vec0_1_2, vec4_5_6, vec12_13_14).Determinant();

        const T m03 = Matrix3x3<T>(vec1_2_3, vec5_6_7, vec9_10_11).Determinant();
        const T m13 = Matrix3x3<T>(vec0_2_3, vec4_6_7, vec8_10_11).Determinant();
        const T m23 = Matrix3x3<T>(vec0_1_3, vec4_5_7, vec8_9_11).Determinant();
        const T m33 = Matrix3x3<T>(vec0_1_2, vec4_5_6, vec8_9_10).Determinant();

        return Matrix4x4<T>(
            m00, -m01, m02, -m03,
            -m10, m11, -m12, m13,
            m20, -m21, m22, -m23,
            -m30, m31, -m32, m33
        );
    }

    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::Invert() const
    {
        const T det = Determinant();
        if (IsEqual(det, static_cast<T>(0)))
        {
            return Identity();
        }

        const T invDet = static_cast<T>(1) / det;
        return AdjoinMatrix() * invDet;
    }


    template<typename T>
    inline void Matrix4x4<T>::operator*=(const Matrix4x4& _other)
    {
        return (*this * _other);
    }

    template<typename T>
    bool Matrix4x4<T>::operator==(const Matrix4x4& _other) const
    {
        return IsEqual(data[0], _other[0]) && IsEqual(data[1], _other[1]) && IsEqual(data[2], _other[2]) && IsEqual(data[3], _other[3])
            && IsEqual(data[4], _other[4]) && IsEqual(data[5], _other[5]) && IsEqual(data[6], _other[6]) && IsEqual(data[7], _other[7])
            && IsEqual(data[8], _other[8]) && IsEqual(data[9], _other[9]) && IsEqual(data[10], _other[10]) && IsEqual(data[11], _other[11])
            && IsEqual(data[12], _other[12]) && IsEqual(data[13], _other[13]) && IsEqual(data[14], _other[14]) && IsEqual(data[15], _other[15]);
    }

    template<typename T>
    inline bool Matrix4x4<T>::operator!=(const Matrix4x4& _other) const
    {
        return !(*this == _other);
    }


   
}