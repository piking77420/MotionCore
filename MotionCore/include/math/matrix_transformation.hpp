﻿#pragma once

#include "toolbox_typedef.hpp"

namespace Tbx
{
    template <typename D, typename F, typename T>
    void MatrixCast(const F& _from, T* _to)
    {
        static_assert(std::is_same_v<T, Matrix3x3<D>> ||
                      std::is_same_v<T, Matrix2x2<D>> || std::is_same_v<T, Matrix4x4<D>>, "T is not a Matrix");

        static_assert(std::is_same_v<F, Matrix3x3<D>> ||
                      std::is_same_v<F, Matrix2x2<D>> || std::is_same_v<F, Matrix4x4<D>>, "F is not a Matrix");

        static_assert(!std::is_same_v<F, T>, "T and F are the same type");

        constexpr size_t size = std::min(F::Size, T::Size);

        for (int i = 0; i < size; i++)
        {
            for (int k = 0; k < size; k++)
            {
                (*_to)[i][k] = _from[i][k];
            }
        }
    }


    template <class T>
    void RotationMatrix(float _angle, Matrix2x2<T>* _matrix)
    {
        (*_matrix)[0][0] = std::cos(_angle);
        (*_matrix)[0][1] = std::sin(_angle);

        (*_matrix)[1][0] = -std::sin(_angle);
        (*_matrix)[1][1] = std::cos(_angle);
    }

    template <class T>
    void RotationMatrix2D(float _angle, Matrix3x3<T>* _matrix)
    {
        (*_matrix)[0][0] = std::cos(_angle);
        (*_matrix)[1][0] = -std::sin(_angle);
        (*_matrix)[2][0] = 0.f;
        (*_matrix)[0][1] = std::sin(_angle);
        (*_matrix)[1][1] = std::cos(_angle);
        (*_matrix)[2][1] = 0.f;
        (*_matrix)[0][2] = 0.f;
        (*_matrix)[1][2] = 0.f;
        (*_matrix)[2][2] = 1.f;
    }


    template <class T>
    void RotationXMatrix3D(float _angleX, Matrix3x3<T>* _matrix)
    {
        (*_matrix)[0].x = static_cast<T>(1);
        (*_matrix)[0].y = 0;
        (*_matrix)[0].z = 0;

        (*_matrix)[1].x = 0;
        (*_matrix)[1].y = std::cos(_angleX);
        (*_matrix)[1].z = std::sin(_angleX);

        (*_matrix)[2].x = 0;
        (*_matrix)[2].y = -std::sin(_angleX);
        (*_matrix)[2].z = std::cos(_angleX);
    }

    template <class T>
    void RotationYMatrix3D(float _angleY, Matrix3x3<T>* _matrix)
    {
        (*_matrix)[0].x = std::cos(_angleY);
        (*_matrix)[0].y = 0;
        (*_matrix)[0].z = -std::sin(_angleY);

        (*_matrix)[1].x = 0;
        (*_matrix)[1].y = static_cast<T>(1);
        (*_matrix)[1].z = 0;

        (*_matrix)[2].x = std::sin(_angleY);
        (*_matrix)[2].y = 0;
        (*_matrix)[2].z = std::cos(_angleY);
    }

    template <class T>
    void RotationZMatrix3D(float _angleZ, Matrix3x3<T>* _matrix)
    {
        (*_matrix)[0].x = std::cos(_angleZ);
        (*_matrix)[0].y = std::sin(_angleZ);
        (*_matrix)[0].z = 0;

        (*_matrix)[1].x = -std::sin(_angleZ);
        (*_matrix)[1].y = std::cos(_angleZ);
        (*_matrix)[1].z = 0;

        (*_matrix)[2].x = 0;
        (*_matrix)[2].y = 0;
        (*_matrix)[2].z = static_cast<T>(1);
    }

    template <class T>
    void RotationMatrix3D(float _angleX, float _angleY, float _angleZ, Matrix3x3<T>* matrix)
    {
        Matrix3x3<T> x, y, z;
        RotationXMatrix3D(_angleX, &x);
        RotationYMatrix3D(_angleY, &y);
        RotationZMatrix3D(_angleZ, &z);


        *matrix = x * y * z;
    }

