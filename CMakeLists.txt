cmake_minimum_required(VERSION 3.10)

# set the project name
project(strategic_map_compiler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(third-party)

add_executable(strategic_map_compiler src/main.cpp
src/parser.cpp 
src/parser.hpp
src/region.hpp
src/compiler.cpp
src/compiler.hpp
src/visualize.hpp
src/visualize.cpp
src/projections.hpp
src/projections.cpp

third-party/nlohmann/json.hpp
third-party/libbmp/libbmp.h
third-party/libbmp/libbmp.cpp)