cmake_minimum_required(VERSION 3.16)

project(odes LANGUAGES CXX)

# Various sets
set(CMAKE_CXX_STANDARD 17)

# Sources
add_executable(odes src/main.cpp)