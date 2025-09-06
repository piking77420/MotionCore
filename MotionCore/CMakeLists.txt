cmake_minimum_required(VERSION 3.26)




project(MotionCore VERSION 0.1.0 LANGUAGES C CXX)
add_library(MotionCoreSIMD INTERFACE)

# Enable parallel compilation for MSVC
if(MSVC)
    add_compile_options(/MP)
endif()

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYSTEM_PROCESSOR_LOWER)

# If user doesn't define intruction set this to auto 
# note: auto will enable all posible intruction set available  
if(NOT DEFINED MOTION_CORE_SIMD_INSTRUCTION_SET)
    set(MOTION_CORE_SIMD_INSTRUCTION_SET "AUTO" CACHE STRING
        "Target SIMD instruction set (AUTO)")
endif()

## Enumurate SIMD intruction set from architecture 
if(SYSTEM_PROCESSOR_LOWER MATCHES "^(x86_64|amd64)$")
    set(SUPPORTED_SIMD "SSE2;AVX;AVX2")
    message(STATUS "Target architecture: x86_64")
elseif(SYSTEM_PROCESSOR_LOWER MATCHES "^i[3-6]86$")
    set(SUPPORTED_SIMD "SSE2;AVX;AVX2")
    message(STATUS "Target architecture: 32-bit x86")
elseif(SYSTEM_PROCESSOR_LOWER MATCHES "^(arm|aarch64|arm64)$")
    set(SUPPORTED_SIMD "NEON;SVE")
    message(STATUS "Target architecture: ARM/ARM64")
else()
    message(FATAL_ERROR "Unsupported target architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

if (MOTION_CORE_SIMD_INSTRUCTION_SET STREQUAL "AUTO")
     ## if user doesn't define intruction set enable all
    set(MOTION_CORE_SIMD_INSTRUCTION_SET "${SUPPORTED_SIMD}")

elseif(NOT MOTION_CORE_SIMD_INSTRUCTION_SET STREQUAL "AUTO"
   AND NOT MOTION_CORE_SIMD_INSTRUCTION_SET STREQUAL "NONE")
    ## Check if user defined simd is supported if not fatal exit   
    list(FIND SUPPORTED_SIMD "${MOTION_CORE_SIMD_INSTRUCTION_SET}" SIMD_INDEX)
    if(SIMD_INDEX EQUAL -1)
        message(FATAL_ERROR
            "SIMD option '${MOTION_CORE_SIMD_INSTRUCTION_SET}' is not supported on this architecture. Supported options: ${SUPPORTED_SIMD}")
    endif()
endif()

if("SSE2" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    target_compile_definitions(MotionCoreSIMD INTERFACE MOTION_CORE_SIMD_SSE2)
    if(MSVC)
        if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8) # 32-bit MSVC needs /arch:SSE2
            add_compile_options("/arch:SSE2")
        endif()
    else()
        add_compile_options(-msse2)
    endif()
endif()

if("AVX" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    target_compile_definitions(MotionCoreSIMD INTERFACE MOTION_CORE_SIMD_AVX)

    if(MSVC)
        add_compile_options("/arch:AVX")
    else()
        add_compile_options(-mavx)
    endif()
endif()

if("AVX2" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    target_compile_definitions(MotionCoreSIMD INTERFACE MOTION_CORE_SIMD_AVX2)

    if(MSVC)
        add_compile_options("/arch:AVX2")
    else()
        add_compile_options(-mavx2)
    endif()
endif()

if("NEON" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    target_compile_definitions(MotionCoreSIMD INTERFACE MOTION_CORE_SIMD_NEON)

    if(NOT MSVC) # GCC/Clang only
        add_compile_options(-mfpu=neon)
    endif()
endif()

if("SVE" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    target_compile_definitions(MotionCoreSIMD INTERFACE MOTION_CORE_SIMD_SVE)
    if(NOT MSVC)
        add_compile_options(-march=armv8.2-a+sve)
    endif()
endif()

if("NONE" IN_LIST MOTION_CORE_SIMD_INSTRUCTION_SET)
    message(STATUS "SIMD disabled")
endif()

message(STATUS "Selected SIMD instruction set: ${MOTION_CORE_SIMD_INSTRUCTION_SET}")

 
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files
set(SOURCE_FILES "")  # Initialize
file(GLOB SOURCE_SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/source src/source/*)

foreach(SUBDIR ${SOURCE_SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/source/${SUBDIR}")
        file(GLOB_RECURSE SUBDIR_SOURCES
            CONFIGURE_DEPENDS
            src/source/${SUBDIR}/*.cpp
            src/source/${SUBDIR}/*.c
        )

        list(APPEND SOURCE_FILES ${SUBDIR_SOURCES})

        # Properly nested group name for IDEs
        source_group("source\\${SUBDIR}" FILES ${SUBDIR_SOURCES})
    endif()
endforeach()

# Collect header files
set(HEADER_FILES "")  # Initialize
file(GLOB HEADERS_SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/include src/include/*)

foreach(SUBDIR ${HEADERS_SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/include/${SUBDIR}")
        file(GLOB_RECURSE SUBDIR_HEADERS
            CONFIGURE_DEPENDS
            src/include/${SUBDIR}/*.hpp
            src/include/${SUBDIR}/*.h
        )

        list(APPEND HEADER_FILES ${SUBDIR_HEADERS})

        # Properly nested group name for IDEs
        source_group("include\\${SUBDIR}" FILES ${SUBDIR_HEADERS})
    endif()
endforeach()

#Collest inl files
set(INL_FILES "")  # Initialize
file(GLOB INLINE_SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/inline src/inline/*)


foreach(SUBDIR ${INLINE_SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/inline/${SUBDIR}")
        file(GLOB_RECURSE SUBDIR_INLINE
            CONFIGURE_DEPENDS
            src/inline/${SUBDIR}/*.inl
        )

        list(APPEND INL_FILES ${SUBDIR_INLINE})

        # Properly nested group name for IDEs
        source_group("inline\\${SUBDIR}" FILES ${SUBDIR_INLINE})
    endif()
endforeach()


if (BUILD_DYNAMIC_IMAGE)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INL_FILES} ${HEADER_FILES} )
    target_compile_definitions(${PROJECT_NAME} PRIVATE MOTION_DYNAMIC_IMAGE MOTION_CORE_EXPORTS)
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${INL_FILES} ${HEADER_FILES})
endif()



find_package(OpenCL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        src/include
        src/inline
        src/externals/include
)
