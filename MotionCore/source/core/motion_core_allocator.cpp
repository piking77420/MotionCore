#include <memory>



#include "core/motion_core_allocator.h"

using namespace MotionCore;

void MotionCoreAllocator::Initialize()
{
	
}

void MotionCoreAllocator::Destroy()
{

}

void* MotionCoreAllocator::Alloc(size_t _size)
{
	return malloc(_size);
}

void MotionCoreAllocator::Free(void* _data)
{
	free(_data);
}
