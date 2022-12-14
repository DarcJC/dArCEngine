
# Add target to build static shaders
# TODO: For the shaders generated at runtime, should use libshdaerc

# Reading variable: SHADER_SOURCE_DIR, SHADER_BINARY_DIR

find_package(Vulkan REQUIRED COMPONENTS glslc FATAL_ERROR)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

# Build shader to spir-v
file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp
        ${SHADER_SOURCE_DIR}/*.geom
        ${SHADER_SOURCE_DIR}/*.tesc
        ${SHADER_SOURCE_DIR}/*.tese
        ${SHADER_SOURCE_DIR}/*.mesh
        ${SHADER_SOURCE_DIR}/*.task
        ${SHADER_SOURCE_DIR}/*.rgen
        ${SHADER_SOURCE_DIR}/*.rchit
        ${SHADER_SOURCE_DIR}/*.rmiss)

add_custom_command(
        COMMAND
        ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        OUTPUT ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach(source IN LISTS SHADERS)
    get_filename_component(FILENAME ${source} NAME)
    add_custom_command(
            COMMAND
            ${glslc_executable}
            #      -MD -MF ${SHADER_BINARY_DIR}/${FILENAME}.d
            -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
            ${source}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(Shader2SPV ALL DEPENDS ${SPV_SHADERS})
