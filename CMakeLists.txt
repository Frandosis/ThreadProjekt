cmake_minimum_required(VERSION 3.15)
project(ThreadProjekt C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c)

add_library (func STATIC functions.c)
add_library (da STATIC dynamicarray.c)
add_library(saq STATIC stackandqueue.c)

target_link_libraries(func  m)
target_link_libraries(func da)
target_link_libraries(func saq)
target_link_libraries(main func)
target_link_libraries(main da)