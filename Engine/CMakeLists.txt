
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
find_package(Vulkan REQUIRED FATAL_ERROR)
include_directories(${Vulkan_INCLUDE_DIRS})
link_libraries(${Vulkan_LIBRARIES})
message(STATUS "Vulkan Includes: ${Vulkan_INCLUDE_DIRS}, Link: ${Vulkan_LIBRARIES}")

add_subdirectory(Source/Runtime)
add_subdirectory(Source/Core)
