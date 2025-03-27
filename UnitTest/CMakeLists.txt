cmake_minimum_required(VERSION 3.26)

project(UnitTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h *.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE MotionCore)
if (BUILD_DYNAMIC_IMAGE)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different 
          $<TARGET_FILE:MotionCore> 
          $<TARGET_FILE_DIR:UnitTest>)
          
  target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_DYNAMIC_IMAGE)
  target_compile_definitions(${PROJECT_NAME} PUBLIC MOTION_CORE_IMPORTS)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main)

# Goole test
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})