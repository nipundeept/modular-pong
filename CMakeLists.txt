cmake_minimum_required(VERSION 4.1)
project(PongBall C)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(PongBall main.c
pong.h
pong.c)

target_link_libraries(PongBall raylib)