    template <class T>
    void RotationMatrix3D(const Quaternion<T>& _quaternion, Matrix3x3<T>* matrix)
    {
        const T b = _quaternion.imaginary.x;
        const T c = _quaternion.imaginary.y;
        const T d = _quaternion.imaginary.z;
        const T a = _quaternion.real;

        const T aa = a * a;
        const T bb = b * b;
        const T cc = c * c;
        const T dd = d * d;

        const T bc = b * c;
        const T ad = a * d;
        const T bd = b * d;
        const T ac = a * c;
        const T ab = a * b;
        const T cd = c * d;

        (*matrix)[0].x = aa + bb - cc - dd;
        (*matrix)[0].y = 2.f * (bc - ad);
        (*matrix)[0].z = 2.f * (bd + ac);

        (*matrix)[1].x = 2.f * (bc + ad);
        (*matrix)[1].y = aa - bb + cc - dd;
        (*matrix)[1].z = 2.f * (cd - ab);

        (*matrix)[2].x = 2.f * (bd - ac);
        (*matrix)[2].y = 2.f * (cd + ab);
        (*matrix)[2].z = aa - bb - cc + dd;
    }


    template <class T>
    void RotationMatrix3D(const Vector3f& _angle, Matrix3x3<T>* matrix)
    {
        RotationMatrix3D(_angle.x, _angle.y, _angle.z, matrix);
    }

    template <class T>
    void RotationMatrix3D(const Vector3f& _angle, Matrix4x4<T>* matrix)
    {
        Matrix3x3<T> m3;
        RotationMatrix3D(_angle, &m3);

        MatrixCast<T, Matrix3x3<T>, Matrix4x4<T>>(m3, matrix);

        (*matrix)[3][3] = 1.f;
    }

    template <class T>
    void RotationMatrix3D(const Quaternion<T>& _quaternion, Matrix4x4<T>* matrix)
    {
        Matrix3x3<T> m3;
        RotationMatrix3D(_quaternion, &m3);
        MatrixCast<T, Matrix3x3<T>, Matrix4x4<T>>(m3, matrix);
        (*matrix)[3][3] = 1.f;
    }


    // Scaling //
    template <class T>
    void ScaleMatrix2D(const Vector2f& _scaling, Matrix2x2<T>* matrix)
    {
        for (size_t i = 0; i < Matrix2x2<T>::Size; ++i)
        {
            (*matrix)[i][i] = _scaling[i];
        }
    }

    template <class T>
    void ScaleMatrix2D(const Vector2f& _scaling, Matrix3x3<T>* matrix)
    {
        Matrix2x2<T> m2;
        ScaleMatrix2D(_scaling, &m2);
        MatrixCast<T, decltype(m2), decltype(*matrix)>() > (m2, matrix);
        (*matrix)[2][2] = 1.f;
    }

    template <class T>
    void ScaleMatrix3D(const Vector3f& _scaling, Matrix3x3<T>* _matrix)
    {
        for (size_t i = 0; i < Matrix3x3<T>::Size; ++i)
        {
            (*_matrix)[i][i] = _scaling[i];
        }
    }

    template <class T>
    void ScaleMatrix3D(const Vector3f& _scaling, Matrix4x4<T>* _matrix)
    {
        Matrix3x3<T> m3;
        ScaleMatrix3D(_scaling, &m3);
        MatrixCast<T, Matrix3x3<T>, Matrix4x4<T>>(m3, _matrix);
        (*_matrix)[3][3] = 1.f;
    }

    // Translation //
    template <class T>
    void TranslationMatrix2D(const Vector2f& _translation, Matrix2x2<T>* _matrix)
    {
        (*_matrix)[1] = _translation;
    }

    template <class T>
    void TranslationMatrix2D(const Vector2f& _translation, Matrix3x3<T>* _matrix)
    {
        Matrix2x2<T> m2;
        TranslationMatrix2D(_translation, &m2);
        MatrixCast<T, Matrix2x2<T>, Matrix3x3<T>>(m2, _matrix);
        (*_matrix)[2][2] = 1.f;
    }

    template <class T>
    void TranslationMatrix3D(const Vector3f& _translation, Matrix3x3<T>* _matrix)
    {
        (*_matrix)[2] = _translation;
    }

    template <class T>
    void TranslationMatrix3D(const Vector3f& _translation, Matrix4x4<T>* _matrix)
    {
        Matrix3x3<T> m2;
        TranslationMatrix3D(_translation, &m2);
        MatrixCast<T, Matrix3x3<T>, Matrix4x4<T>>(m2, _matrix);
        (*_matrix)[3][3] = 1.f;
    }


