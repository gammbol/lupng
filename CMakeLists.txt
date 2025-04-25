cmake_minimum_required(VERSION 3.25)
project(lupng)

add_executable(lupng lupng.c)

target_include_directories(lupng PUBLIC "~/projects/seria")
target_link_directories(lupng PUBLIC "~/projects/seria/build")
target_link_libraries(lupng PUBLIC seria)
