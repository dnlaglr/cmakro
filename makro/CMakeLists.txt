cmake_minimum_required(VERSION 3.27)
project(makro VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(makro ${SOURCES})