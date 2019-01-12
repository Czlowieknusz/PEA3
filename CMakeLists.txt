cmake_minimum_required(VERSION 3.13)
project(PEA3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PEA3
        AlgorithmTSP.h
        DataLoader.cpp
        DataLoader.h
        main.cpp
        Menu.cpp
        Menu.h
        Test.cpp
        Test.h
        Timer.cpp
        Timer.h GeneticAlgorithm.cpp GeneticAlgorithm.h)
