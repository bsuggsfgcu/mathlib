cmake_minimum_required(VERSION 3.28)
project(mathlib)

set(CMAKE_CXX_STANDARD 20)

add_library(mathlib STATIC library.cpp)

# Create the executable from main.cpp
add_executable(main_exec main.cpp)

# Link the mathlib library to the executable
target_link_libraries(main_exec PRIVATE mathlib)