cmake_minimum_required(VERSION 3.30)
project(open_translation_server)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os  -O3 -flto -march=native -flto -funroll-loops")

add_library(open_translation_server STATIC library.cpp)
