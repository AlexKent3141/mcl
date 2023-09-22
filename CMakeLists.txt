cmake_minimum_required(VERSION 3.19)
project(mcl LANGUAGES C)

add_compile_options(
  -Wall
  -Wextra
  -Werror
  -ansi)

add_library(mcl INTERFACE)

target_include_directories(mcl
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

enable_testing()
add_subdirectory(test)
