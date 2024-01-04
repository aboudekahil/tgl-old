cmake_minimum_required(VERSION 3.28)
project(tgl)

set(CMAKE_CXX_STANDARD 20)

add_library(tgl STATIC library.cpp
        src/tgl.cpp)
