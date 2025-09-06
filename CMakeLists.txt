cmake_minimum_required(VERSION 3.26)

set(BUILD_DYNAMIC_IMAGE OFF)
set(BUILD_SAMPLE ON)
set(BUILD_UNIT_TEST ON)

project(MotionCore VERSION 0.1.0 LANGUAGES C CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

add_subdirectory(MotionCore)
if (BUILD_SAMPLE)
    add_subdirectory(MotionCoreSample)
endif()

if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()