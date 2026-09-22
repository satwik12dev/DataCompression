cmake_minimum_required(VERSION 3.20)

project(DataCompression C)

set(CMAKE_C_STANDARD 11)

file(GLOB QUESTIONS "Assignment1/*.c")

foreach(FILE ${QUESTIONS})
    get_filename_component(NAME ${FILE} NAME_WE)
    add_executable(${NAME} ${FILE}
            Assignment2/Q1.c)

endforeach()