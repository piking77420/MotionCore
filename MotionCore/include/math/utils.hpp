#pragma once

#include "toolbox_headerfile.hpp"
#include "toolbox_typedef.hpp"

namespace Tbx
{
     template <typename T>
     inline float TriangleArea2D(T _x1, T _y1, T _x2, T _y2, T _x3, T _y3)
     {
         return (_x1 - _x2) * (_y2 - _y3) - (_x2 - _x3) * (_y1 - _y2); 
     }
    
    template <typename T>
    void BaryCenter(const Vector3<T>& _A, const Vector3<T>& _B, const Vector3<T>& _C, const Vector3<T>& _P, T* _u, T* _v, T*_w)
    {
        
        Vector3<T> m = Vector3<T>::Cross(_B - _A, _C - _A);

        typename Vector3<T>::DataType nu,nv,ood;

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
    bool IsInTriangle(Vector3<T> _P, Vector3<T> _A, Vector3<T> _B, Vector3<T> _C)
    {
         T u = static_cast<T>(0);
         T v = static_cast<T>(0);
         T w = static_cast<T>(0);

         BaryCenter<T>(_A, _B, _C, _P, &u , &v, &w);

         return v >= static_cast<T>(0) && w >= static_cast<T>(0) && (v + w) <= static_cast<T>(1);
    }
}
