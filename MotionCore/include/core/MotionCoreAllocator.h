#pragma once

#include "MotionCoreHeader.h"

namespace MotionCore
{
	class MotionCoreAllocator
	{
	public:
		static void Initialize();

		static void Destroy();

		MOTION_CORE static void* Alloc(size_t _size);

		MOTION_CORE static void Free(void* _data);
	private:

	};
}

