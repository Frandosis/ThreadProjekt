cmake_minimum_required(VERSION 3.15)
project(ThreadProjekt C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c
        functions.h)

add_library (prime STATIC functions.c)
add_library (da STATIC dynamicarray.c)

target_link_libraries(prime  m)
target_link_libraries(prime da)
target_link_libraries(main  prime)
target_link_libraries(main da)