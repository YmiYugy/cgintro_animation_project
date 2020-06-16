cmake_minimum_required(VERSION 3.16)
project(glad)

set(CMAKE_C_STANDARD 11)

include_directories(include)
add_library(glad src/glad.c)
