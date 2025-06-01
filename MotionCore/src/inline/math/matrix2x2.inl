
namespace Tbx
{
    template <typename T>
    CONSTEVAL Matrix2x2<T> Matrix2x2<T>::Identity()
    {
        return { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };
    }

    template <typename T>
    constexpr Matrix2x2<T>::Matrix2x2(T m00, T m10, T m01, T m11)
    {
        data[0] = m00;
        data[1] = m10;

        data[2] = m01;
        data[3] = m11;
    }

    template <typename T>
    constexpr Matrix2x2<T>::Matrix2x2(DataType _value)
    {
        data[0] = _value;
        data[1] = _value;

        data[2] = _value;
        data[3] = _value;
    }


    template <typename T>
    T& Matrix2x2<T>::Get(uint32_t _colom, uint32_t _row)
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return data[(_row * Size) + _colom];
    }

    template <typename T>
    const T& Matrix2x2<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return data[(_row * Size) + _colom];
    }

    template <typename T>
    T& Matrix2x2<T>::operator[](uint32_t _offset)
    {
        assert(_offset < (Size * Size) && "out of bounds");
        return data[_offset];
    }

    template <typename T>
    const T& Matrix2x2<T>::operator[](uint32_t _offset) const
    {
        assert(_offset < (Size * Size) && "out of bounds");
        return data[_offset];
    }

    template <typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(const Matrix2x2& RESTRICT _other)
    {
        assert(&_other != this && "other shoud not be this, for restricted keyworld");

        const T s00 = data[0], ot00 = _other[0];
        const T s10 = data[1], ot10 = _other[1];

        const T s01 = data[2], ot01 = _other[2];
        const T s11 = data[3], ot11 = _other[3];


        const T m00 = s00 * ot00 + s01 * ot10;
        const T m10 = s00 * ot01 + s01 * ot11;

        const T m01 = s10 * ot00 + s11 * ot10;
        const T m11 = s10 * ot01 + s11 * ot11;

        return { m00, m01, m10, m11 };
    }

    template <typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(DataType _value)
    {
        return 
        {   data[0] * _value,
            data[1] * _value,
            data[2] * _value,
            data[3] * _value,
        };
    }

    template <typename T>
    void Matrix2x2<T>::operator*=(DataType type)
    {
        data[0] *= type;
        data[1] *= type;
        data[2] *= type;
        data[3] *= type;
    }

    template <typename T>
    void Matrix2x2<T>::operator*=(Matrix2x2 _m2)
    {
        *this = *this * _m2;
    }

	template <typename T>
	bool Matrix2x2<T>::operator==(const  Matrix2x2<T>& _other) const
	{

		for (size_t i = 0; i < Size * Size; ++i)
		{

			if (!IsEqual(data[i], _other[i]))
			{
				return false;
			}

		}

		return true;
	}


    template <typename T>
    bool Matrix2x2<T>::operator!=(const  Matrix2x2<T>& _other) const
    {
        return !(*this == _other);
    }

    template <typename T>
    Matrix2x2<T> Matrix2x2<T>::Transpose() const
    {
        return {
            Matrix2x2(data[0], data[2], data[1], data[3])
        };
    }
 
    template <typename T>
    void Matrix2x2<T>::Trace(T* array) const
    {
        array[0] = data[0];
        array[1] = data[3];
    }

    template <typename T>
    constexpr T Matrix2x2<T>::Determinant() const
    {
        return data[0] * data[3] - data[1] * data[2];
    }


}