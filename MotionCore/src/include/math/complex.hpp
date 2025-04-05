#pragma once

#include "toolbox_headerfile.hpp"

namespace Tbx 
{
    template<typename T>
    struct Complex
    {
        T real;
        T imaginary;

        constexpr Complex() = default;

        constexpr Complex(T _real, T _imaginary) : real(_real), imaginary(_imaginary) {}

        constexpr Complex(const Vector2<T>& _vec2) : real(_vec2.x), imaginary(_vec2.y) {}

        ~Complex() = default;
    };

}

