cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

project(underwater_world)
file(GLOB SRC
        "src/*.h"
        "src/*.cpp"
        )
include_directories(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(third_party/glfw)
include_directories(third_party/glfw/include)

add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)

add_subdirectory(third_party/glm)

add_subdirectory(third_party/tinyobjloader)

include_directories(third_party/entt/src)

include_directories(third_party/stb)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})




target_link_libraries(${CMAKE_PROJECT_NAME} glfw glad glm tinyobjloader)
