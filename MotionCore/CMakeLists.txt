cmake_minimum_required(VERSION 3.26)

project(MotionCore VERSION 0.1.0 LANGUAGES C CXX)

# Enable parallel compilation for MSVC
if(MSVC)
    add_compile_options(/MP)
endif()

# Set c++ standart
set(CMAKE_CXX_STANDARD ${MOTION_CPP_VERSION})
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
