cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(dArcEngine LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CMakeDependentOption)
#include(External/cmake/CXXModules.cmake)

set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${PROJECT_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")
set(GLOBAL_OUTPUT_PATH ${BINARY_ROOT_DIR})

include(External/cmake/GlobalDefines.cmake)

link_directories(${GLOBAL_OUTPUT_PATH})

SET(CMAKE_C_FLAGS_DEBUG "$<$<CONFIG:DEBUG>:-D_DEBUG>")

add_subdirectory(Engine)
