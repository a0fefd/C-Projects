cmake_minimum_required(VERSION 3.28)
project(RocketGame C)

set(CMAKE_C_STANDARD 11)

set(SDL_PATH "D:\\nbigi0\\My Documents\\Coding\\C\\")
set(SDL_LIBRARY "D:\\nbigi0\\My Documents\\Coding\\C\\RocketGame\\SDL2.dll")
set(SDL_INCLUDE_DIR "D:\\nbigi0\\My Documents\\Coding\\C\\RocketGame\\include\\SDL2")
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

link_libraries(${SDL_LIBRARY})
add_executable(RocketGame main.c
        loop.c
        loop.h
        engine/engine.c
        engine/engine.h)
