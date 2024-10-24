#pragma once

#include "motion_core_header.h"

namespace MotionCore
{
	class MotionCoreAllocator
	{
	public:
		static void Initialize();

		static void Destroy();

		static void* Alloc(size_t _size);

		static void Free(void* _data);
	private:

	};
}

