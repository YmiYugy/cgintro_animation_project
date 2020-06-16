cmake_minimum_required(VERSION 3.16)
project(underwater_world)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
        "src/*.h"
        "src/*.cpp"
        )
include_directories(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)
include_directories(third_party/glfw/include)

add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)

add_subdirectory(third_party/glm)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_INSTALL OFF)
add_subdirectory(third_party/assimp)
include_directories(third_party/assimp/include)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} glfw glad glm assimp)