#pragma once

#include "MotionCoreHeader.h"


namespace MotionCore
{
    class MotionCoreAllocator
    {
    public:
        MOTION_CORE_API static inline void* Allocate(size_t _size)
        {
            return malloc(_size);
        }

        MOTION_CORE_API static inline void* AllocateAlligned(size_t _size, size_t _alignement)
        {
            #ifdef _MSC_VER
            return _aligned_malloc(_size, _alignement);
            #elif
            return std::aligned_alloc(_size, _alignement));
            #endif _MSC_VER
    
        }

        MOTION_CORE_API static inline  void DeallocateAlligned(void* _ptr)
        {
            #ifdef _MSC_VER
            _aligned_free(_ptr);
            #elif
            std::free(_ptr)
            #endif
        }

        MOTION_CORE_API static inline void Deallocate(void* _ptr)
        {
            return std::free(_ptr);
        }

        MotionCoreAllocator() = delete;

        ~MotionCoreAllocator() = delete;

    private:
        
    };

}

#define OVERLOAD_MEMORY_OPERATOR(T)
        MOTION_CORE_API inline void* operator new(size_t size)\
        {\
              return MotionCore::MotionCoreAllocator::Allocate(size);\
        }\
        MOTION_CORE_API inline void operator delete(void* _ptr)\
        {\
            MotionCore::MotionCoreAllocator::Deallocate(_ptr);\
        }\
        