cmake_minimum_required(VERSION 3.17)
project(NumMeth C)

set(CMAKE_C_STANDARD 11)

include_directories(lab1)
set(LAB1 lab1/lab1.c lab1/lab1.h lab1/main.c)
add_executable(lab1_d ${LAB1})
target_link_libraries(lab1_d PRIVATE m)

include_directories(lab2)
set(LAB2 lab2/lab2.c lab2/lab2.h lab2/main.c)
add_executable(lab2_d ${LAB2})
target_link_libraries(lab2_d PRIVATE m)

