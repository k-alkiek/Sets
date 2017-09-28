cmake_minimum_required(VERSION 3.8)
project(Sets)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Set.cpp Set.h)
add_executable(Sets ${SOURCE_FILES})