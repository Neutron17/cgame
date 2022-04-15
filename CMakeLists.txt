cmake_minimum_required(VERSION 3.0)

project(cgame LANGUAGES C)

add_executable(cgame main.c)

install(TARGETS cgame RUNTIME DESTINATION bin)
