cmake_minimum_required(VERSION 3.21)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Matrix
        main.cpp
        matrix.cpp
        matrix.h)
