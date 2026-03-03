cmake_minimum_required(VERSION 3.31)

project(tds)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

add_executable(test_da    tests/test_da.c)
add_executable(test_list  tests/test_list.c)
add_executable(test_ht    tests/test_ht.c)

target_include_directories(test_da   PUBLIC include)
target_include_directories(test_list PUBLIC include)
target_include_directories(test_ht   PUBLIC include)