    // Graphic //
    template <typename T>
    Matrix4x4<T> LookAtRH(const Vector3<T>& _eye, const Vector3<T>& _center, const Vector3<T>& _up)
    {
        Vector3<T> f = (_center - _eye).Normalize();
        Vector3<T> s = Vector3<T>::Cross(f, _up).Normalize();
        Vector3<T> u = Vector3<T>::Cross(s, f);

        Matrix4x4<T> result = Matrix4x4<T>::Identity();
        result[0][0] = s.x;
        result[1][0] = s.y;
        result[2][0] = s.z;
        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;
        result[0][2] = -f.x;
        result[1][2] = -f.y;
        result[2][2] = -f.z;

        // Apply translation to the matrix (dot products for camera position)
        result[3][0] = -Vector3<T>::Dot(s, _eye);
        result[3][1] = -Vector3<T>::Dot(u, _eye);
        result[3][2] = Vector3<T>::Dot(f, _eye);

        return result;
    }


    template <typename T>
    Matrix4x4<T> PerspectiveMatrix(const T fov, const T aspect, const T Near, const T Far)
    {
        const T fFovRad = static_cast<T>(1) / std::tanf(fov / static_cast<T>(2.f));
        const T zdiff = Near - Far;

        const T r00 = fFovRad / aspect;
        const T r11 = fFovRad;

        const T r22 = (Far + Near) / zdiff;
        const T r32 = (static_cast<T>(2) * Far * Near) / zdiff;

        return {
            {r00, 0.f, 0.f, 0.f},
            {0.f, r11, 0.f, 0.f},
            {0.f, 0.f, r22, static_cast<T>(-1.0)},
            {0, 0, r32, 0.f}
        };
    };

    template <typename T>
    Matrix4x4<T> PerspectiveMatrixFlipYAxis(const T fov, const T aspect, const T Near, const T Far)
    {
        const T fFovRad = static_cast<T>(1) / std::tanf(fov / static_cast<T>(2.f));
        const T zdiff = Near - Far;

        const T r00 = fFovRad / aspect;
        const T r11 = fFovRad;

        const T r22 = (Far + Near) / zdiff;
        const T r32 = (static_cast<T>(2) * Far * Near) / zdiff;

        return {
            {r00, 0.f, 0.f, 0.f},
            {0.f, -r11, 0.f, 0.f},
            {0.f, 0.f, r22, static_cast<T>(-1.0)},
            {0, 0, r32, 0.f}
        };
    };

    template <class T>
    constexpr static Matrix4x4<T> OrthoGraphicMatrix(T left, T right, T bottom, T top, T zNear, T zFar)
    {
        T topBottomDiff = top - bottom;
        T rightLeftDiff = right - left;
        T farMinusNear = zFar - zNear;

        T r00 = static_cast<T>(2) / rightLeftDiff;
        T r11 = static_cast<T>(2) / topBottomDiff;
        T r22 = -static_cast<T>(2) / farMinusNear;

        T r03 = -(right + left) / rightLeftDiff;
        T r13 = -(top + bottom) / topBottomDiff;
        T r23 = -(zFar + zNear) / farMinusNear;

        return {
            {r00, 0.f, 0.f, 0.f},
            {0.f, r11, 0.f, 0.f},
            {0.f, 0.f, r22, 0.f},
            {r03, r13, r23, 1.f}
        };
    }

    // Determinant //

    template <class T>
    constexpr inline static T Determinant(const Matrix2x2<T>& matrix)
    {
        T result = 0;

        result = matrix[0].x * matrix[1].y - matrix[0].y * matrix[1].x;

        return result;
    }

    template <class T>
    constexpr inline static T Determinant(const Matrix3x3<T>& matrix)
    {
        T result = 0;

        T d0 = Determinant(Matrix2x2<T>(matrix[1].y, matrix[1].z, matrix[2].y, matrix[2].z));

        T d1 = Determinant(Matrix2x2<T>(matrix[1].x, matrix[1].z, matrix[2].x, matrix[2].z));

        T d2 = Determinant(Matrix2x2<T>(matrix[1].x, matrix[1].y, matrix[2].x, matrix[2].y));

        T m0 = +1 * matrix[0].x * d0;
        T m1 = -1 * matrix[0].y * d1;
        T m2 = +1 * matrix[0].z * d2;

        result = m0 + m1 + m2;

        return result;
    }

