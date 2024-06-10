cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_STANDARD 23)

set (CMAKE_C_COMPILER gcc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer -Ofast")

project(MineSweep)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(MineSweep ${SRC_LIST})
