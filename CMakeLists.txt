cmake_minimum_required(VERSION 3.31)

project(libds)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(ds STATIC src/da.c)
add_executable(test_da tests/test_da.c)

target_include_directories(ds PUBLIC include)
target_link_libraries(test_da PRIVATE ds)

