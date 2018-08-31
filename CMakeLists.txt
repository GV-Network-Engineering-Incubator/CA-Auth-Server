cmake_minimum_required(VERSION 3.8)
project(Nucleus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/*)
add_executable(nucleus ${SOURCE_FILES})
