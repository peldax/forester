cmake_minimum_required(VERSION 3.12)
project(forester)

set(CMAKE_CXX_STANDARD 17)

add_executable(forester
        main.cpp
        Graph.cpp Graph.hpp
        MutableGraph.cpp MutableGraph.hpp
        Generator.cpp Generator.hpp
        GraphSolver.cpp GraphSolver.hpp
        SmartGraphSolver.cpp SmartGraphSolver.hpp
        CacheState.hpp)
