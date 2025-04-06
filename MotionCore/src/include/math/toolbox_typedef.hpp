
#pragma once

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"


#include "matrix2x2.hpp"
#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

#include "quaternion.hpp"

#include "matrix_transformation.hpp"

namespace Tbx
{
    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector2ui = Vector2<unsigned int>;
    using Vector2d = Vector2<double>;
    using Vector2ld = Vector2<long double>;

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
    using Vector3d = Vector3<double>;
    using Vector3ld = Vector3<long double>;

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
    using Vector4d = Vector4<double>;
    using Vector4ld = Vector4<long double>;

    using Matrix2x2f = Matrix2x2<float>;
    using Matrix2x2i = Matrix2x2<int>;
    using Matrix2x2d = Matrix2x2<double>;
    using Matrix2x2ld = Matrix2x2<long double>;

    using Matrix3x3f = Matrix3x3<float>;
    using Matrix3x3i = Matrix3x3<int>;
    using Matrix3x3d = Matrix3x3<double>;
    using Matrix3x3ld = Matrix3x3<long double>;

    using Matrix4x4f = Matrix4x4<float>;
    using Matrix4x4i = Matrix4x4<int>;
    using Matrix4x4d = Matrix4x4<double>;
    using Matrix4x4ld = Matrix4x4<long double>;

    using Quaternionf = Quaternion<float>;
    using Quaternioni = Quaternion<int>;
    using Quaterniond = Quaternion<double>;
    using Quaternionld = Quaternion<long double>;
}


#include <iostream>

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, Tbx::Vector2<T> vec)
{
    ostream << "x : " << vec.x << ", " << "y : " << vec.y << '\n';

    return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, Tbx::Vector3<T> vec)
{
    ostream << "x : " << vec.x << ", " << "y : " << vec.y << ", " << "z : " << vec.z << '\n';

    return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, Tbx::Vector4<T> vec)
{
    ostream << "x : " << vec.x << ", " << "y : " << vec.y << ", " << "z : " << vec.z << ", " << "w : " << vec.w << '\n';

    return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, const Tbx::Matrix2x2<T>& matrix)
{
   ostream << "m00 : " << matrix[0] << "m10 : " << matrix[2] << '\n';
   ostream << "m01 : " << matrix[1] << "m11 : " << matrix[3] << '\n';

   return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, const Tbx::Matrix3x3<T>& matrix)
{
    ostream << "m00 : " << matrix[0] << " m01 : " << matrix[3] << " m02 : " << matrix[6] << '\n';
    ostream << "m10 : " << matrix[1] << " m11 : " << matrix[4] << " m12 : " << matrix[7] << '\n';
    ostream << "m20 : " << matrix[2] << " m21 : " << matrix[5] << " m22 : " << matrix[8] << '\n';

    return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, const Tbx::Matrix4x4<T>& matrix)
{
    ostream << "m00 : " << matrix[0] << " m01 : " << matrix[4] << " m02 : " << matrix[8] << " m03 : " << matrix[12] << '\n';
    ostream << "m10 : " << matrix[1] << " m11 : " << matrix[5] << " m12 : " << matrix[9] << " m13 : " << matrix[13] << '\n';
    ostream << "m20 : " << matrix[2] << " m21 : " << matrix[6] << " m22 : " << matrix[10] << " m23 : " << matrix[14] << '\n';
    ostream << "m30 : " << matrix[3] << " m31 : " << matrix[7] << " m32 : " << matrix[11] << " m33 : " << matrix[15] << '\n';

    return ostream;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& ostream, const Tbx::Quaternion<T>& q)
{
    ostream << q.imaginary.x << " w : " << q.real << '\n';

    return ostream;
}


// C++20 (and later) code
#if __cplusplus >= 202002L

#include <format>

template <typename T>
struct std::formatter<Tbx::Vector2<T>> : std::formatter<std::string> 
{
    // Parse format specifiers (if any)
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        // For simplicity, we don't handle custom format specifiers here
        return ctx.begin();
    }

    auto format(const Tbx::Vector2<T>& v, std::format_context& ctx) const -> std::format_context::iterator {
        // Create a string representation of vec2
        const std::string s = "x : " + std::to_string(v.x) + ", " + "y : " + std::to_string(v.y);
        // Delegate formatting to the standard string formatter
        return std::formatter<std::string>::format(s, ctx);
    }
};

