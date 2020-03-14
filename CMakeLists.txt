cmake_minimum_required(VERSION 3.15)
project(template C)

set(CMAKE_C_STANDARD 99)

add_executable(template main.c template.h array.h stack.h queue.h list.h)