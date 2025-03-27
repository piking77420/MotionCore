#pragma once


#if defined(MOTION_DYNAMIC_IMAGE)
#ifdef MOTION_CORE_EXPORTS
#define MOTION_CORE_API __declspec(dllexport)
#elif MOTION_CORE_IMPORTS
#define MOTION_CORE_API __declspec(dllimport)
#else
#define MOTION_CORE_API
#endif
#else
#define MOTION_CORE_API
#endif

#define FORCEINLINE __forceinline

#include "toolbox_typedef.hpp"
#include "matrix_transformation.hpp"