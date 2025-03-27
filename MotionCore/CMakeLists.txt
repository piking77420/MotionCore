cmake_minimum_required(VERSION 3.26)

project(MotionCore VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCE_FILES src/source/*.c src/source/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/include/*.h src/include/*.hpp)


if (BUILD_DYNAMIC_IMAGE)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_DYNAMIC_IMAGE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_CORE_EXPORTS)

else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES}) 
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src/include)
