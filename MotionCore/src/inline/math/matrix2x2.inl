#pragma once

namespace Tbx
{
    template <typename T>
    constexpr Matrix2x2<T> Matrix2x2<T>::Identity()
    {
        return { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };
    }

    template <typename T>
    constexpr Matrix2x2<T>::Matrix2x2(T m00, T m10, T m01, T m11)
    {
        m_Data[0] = m00;
        m_Data[1] = m10;

        m_Data[2] = m01;
        m_Data[3] = m11;
    }

    template <typename T>
    constexpr Matrix2x2<T>::Matrix2x2(DataType _value)
    {
        m_Data[0] = _value;
        m_Data[1] = _value;

        m_Data[2] = _value;
        m_Data[3] = _value;
    }


    template <typename T>
    T& Matrix2x2<T>::Get(uint32_t _colom, uint32_t _row)
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template <typename T>
    const T& Matrix2x2<T>::Get(uint32_t _colom, uint32_t _row) const
    {
        assert(_colom < Size && _row < Size && "out of bounds");

        return m_Data[(_row * Size) + _colom];
    }

    template <typename T>
    T& Matrix2x2<T>::operator[](uint32_t _offset)
    {
        assert(_offset < (Size * Size), "out of bounds");
        return m_Data[_offset];
    }

    template <typename T>
    const T& Matrix2x2<T>::operator[](uint32_t _offset) const
    {
        assert(_offset < (Size * Size), "out of bounds");
        return m_Data[_offset];
    }

    template <typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(const Matrix2x2& RESTRICT _other)
    {
        assert(&_other != this && "other shoud not be this, for restricted keyworld");

        const T m00 = m_Data[0] * _other[0] + m_Data[2] * _other[1];
        const T m10 = m_Data[0] * _other[2] + m_Data[2] * _other[3];

        const T m01 = m_Data[1] * _other[0] + m_Data[3] * _other[1];
        const T m11 = m_Data[1] * _other[2] + m_Data[3] * _other[3];

        return { m00, m01, m10, m11 };
    }

    template <typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(DataType _value)
    {
        return 
        {   m_Data[0] * _value,
            m_Data[1] * _value,
            m_Data[2] * _value,
            m_Data[3] * _value,
        };
    }

    template <typename T>
    void Matrix2x2<T>::operator*=(DataType type)
    {
        m_Data[0] *= type;
        m_Data[1] *= type;
        m_Data[2] *= type;
        m_Data[3] *= type;
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

			if (!IsEqual(m_Data[i], _other[i]))
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
            Matrix2x2(m_Data[3], m_Data[2], m_Data[1], m_Data[0])
        };
    }
 
    template <typename T>
    void Matrix2x2<T>::Trace(T* array) const
    {
        array[0] = m_Data[0];
        array[1] = m_Data[3];
    }

    template <typename T>
    constexpr T Matrix2x2<T>::Determinant() const
    {
        return m_Data[0] * m_Data[3] - m_Data[1] * m_Data[2];
    }


}