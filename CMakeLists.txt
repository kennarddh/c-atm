cmake_minimum_required(VERSION 3.28)
project(C C)

set(CMAKE_C_STANDARD 23)

include_directories("${CMAKE_SOURCE_DIR}")

add_executable(C main.c)
