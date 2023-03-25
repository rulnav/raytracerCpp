cmake_minimum_required(VERSION 3.0)

project(my_project)

add_executable(main main.cpp vectorclass.hpp pixelarray.hpp)

target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror -v)
