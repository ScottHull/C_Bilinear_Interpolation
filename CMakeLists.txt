cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp src/interpolation.h src/io.h)