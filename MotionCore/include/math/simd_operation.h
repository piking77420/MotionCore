#pragma once
#ifndef TOOL_BOXSIMD
#define TOOL_BOXSIMD

#include "toolbox_typedef.hpp"
#include <immintrin.h>

namespace Tbx
{
    using Float64 = double;
    using Float32 = float;
    
    namespace SIMD
    {
        template<typename T>
        Vector3<T> min(const Vector3<T>& _minValue, const Vector3<T>& _vec)
        {
            Vector3<T> outVec = _vec;

#ifdef __MACHINEX86_X64 
            if constexpr (std::is_same_v<typename Vector3<T>::DataType, float>)
            {
                __m128 minValueVec = _mm_set_ps(0.0f, _minValue.z, _minValue.y, _minValue.x);
                __m128 vec = _mm_set_ps(0.0f, _vec.z, _vec.y, _vec.x);  // set the vector with a dummy 4th element
                __m128 result = _mm_min_ps(vec, minValueVec);

                float outArray[4];
                _mm_storeu_ps(outArray, result);
                outVec.x = outArray[0];
                outVec.y = outArray[1];
                outVec.z = outArray[2];
            }
            else if (std::is_same_v<typename Vector3<T>::DataType, double>)
            {
                __m256d minValueVec = _mm256_set_pd(0.0, _minValue.z, _minValue.y, _minValue.x);
                __m256d vec = _mm256_set_pd(0.0, _vec.z, _vec.y, _vec.x);  // set the vector with a dummy 4th element
                __m256d result = _mm256_min_pd(vec, minValueVec);

                double outArray[4];
                _mm256_storeu_pd(outArray, result);
                outVec.x = outArray[0];
                outVec.y = outArray[1];
                outVec.z = outArray[2];
            }
#else
            // Fallback for non-SIMD capable systems
            outVec.x = std::min(_minValue.x, _vec.x);
            outVec.y = std::min(_minValue.y, _vec.y);
            outVec.z = std::min(_minValue.z, _vec.z);
#endif

            return outVec;
        }

        template<typename T>
        Vector3<T> max(const Vector3<T>& _maxValue, const Vector3<T>& _vec)
        {
            Vector3<T> outVec = _vec;

#ifdef __MACHINEX86_X64 
            if constexpr (std::is_same_v<typename Vector3<T>::DataType, float>)
            {
                __m128 maxValueVec = _mm_set_ps(0.0f, _maxValue.z, _maxValue.y, _maxValue.x);
                __m128 vec = _mm_set_ps(0.0f, _vec.z, _vec.y, _vec.x);  
                __m128 result = _mm_max_ps(vec, maxValueVec);

                float outArray[4];
                _mm_storeu_ps(outArray, result);
                outVec.x = outArray[0];
                outVec.y = outArray[1];
                outVec.z = outArray[2];
            }
            else if (std::is_same_v<typename Vector3<T>::DataType, double>)
            {
                __m256d maxValueVec = _mm256_set_pd(0.0, _maxValue.z, _maxValue.y, _maxValue.x);
                __m256d vec = _mm256_set_pd(0.0, _vec.z, _vec.y, _vec.x);  
                __m256d result = _mm256_max_pd(vec, maxValueVec);

                double outArray[4];
                _mm256_storeu_pd(outArray, result);
                outVec.x = outArray[0];
                outVec.y = outArray[1];
                outVec.z = outArray[2];
            }
#else
            // Fallback for non-SIMD capable systems
            outVec.x = std::max(_minValue.x, _vec.x);
            outVec.y = std::min(_minValue.y, _vec.y);
            outVec.z = std::min(_minValue.z, _vec.z);
#endif

            return outVec;
        }

    }
    
}

#endif //TOOL_BOXSIMD  
