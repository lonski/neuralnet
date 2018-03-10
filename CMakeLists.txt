cmake_minimum_required(VERSION 2.8.4)
project(neuralnet)

set(neuralnet_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O2 -Wall -Wextra -Wformat-security -pipe -Wno-unused-local-typedefs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${neuralnet_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${neuralnet_BINARY_DIR}")

add_subdirectory(src)
add_subdirectory(test)