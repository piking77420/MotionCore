#include "core/motion_core_engine.hpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>
#include <iostream>
#include <vector>

const char* kernelSource = R"CLC(
__kernel void hello(__global char* out) {
    out[0] = 'H';
    out[1] = 'e';
    out[2] = 'l';
    out[3] = 'l';
    out[4] = 'o';
    out[5] = ',';
    out[6] = ' ';
    out[7] = 'W';
    out[8] = 'o';
    out[9] = 'r';
    out[10] = 'l';
    out[11] = 'd';
    out[12] = '!';
    out[13] = '\0';
}
)CLC";
void MotionCore::MotionCoreEngine::Init(const MotionCoreEngineCreateInfo& _MotionCoreEngineCreateInfo)
{
    constexpr size_t allocAligne = alignof(RigidBody);

    
#ifdef _MSC_VER
    bodies = reinterpret_cast<RigidBody*>(_aligned_malloc(_MotionCoreEngineCreateInfo.maxBodies * sizeof(RigidBody), allocAligne));
#elif
        bodies = std::aligned_alloc(allocAligne, num_allocated_bytes));

#endif _MSC_VER

}
MotionCore::MotionCoreEngine::MotionCoreEngine()
{
	std::cout << "MotionCoreEngine " << std::endl;
}
MotionCore::MotionCoreEngine::~MotionCoreEngine()
{
    if (bodies != nullptr)
    {
#ifdef _MSC_VER
        _aligned_free(bodies);
        bodies = nullptr;
#elif
        std::free(bodies)
#endif
    }
}
void MotionCore::MotionCoreEngine::HelloEngine()
{
        // 1. Get platform
        cl_platform_id platform;
        clGetPlatformIDs(1, &platform, nullptr);

        // 2. Get device
        cl_device_id device;
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr);

        // 3. Create context
        cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, nullptr);

        // 4. Create command queue
        cl_command_queue queue = clCreateCommandQueue(context, device, 0, nullptr);

        // 5. Create and build program
        cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, nullptr, nullptr);
        clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);

        // 6. Create kernel
        cl_kernel kernel = clCreateKernel(program, "hello", nullptr);

        // 7. Create buffer
        char output[64];
        cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(output), nullptr, nullptr);

        // 8. Set kernel argument
        clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);

        // 9. Enqueue kernel
        size_t globalWorkSize[1] = { 1 };
        clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr);

        // 10. Read result
        clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(output), output, 0, nullptr, nullptr);

        std::cout << output << std::endl;

        // Cleanup
        clReleaseMemObject(buffer);
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);

    
}
