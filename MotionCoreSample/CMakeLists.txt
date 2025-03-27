cmake_minimum_required(VERSION 3.26)

project(MotionCoreSample VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCE_FILES src/source/*.c src/source/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/include/*.h src/include/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp ${HEADER_FILES}) 

target_link_libraries(${PROJECT_NAME} PRIVATE MotionCore)

if (BUILD_DYNAMIC_IMAGE)
        # Avoid copy the pdb on realse
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            $<TARGET_FILE:MotionCore> 
        $<TARGET_FILE_DIR:MotionCoreSample>)

    target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_DYNAMIC_IMAGE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_CORE_IMPORTS)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src/include)
