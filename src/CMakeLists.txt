cmake_minimum_required(VERSION 3.12)
project(forester)

set(CMAKE_CXX_STANDARD 17)

add_executable(forester main.cpp SmartGraphSolver.cpp SmartGraphSolver.hpp Generator.cpp Generator.hpp CacheState.hpp MutableGraph.cpp MutableGraph.hpp Graph.cpp Graph.hpp GraphSolver.cpp GraphSolver.hpp)
