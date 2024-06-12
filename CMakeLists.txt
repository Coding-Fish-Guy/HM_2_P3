cmake_minimum_required(VERSION 3.28)
project(HM_2_P3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HM_2_P3
        C_DGLSolver.cpp
        C_DGLSolver.h
        CMyVector.cpp
        CMyVector.h
        main.cpp)
