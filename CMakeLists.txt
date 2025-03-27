cmake_minimum_required(VERSION 3.26)

set(BUILD_DYNAMIC_IMAGE ON)
set(BUILD_SAMPLE ON)
set(BUILD_UNIT_TEST ON)

if(MSVC)
    if(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
        message(STATUS "Building for x64 architecture.")
    else()
        message(FATAL_ERROR "This project requires x64 architecture.")
    endif()
endif()

project(MotionCore VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(MotionCore)
if (BUILD_SAMPLE)
    add_subdirectory(MotionCoreSample)
endif()

if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()