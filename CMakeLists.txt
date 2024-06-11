cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 23)
set (CMAKE_C_COMPILER gcc)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Ofast")

project(MineSweep)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(MineSweep ${SRC_LIST})