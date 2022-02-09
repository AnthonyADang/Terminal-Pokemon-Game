cmake_minimum_required(VERSION 3.21)
project(Pokemon_Game C)

set(CMAKE_C_STANDARD 11)

include_directories(assignment_1.1)
include_directories(assignment_1.2)

add_executable(Pokemon_Game
        assignment_1.1/map.c
        assignment_1.1/map.h
        assignment_1.2/heap.c
        assignment_1.2/heap.h
        assignment_1.2/poke327.c)
