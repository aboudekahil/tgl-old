cmake_minimum_required(VERSION 3.28)
project(tgl)

set(CMAKE_CXX_STANDARD 20)

add_library(tgl STATIC
        src/tgl.cpp
        src/tgl.h
        src/internal/internal.h
        src/internal/internal.cpp
        src/colors/tgl_colors.h
        src/colors/tgl_colors.cpp
)


add_executable(main test/main.cpp
        src/tgl.cpp
        src/internal/internal.cpp
        src/colors/tgl_colors.cpp
)
