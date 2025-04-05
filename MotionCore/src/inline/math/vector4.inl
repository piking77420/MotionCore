
namespace Tbx
{
    template <typename T>
    constexpr Vector4<T>::Vector4(T valueX, T valueY, T valueZ, T valueW) : x(valueX), y(valueY), z(valueZ), w(valueW) {}

    template <typename T>
    constexpr T* Vector4<T>::GetPtr()
    {
        return &x;
    }

    template <typename T>
    constexpr const T* Vector4<T>::GetPtr() const
    {
        return &x;
    }

    template <typename T>
    inline T Vector4<T>::Magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::Normalize() const
    {
        const T mag = Magnitude();

        if (IsEqual<T>(mag, static_cast<T>(1)))
            return this;

        const T InvMagnitude = static_cast<T>(1) / mag;

        return { x * InvMagnitude, y * InvMagnitude, z * InvMagnitude, w * InvMagnitude };
    }

    template <typename T>
    constexpr float Vector4<T>::Dot(const Vector4& _v1, const Vector4& _v2)
    {
        return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z + _v1.w * _v2.w;
    }


    template <typename T>
    constexpr T Vector4<T>::DistanceSquare(const Vector4& _a, const Vector4& _b)
    {
        // avoid aliasing
        const DataType dx = _a.x - _b.x;
        const DataType dy = _a.y - _b.y;
        const DataType dz = _a.z - _b.z;
        const DataType dw = _a.w - _b.w;

        const DataType result = (dx * dx + dy * dy + dz * dz + dw * dw);

        return result;       
    }

    template <typename T>
    constexpr T Vector4<T>::Distance(const Vector4& _a, const Vector4& _b)
    {
        return std::sqrt(DistanceSquare(_a, _b));
    }
}
