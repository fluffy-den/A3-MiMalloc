cmake_minimum_required(VERSION 3.18)

#
# Include Guard
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

#
# Project
#
project(
  "a3fy"
  LANGUAGES CXX
  VERSION 0.1
)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
set(LIBRARY_NAME lib${PROJECT_NAME})

#
# CPM
#
if(NOT EXISTS CPM_DOWNLOAD_VERSION)
  set(CPM_DOWNLOAD_VERSION 0.35.1)
endif()
set(CPM_DOWNLOAD_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpm/cpm_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  file(DOWNLOAD
       https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
       ${CPM_DOWNLOAD_LOCATION}
  )
endif()
include("cmake/cpm/cpm_${CPM_DOWNLOAD_VERSION}.cmake")

#
# Install Dirs
#
include(GNUInstallDirs)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../")
endif()

#
# Compiler flags
#
if(MSVC)
  add_compile_options(
    /W4
  )
else()
  add_compile_options(
    # extra debug
    -Wall
    -Wextra
    -pedantic
    -Wno-unknown-pragmas
    -fvisibility=hidden
    # auto-vectorisation types
    -mmmx
    -msse
    -msse2
    -mssse3
    -msse3
    -mfma
    -msse4
    -msse4.1
    -msse4.2
    -mavx
    -mavx2
    # auto-vectorisation debug
    -ftree-vectorizer-verbose=6
    -fopt-info-vec-optimized
    -fopt-info-vec-missed 
  )
endif()

# Release
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_compile_options(-O3)
endif()

#
# Is debug configuration?
#
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(OUTPUT_SUFFIX _dbg${OUTPUT_SUFFIX})
endif()

#
# CPM -> MiMalloc
#
if (CMAKE_BUILD_TYPE STREQUAL Debug)
endif()
CPMAddPackage(
  NAME mimalloc
  GIT_TAG master
  GITHUB_REPOSITORY microsoft/mimalloc
  OPTION MI_OVERRIDE=ON)
target_compile_definitions(mimalloc-static PUBLIC MI_SECURE=3)

#
# Library
#
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${LIBRARY_NAME} SHARED ${HEADERS} ${SOURCES})
target_compile_definitions(${LIBRARY_NAME} PRIVATE A3_FLUFFY_ALLOCATOR_CONSTRUCT=1)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(OUTPUT_SUFFIX _x64)
else()
  set(OUTPUT_SUFFIX)
endif()
set_target_properties(
  ${LIBRARY_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             LINKER_LANGUAGE CXX
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SYSTEM}/
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SYSTEM}/
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SYSTEM}/
             OUTPUT_NAME ${PROJECT_NAME}${OUTPUT_SUFFIX}
             PREFIX ""
)
target_link_libraries(
  ${LIBRARY_NAME}
  PUBLIC mimalloc-static
)
target_include_directories(
  ${LIBRARY_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> 
         $<INSTALL_INTERFACE:include/fluffy>
  PRIVATE src
)