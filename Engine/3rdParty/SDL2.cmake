
include(ExternalProject)

ExternalProject_Add(
  SDL2

  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG "main"

  UPDATE_COMMAND ""
  PATCH_COMMAND ""

  SOURCE_DIR "${THIRD_PARTY_DIR}/SDL2"
  INSTALL_DIR "${GLOBAL_OUTPUT_PATH}/SDL2"

  CMAKE_ARGS -DSDL_STATIC:BOOL=FALSE
        -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/SDL2
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}

  TEST_COMMAND ""
)

message(STATUS "SDL2 Source: ${THIRD_PARTY_DIR}/SDL2")

ExternalProject_Add_Step(
        SDL2 CopyToBin
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/SDL2/bin ${GLOBAL_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/SDL2/lib ${GLOBAL_OUTPUT_PATH}
        DEPENDEES install
)

set(SDL2_INCLUDE_DIRS "${THIRD_PARTY_DIR}/SDL2/include")
set(SDL2_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}SDL2d${CMAKE_SHARED_LIBRARY_SUFFIX}")
include_directories(${SDL2_INCLUDE_DIRS})

message(STATUS "Adding include dir: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 Library: ${SDL2_LIBRARIES}")
