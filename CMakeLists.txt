cmake_minimum_required(VERSION 3.30.5)
project(CS_ASSIGNMENT2_SOUND)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS_ASSIGNMENT2_SOUND
        main.cpp
        SUS.cpp
        FiveByFive.cpp
        miser.cpp              # <--- ضيف ده (عشان خطأ miser)
        fourxfourTicTacToe.cpp
        NUMERICALTICTACTOE.cpp # <--- ضيف ده (عشان خطأ Numerical)
        # وأي ملف cpp تاني عندك
)