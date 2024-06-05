cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_STANDARD 17)

set (CMAKE_C_COMPILER gcc)

add_compile_options(-Wall)

project(MineSweep)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(MineSweep ${SRC_LIST})