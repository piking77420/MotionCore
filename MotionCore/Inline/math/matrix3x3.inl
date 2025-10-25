

namespace Tbx
{
    template<typename T>
    constexpr Matrix3x3<T>::Matrix3x3(T m00, T m10, T m20,
        T m01, T m11, T m21,
        T m02, T m12, T m22)
    {
        data[0] = m00;
        data[1] = m10;
        data[2] = m20;

        data[3] = m01;
        data[4] = m11;
        data[5] = m21;

        data[6] = m02;
        data[7] = m12;
        data[8] = m22;
    }

    template<typename T>
    inline constexpr Matrix3x3<T>::Matrix3x3(const Vector3<T>& _vec1, const Vector3<T>& _vec2, const Vector3<T>& _vec3)
    {
        data[0] = _vec1.x;
        data[1] = _vec1.y;
        data[2] = _vec1.z;

        data[3] = _vec2.x;
        data[4] = _vec2.y;
        data[5] = _vec2.z;

        data[6] = _vec3.x;
        data[7] = _vec3.y;
        data[8] = _vec3.z;
    }

    template<typename T>
    constexpr Matrix3x3<T>::Matrix3x3(T _value)
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
    }

    template<typename T>
    CONSTEVAL Matrix3x3<T> Matrix3x3<T>::Identity()
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

        return data[(_row * Size) + _colom];
    }

    template<typename T>
    const T& Matrix3x3<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return data[(_row * Size) + _colom];
    }

    template<typename T>
    T& Matrix3x3<T>::operator[](uint32_t _offset)
    {
        assert(_offset < (Size * Size) && "out of bounds");

        return data[_offset];
    }

    template<typename T>
    const T& Matrix3x3<T>::operator[](uint32_t _offset) const
    {
        assert(_offset < (Size * Size) && "out of bounds");

        return data[_offset];
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& RESTRICT _other) const
    {
        const T m00 = data[0] * _other[0] + data[3] * _other[1] + data[6] * _other[2];
        const T m01 = data[1] * _other[0] + data[4] * _other[1] + data[7] * _other[2];
        const T m02 = data[2] * _other[0] + data[5] * _other[1] + data[8] * _other[2];

        const T m10 = data[0] * _other[3] + data[3] * _other[4] + data[6] * _other[5];
        const T m11 = data[1] * _other[3] + data[4] * _other[4] + data[7] * _other[5];
        const T m12 = data[2] * _other[3] + data[5] * _other[4] + data[8] * _other[5];

        const T m20 = data[0] * _other[6] + data[3] * _other[7] + data[6] * _other[8];
        const T m21 = data[1] * _other[6] + data[4] * _other[7] + data[7] * _other[8];
        const T m22 = data[2] * _other[6] + data[5] * _other[7] + data[8] * _other[8];

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
            data[0] * _scalar, data[1] * _scalar, data[2] * _scalar,
            data[3] * _scalar, data[4] * _scalar, data[5] * _scalar,
            data[6] * _scalar, data[7] * _scalar, data[8] * _scalar
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
        return IsEqual(data[0], _other[0]) && IsEqual(data[1], _other[1]) && IsEqual(data[2], _other[2])
            && IsEqual(data[3], _other[3]) && IsEqual(data[4], _other[4]) && IsEqual(data[5], _other[5])
            && IsEqual(data[6], _other[6]) && IsEqual(data[7], _other[7]) && IsEqual(data[8], _other[8]);
    }

    template<typename T>
    bool Matrix3x3<T>::operator!=(const Matrix3x3& RESTRICT _other) const
    {
        return !(*this == _other);
    }

    template<typename T>
    void Matrix3x3<T>::Trace(T* _trace) const
    {
        _trace[0] = data[0];
        _trace[1] = data[4];
        _trace[2] = data[8];
    }

    template<typename T>
    constexpr T Matrix3x3<T>::Determinant() const
    {
        const T m0 = data[0] * Matrix2x2<T>(data[4], data[5], data[7], data[8]).Determinant();
        const T m1 = -data[1] * Matrix2x2<T>(data[3], data[5], data[6], data[8]).Determinant();
        const T m2 =  data[2] * Matrix2x2<T>(data[3], data[4], data[6], data[7]).Determinant();

        return m0 + m1 + m2;
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::Transpose() const
    {
        return
        {
            data[0], data[3], data[6],
            data[1], data[4], data[7],
            data[2], data[5], data[8]
        };
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::AdjoinMatrix() const
    {
        using Vector2 = Vector2<T>;

        const Vector2 vec78 = Vector2(data[7], data[8]);
        const Vector2 vec68 = Vector2(data[6], data[8]);
        const Vector2 vec67 = Vector2(data[6], data[7]);

        const Vector2 vec01 = Vector2(data[0], data[1]);
        const Vector2 vec02 = Vector2(data[0], data[2]);
        const Vector2 vec12 = Vector2(data[1], data[2]);

        const Vector2 vec34 = Vector2(data[3], data[4]);
        const Vector2 vec45 = Vector2(data[4], data[5]);
        const Vector2 vec35 = Vector2(data[3], data[5]);


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
        };
    }

    template<typename T>
    Matrix3x3<T> Matrix3x3<T>::Invert() const
    {
        const T det = Determinant();

        if (std::abs(det) < static_cast<T>(Epsilon<T>()))
        {
            return Identity();
        }

        const T invDet = static_cast<T>(1) / det;

        return (AdjoinMatrix()) * invDet;
    }

  

    template<typename T>
    void Matrix3x3<T>::ExtractEulerAngleXYZ(T* _xyz)

    {
        const T T1 = std::atan2(data[6], data[8]);
        const T C2 = std::sqrt(data[0] * data[0] + data[3] * data[3]);
        const T T2 = std::atan2(-data[6], C2);
        const T S1 = std::sin(T1);
        const T C1 = std::cos(T1);
        const T T3 = std::atan2(S1 * data[2] - C1 * data[1], C1 * data[4] - S1 * data[5]);

        _xyz[0] = -T1;
        _xyz[1] = -T2;
        _xyz[2] = -T3;
    }

}