    template <class T>
    T Determinant(const Matrix4x4<T>& matrix)
    {
        T result = 0;

        Matrix3x3<T> m0;
        m0[0].x = matrix[1].y;
        m0[1].x = matrix[2].y;
        m0[2].x = matrix[3].y;
        m0[0].y = matrix[1].z;
        m0[1].y = matrix[2].z;
        m0[2].y = matrix[3].z;
        m0[0].z = matrix[1].w;
        m0[1].z = matrix[2].w;
        m0[2].z = matrix[3].w;

        Matrix3x3<T> m1;
        m1[0].x = matrix[1].x;
        m1[1].x = matrix[2].x;
        m1[2].x = matrix[3].x;
        m1[0].y = matrix[1].z;
        m1[1].y = matrix[2].z;
        m1[2].y = matrix[3].z;
        m1[0].z = matrix[1].w;
        m1[1].z = matrix[2].w;
        m1[2].z = matrix[3].w;


        Matrix3x3<T> m2;
        m2[0].x = matrix[1].x;
        m2[1].x = matrix[2].x;
        m2[2].x = matrix[3].x;
        m2[0].y = matrix[1].y;
        m2[1].y = matrix[2].y;
        m2[2].y = matrix[3].y;
        m2[0].z = matrix[1].w;
        m2[1].z = matrix[2].w;
        m2[2].z = matrix[3].w;

        Matrix3x3<T> m3;
        m3[0].x = matrix[1].x;
        m3[1].x = matrix[2].x;
        m3[2].x = matrix[3].x;
        m3[0].y = matrix[1].y;
        m3[1].y = matrix[2].y;
        m3[2].y = matrix[3].y;
        m3[0].z = matrix[1].z;
        m3[1].z = matrix[2].z;
        m3[2].z = matrix[3].z;

        T add0 = matrix[0].x * Determinant(m0);
        T add1 = -1.f * matrix[0].y * Determinant(m1);
        T add2 = matrix[0].z * Determinant(m2);
        T add3 = -1.f * matrix[0].w * Determinant(m3);

        result = add0 + add1 + add2 + add3;

        return result;
    }