template <typename T>
struct std::formatter<Tbx::Vector3<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Vector3<T>& v, std::format_context& ctx) const -> std::format_context::iterator {
        const std::string s = "x : " + std::to_string(v.x) + ", " + "y : " + std::to_string(v.y) + ", " + "z : " + std::to_string(v.z);
        return std::formatter<std::string>::format(s, ctx);
    }
};

template <typename T>
struct std::formatter<Tbx::Vector4<T>> : std::formatter<std::string> 
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Vector4<T>& v, std::format_context& ctx) const -> std::format_context::iterator {
        const std::string s = "x : " + std::to_string(v.x) + ", " + "y : " + std::to_string(v.y) + ", " + "z : " + std::to_string(v.z) + ", " + "w : " + std::to_string(v.w);
        return std::formatter<std::string>::format(s, ctx);
    }
};

template <typename T>
struct std::formatter<Tbx::Matrix2x2<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Matrix2x2<T>& matrix, std::format_context& ctx) const -> std::format_context::iterator {

        const std::string s = "\nm00 : " + std::to_string(matrix[0]) + "m10 : " + std::to_string(matrix[2]) + '\n'
                      + "m01 : " + std::to_string(matrix[1]) + "m11 : " + std::to_string(matrix[3]) + '\n';

        // Delegate formatting to the standard string formatter
        return std::formatter<std::string>::format(s, ctx);
    }
};


template <typename T>
struct std::formatter<Tbx::Matrix3x3<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Matrix3x3<T>& matrix, std::format_context& ctx) const -> std::format_context::iterator {

        const std::string s =   "\nm00 : " + std::to_string(matrix[0]) + " m01 : " + std::to_string(matrix[3]) + " m02 : " + std::to_string(matrix[6]) + '\n'
                        + "m10 : " + std::to_string(matrix[1]) + " m11 : " + std::to_string(matrix[4]) + " m12 : " + std::to_string(matrix[7]) + '\n'
                        + "m20 : " + std::to_string(matrix[2]) + " m21 : " + std::to_string(matrix[5]) + " m22 : " + std::to_string(matrix[8]) << '\n';

        // Delegate formatting to the standard string formatter
        return std::formatter<std::string>::format(s, ctx);
    }
};

template <typename T>
struct std::formatter<Tbx::Matrix4x4<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Matrix4x4<T>& matrix, std::format_context& ctx) const -> std::format_context::iterator {

        const std::string s =  "\nm00 : " +  std::to_string(matrix[0]) + " m01 : " + std::to_string(matrix[4]) + " m02 : " + std::to_string(matrix[8]) + " m03 : " + std::to_string(matrix[12]) + '\n'
                       + "m10 : " + std::to_string(matrix[1]) + " m11 : " + std::to_string(matrix[5]) + " m12 : " + std::to_string(matrix[9]) + " m13 : " + std::to_string(matrix[13]) + '\n'
                       + "m20 : " + std::to_string(matrix[2]) + " m21 : " + std::to_string(matrix[6]) + " m22 : " + std::to_string(matrix[10]) + " m23 : " + std::to_string(matrix[14]) + '\n'
                       + "m30 : " + std::to_string(matrix[3]) + " m31 : " + std::to_string(matrix[7]) + " m32 : " + std::to_string(matrix[11]) + " m33 : " + std::to_string(matrix[15]) + '\n';

        // Delegate formatting to the standard string formatter
        return std::formatter<std::string>::format(s, ctx);
    }
};

template <typename T>
struct std::formatter<Tbx::Quaternion<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(const Tbx::Quaternion<T>& q, std::format_context& ctx) const -> std::format_context::iterator {

        const std::string s = "x : " + std::to_string(q.imaginary.x) + ", " + "y : " + std::to_string(q.imaginary.y) + ", " + "z : " + std::to_string(q.imaginary.z) + ", " + "w : " + std::to_string(q.real);
        // Delegate formatting to the standard string formatter
        return std::formatter<std::string>::format(s, ctx);
    }
};


#endif