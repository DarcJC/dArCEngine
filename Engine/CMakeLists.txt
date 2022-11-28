
set(ENGINE_ROOT_DIR "${PROJECT_ROOT_DIR}/Engine")
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/3rdParty")

# Use Multi Processors
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT dArCEditor)
endif()

include_directories(3rdParty/include)
include(3rdParty/SDL2.cmake)

# Import vulkan
find_package(Vulkan REQUIRED COMPONENTS glslc FATAL_ERROR)
include_directories(${Vulkan_INCLUDE_DIRS})
link_libraries(${Vulkan_LIBRARIES})
message(STATUS "Vulkan Includes: ${Vulkan_INCLUDE_DIRS}, Link: ${Vulkan_LIBRARIES}, GLSLC: ${glslc_executable}")

# Build shader
set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Shaders)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Shaders)
include(../External/cmake/BuildShader.cmake)

# Subproject
add_subdirectory(Source/Runtime)
add_subdirectory(Source/Core)
