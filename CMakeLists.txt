cmake_minimum_required(VERSION 3.9)
project(Sudoku_Cpp_Shell)

set(CMAKE_CXX_STANDARD 11)

add_executable(Sudoku_Cpp_Shell
        src/BTSolver.cpp
        src/BTSolver.hpp
        src/Constraint.cpp
        src/Constraint.hpp
        src/ConstraintNetwork.cpp
        src/ConstraintNetwork.hpp
        src/Domain.cpp
        src/Domain.hpp
        src/Main.cpp
        src/SudokuBoard.cpp
        src/SudokuBoard.hpp
        src/Trail.cpp
        src/Trail.hpp
        src/Variable.cpp
        src/Variable.hpp)
