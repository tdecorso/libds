cmake_minimum_required(VERSION 3.31)

project(tds)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

add_library(tds STATIC src/da.c 
                       src/stack.c
                       src/list.c  
                       src/bst.c  )

add_executable(test_da    tests/test_da.c)
add_executable(test_stack tests/test_stack.c)
add_executable(test_list  tests/test_list.c)
add_executable(test_bst   tests/test_bst.c)

target_include_directories(tds PUBLIC include)

target_link_libraries(test_da    PRIVATE tds)
target_link_libraries(test_stack PRIVATE tds)
target_link_libraries(test_list  PRIVATE tds)
target_link_libraries(test_bst   PRIVATE tds)

