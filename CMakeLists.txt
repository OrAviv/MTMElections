cmake_minimum_required(VERSION 3.13)
project(MTMElections C)

set(CMAKE_C_STANDARD 99)

add_executable(MTMElections main.c citizen.c citizen.h city.c city.h candidate.c candidate.h mtm_elections.c)