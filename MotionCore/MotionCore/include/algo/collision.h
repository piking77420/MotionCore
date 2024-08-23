#pragma once

#include "motion_core_typedef.h"

namespace MotionCore
{
    FORCEINLINE bool AABBAABB(const Vec3& _centerA, const Vec3& _extendA, const Vec3& _centerB, const Vec3& _extendB)
    {
        if (std::abs(_centerA.x -_centerB.x) > (_extendA.x + _extendB.x)) return false;
        if (std::abs(_centerA.y -_centerB.y) > (_extendA.y + _extendB.y)) return false;
        if (std::abs(_centerA.z -_centerB.z) > (_extendA.z + _extendB.z)) return false;

        return true;
    }
    

    FORCEINLINE bool SphereSphere(const Vec3& _centerA, numeric _radiusA, const Vec3& _centerB, numeric _radiusB)
    {
        const Vec3 sphereDirectionVector = _centerA - _centerB;
        const numeric distanceSquare = sphereDirectionVector.MagnitudeSquare();
        const numeric radiusSum = _radiusA * _radiusA + _radiusB * _radiusB;

       return distanceSquare <= radiusSum;
    }

    FORCEINLINE bool CaspuleCaspule(const Caspule& _a, const Caspule& _b)
    {
        
    }

    template <typename T>
     inline float TriangleArea2D(T _x1, T _y1, T _x2, T _y2, T _x3, T _y3)
    {
        return (_x1 - _x2) * (_y2 - _y3) - (_x2 - _x3) * (_y1 - _y2); 
    }
    
    template <typename T>
    FORCEINLINE void BaryCenter(const Tbx::Vector3<T>& _A, const Tbx::Vector3<T>& _B, const Tbx::Vector3<T>& _C, const Tbx::Vector3<T>& _P, T* _u, T* _v, T*_w)
    {
        
        Tbx::Vector3<T> m = Tbx::Vector3<T>::Cross(_B - _A, _C - _A);

        typename Tbx::Vector3<T>::DataType nu,nv,ood;

        T x = std::abs(m.x);
        T y = std::abs(m.y);
        T z = std::abs(m.z);

        if (x >= y && x >= z)
        {
            nu = TriangleArea2D(_P.y, _P.z, _B.z,_B.z,_C.y,_C.z);
            nv = TriangleArea2D(_P.y, _P.z, _C.y,_C.z,_A.y,_A.z);
            ood = static_cast<T>(1) / m.x;
            
        }else if (y >= x && y >= z)
        {
            nu = TriangleArea2D(_P.x, _P.z, _B.x,_B.z,_C.x,_C.z);
            nv = TriangleArea2D(_P.x, _P.z, _C.x,_C.z,_A.x,_A.z);
            ood = static_cast<T>(1) / -m.y;
        }
        else
        {
            nu = TriangleArea2D(_P.x, _P.y, _B.x,_B.y,_C.x,_C.z);
            nv = TriangleArea2D(_P.x, _P.y, _C.y,_C.y,_A.x,_A.y);
            ood = static_cast<T>(1) / m.z;
        }
        *_u = nu * ood;
        *_v = nu * ood;
        *_w = 1.0f - *_u - *_v;
    }

    template <typename T>
    bool IsInTriangle(Tbx::Vector3<T> _P, Tbx::Vector3<T> _A, Tbx::Vector3<T> _B, Tbx::Vector3<T> _C)
    {
        T u = static_cast<T>(0);
        T v = static_cast<T>(0);
        T w = static_cast<T>(0);

        BaryCenter<T>(_A, _B, _C, _P, &u , &v, &w);

        return v >= static_cast<T>(0) && w >= static_cast<T>(0) && (v + w) <= static_cast<T>(1);
    }
    
}

