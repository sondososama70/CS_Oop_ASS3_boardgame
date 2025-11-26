cmake_minimum_required(VERSION 3.31)
project(Ass3_BoardGames)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List of all source files
set(SOURCES
        main.cpp
        SOS_UI.cpp
        SOS_Board.cpp
        NumericalTicTacToe.cpp
        miser.cpp
        FiveByFive.cpp
        FiveByFive.h
)

# Create executable target
add_executable(BoardGames ${SOURCES})

# Optional: Include directories if headers are in separate folders
# target_include_directories(CS_ASSIGNMENT2_SOUND PRIVATE ${PROJECT_SOURCE_DIR})
