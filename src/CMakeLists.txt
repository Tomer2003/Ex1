cmake_minimum_required(VERSION 3.0.0)
project(matrix VERSION 0.1.0)

set(C_STANDARD C99)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(
    ErrorCode SHARED
    ErrorCode.c
    ErrorCode.h
)


add_library(
    Matrix SHARED
    Matrix.c
    Matrix.h
)