    template <class T>
    void AdjoinMatrix(const Matrix4x4<T>& matrix, Matrix4x4<T>* _out)
    {
        Matrix4x4<T> copy = matrix;

        // First row
        (*_out)[0][0] = Determinant(Matrix3x3<T>({
            {copy[1][1], copy[1][2], copy[1][3]},
            {copy[2][1], copy[2][2], copy[2][3]},
            {copy[3][1], copy[3][2], copy[3][3]}
        }));

        (*_out)[0][1] = -Determinant(Matrix3x3<T>({
            {copy[1][0], copy[1][2], copy[1][3]},
            {copy[2][0], copy[2][2], copy[2][3]},
            {copy[3][0], copy[3][2], copy[3][3]}
        }));

        (*_out)[0][2] = Determinant(Matrix3x3<T>({
            {copy[1][0], copy[1][1], copy[1][3]},
            {copy[2][0], copy[2][1], copy[2][3]},
            {copy[3][0], copy[3][1], copy[3][3]}
        }));

        (*_out)[0][3] = -Determinant(Matrix3x3<T>({
            {copy[1][0], copy[1][1], copy[1][2]},
            {copy[2][0], copy[2][1], copy[2][2]},
            {copy[3][0], copy[3][1], copy[3][2]}
        }));

        // Second row
        (*_out)[1][0] = -Determinant(Matrix3x3<T>({
            {copy[0][1], copy[0][2], copy[0][3]},
            {copy[2][1], copy[2][2], copy[2][3]},
            {copy[3][1], copy[3][2], copy[3][3]}
        }));

        (*_out)[1][1] = Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][2], copy[0][3]},
            {copy[2][0], copy[2][2], copy[2][3]},
            {copy[3][0], copy[3][2], copy[3][3]}
        }));

        (*_out)[1][2] = -Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][3]},
            {copy[2][0], copy[2][1], copy[2][3]},
            {copy[3][0], copy[3][1], copy[3][3]}
        }));

        (*_out)[1][3] = Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][2]},
            {copy[2][0], copy[2][1], copy[2][2]},
            {copy[3][0], copy[3][1], copy[3][2]}
        }));

        // Third row
        (*_out)[2][0] = Determinant(Matrix3x3<T>({
            {copy[0][1], copy[0][2], copy[0][3]},
            {copy[1][1], copy[1][2], copy[1][3]},
            {copy[3][1], copy[3][2], copy[3][3]}
        }));

        (*_out)[2][1] = -Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][2], copy[0][3]},
            {copy[1][0], copy[1][2], copy[1][3]},
            {copy[3][0], copy[3][2], copy[3][3]}
        }));

        (*_out)[2][2] = Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][3]},
            {copy[1][0], copy[1][1], copy[1][3]},
            {copy[3][0], copy[3][1], copy[3][3]}
        }));

        (*_out)[2][3] = -Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][2]},
            {copy[1][0], copy[1][1], copy[1][2]},
            {copy[3][0], copy[3][1], copy[3][2]}
        }));

        // Fourth row
        (*_out)[3][0] = -Determinant(Matrix3x3<T>({
            {copy[0][1], copy[0][2], copy[0][3]},
            {copy[1][1], copy[1][2], copy[1][3]},
            {copy[2][1], copy[2][2], copy[2][3]}
        }));

        (*_out)[3][1] = Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][2], copy[0][3]},
            {copy[1][0], copy[1][2], copy[1][3]},
            {copy[2][0], copy[2][2], copy[2][3]}
        }));

        (*_out)[3][2] = -Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][3]},
            {copy[1][0], copy[1][1], copy[1][3]},
            {copy[2][0], copy[2][1], copy[2][3]}
        }));

        (*_out)[3][3] = Determinant(Matrix3x3<T>({
            {copy[0][0], copy[0][1], copy[0][2]},
            {copy[1][0], copy[1][1], copy[1][2]},
            {copy[2][0], copy[2][1], copy[2][2]}
        }));

        *_out = _out->Transpose();
    }

    template <typename T>
    void Invert(const Matrix4x4<T>& _matrix, Matrix4x4<T>* _outMatrix)
    {
        // Compute the determinant of the matrix
        const T determinant = Determinant(_matrix);

        if (determinant == static_cast<T>(0))
        {
            return;
        }

        const T invertedDeterminant = static_cast<T>(1) / determinant;

        Matrix4x4<T> adj;
        AdjoinMatrix(_matrix, &adj);

        // Perform the inversion
        for (int i = 0; i < 4; i++)
        {
            for (int k = 0; k < 4; k++)
            {
                (*_outMatrix)[i][k] = invertedDeterminant * adj[i][k];
            }
        }
    }

    template <class T>
    Matrix3x3<T> AdjoinMatrix(const Matrix3x3<T>& matrix)
    {
        Matrix3x3<T> copy = matrix.Transpose();
        Matrix3x3<T> result;

        // Calculate the cofactors for each element
        T m1 = Determinant(Matrix2x2<T>(Vector2<T>(copy[1][1], copy[1][2]), Vector2<T>(copy[2][1], copy[2][2])));
        T m2 = Determinant(Matrix2x2<T>(Vector2<T>(copy[1][0], copy[1][2]), Vector2<T>(copy[2][0], copy[2][2])));
        T m3 = Determinant(Matrix2x2<T>(Vector2<T>(copy[1][0], copy[1][1]), Vector2<T>(copy[2][0], copy[2][1])));
        result[0][0] = m1;
        result[0][1] = -m2;
        result[0][2] = m3;

        m1 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][1], copy[0][2]), Vector2<T>(copy[2][1], copy[2][2])));
        m2 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][0], copy[0][2]), Vector2<T>(copy[2][0], copy[2][2])));
        m3 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][0], copy[0][1]), Vector2<T>(copy[2][0], copy[2][1])));
        result[1][0] = -m1;
        result[1][1] = m2;
        result[1][2] = -m3;

        m1 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][1], copy[0][2]), Vector2<T>(copy[1][1], copy[1][2])));
        m2 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][0], copy[0][2]), Vector2<T>(copy[1][0], copy[1][2])));
        m3 = Determinant(Matrix2x2<T>(Vector2<T>(copy[0][0], copy[0][1]), Vector2<T>(copy[1][0], copy[1][1])));
        result[2][0] = m1;
        result[2][1] = -m2;
        result[2][2] = m3;

        return result;
    }

    template <typename T>
    Matrix3x3<T> Invert(const Matrix3x3<T>& _matrix)
    {
        const Matrix3x3<T> adj = AdjoinMatrix(_matrix);

        const T determinant = Determinant(_matrix);
        const T invertedDeternimant = static_cast<T>(1) / determinant;

        Matrix3x3<T> result;
        for (size_t i = 0; i < Matrix3x3<T>::Size; i++)
        {
            for (size_t k = 0; k < Matrix3x3<T>::Size; k++)
            {
                result[i][k] = invertedDeternimant * adj[i][k];
            }
        }
        return result;
    }


    template <typename T>
    void ToMatrix(const Quaternion<T>& _from, Matrix3x3<T>* _out)
    {
        const T b = _from.imaginary.x;
        const T c = _from.imaginary.y;
        const T d = _from.imaginary.z;
        const T a = _from.real;

        const T aa = a * a;
        const T bb = b * b;
        const T cc = c * c;
        const T dd = d * d;

        const T bc = b * c;
        const T da = d * a;
        const T bd = b * d;
        const T ca = c * a;
        const T ba = b * a;
        const T cd = c * d;

        *_out =
        {
            {2.f * (aa + bb) - 1.f, 2.f * (bc + da), 2.f * (bd - ca)},
            {2.f * (bc - da), 2.f * (aa + cc) - 1.f, 2.f * (cd + ba)},
            {2.f * (bd + ca), 2.f * (cd - ba), 2.f * (aa + dd) - 1.f},
        };
    }

    template <typename T>
    void ToMatrix(const Quaternion<T>& _from, Matrix4x4<T>* _out)
    {
        Matrix3x3<T> m3;
        ToMatrix(_from, m3);
        MatrixCast<T, decltype(m3), decltype(*_out)>(m3, *_out);
    }

    template <typename T>
    void FromMatrix(const Matrix3x3<T>& _matrix, Quaternion<T>* _out)
    {
        T trace = _matrix.Trace();

        T a = sqrtf(1.f + trace) / 2.f;
        T divide = 4.f * a;
        T b = _matrix[2][1] - _matrix[1][2];
        T c = _matrix[0][2] - _matrix[2][0];
        T d = _matrix[1][0] - _matrix[0][1];

        T denom = 1.f / divide;

        return Quaternion(b * denom, c * denom, d * denom, -a).Normalize();
    }


    template <typename T>
    void FromMatrix(const Matrix4x4<T>& _matrix, Quaternion<T>* _out)
    {
        Matrix3x3<T> m3;
        MatrixCast<T, Matrix4x4<T>, Matrix3x3<T>>(_matrix, m3);

        T trace = m3.Trace();

        T a = sqrtf(1.f + trace) / 2.f;
        T divide = 4.f * a;
        T b = m3[2][1] - m3[1][2];
        T c = m3[0][2] - m3[2][0];
        T d = m3[1][0] - m3[0][1];

        T denom = 1.f / divide;

        return Quaternion(b * denom, c * denom, d * denom, -a).Normalize();
    }

    template <typename T>
    void Trs2D(const Vector2<T>& _translation, const T& _rotation, const Vector2<T>& _scale, Matrix3x3<T>* _outModel)
    {
        Matrix2x2<T> rot;
        Matrix2x2<T> scale;

        RotationMatrix2D(_rotation, &rot);
        ScaleMatrix2D(_rotation, &scale);

        *_outModel = rot * scale;
        *_outModel[Matrix3x3<T>::Size] = {_translation.x, _translation.y, static_cast<T>(1)};
    }

    template <typename T>
    void Trs3D(const Vector3<T>& _translation, const Vector3<T>& _rotation, const Vector3<T>& _scale,
               Matrix4x4<T>* _outModel)
    {
        Matrix4x4<T> rot;
        Matrix4x4<T> scale;

        RotationMatrix3D(_rotation, &rot);
        ScaleMatrix3D(_scale, &scale);

        *_outModel = rot * scale;
        (*_outModel)[Matrix4x4<T>::Size - 1] = {_translation.x, _translation.y, _translation.z, static_cast<T>(1)};
    }

    template <typename T>
    void Trs3D(const Vector3<T>& _translation, const Quaternion<T>& _rotation, const Vector3<T>& _scale,
               Matrix4x4<T>* _outModel)
    {
        Matrix4x4<T> rot;
        Matrix4x4<T> scale;

        RotationMatrix3D(_rotation, &rot);
        ScaleMatrix3D(_scale, &scale);

        *_outModel = rot * scale;
        (*_outModel)[Matrix4x4<T>::Size - 1] = {_translation.x, _translation.y, _translation.z, static_cast<T>(1)};
    }
}
