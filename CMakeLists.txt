cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tired VERSION 0.0.1 LANGUAGES C CXX)

add_executable(tired src/main.cpp
    src/uio/uio.cpp
    src/executor/executor.cpp)