cmake_minimum_required(VERSION 3.15)
project(Hearts)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hearts main.cpp Card.cpp Card.h Board.cpp Board.h Player.cpp Player.h RanPlayer.cpp RanPlayer.h HighCardHeurPlayer.cpp HighCardHeurPlayer.h MedHuerPlayer.cpp MedHuerPlayer.h)