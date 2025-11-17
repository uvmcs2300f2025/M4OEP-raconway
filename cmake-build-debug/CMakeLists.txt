cmake_minimum_required(VERSION 3.26)
project(M1OEP_raconway)

set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_SOURCE_DIR}/statsVisual.py ${CMAKE_BINARY_DIR}/statsVisual.py COPYONLY)



add_executable(M1OEP_raconway ../main.cpp
        ../Card.h
        ../Player.h
        ../Player.cpp
        ../Deck.h
        ../Hand.cpp
        ../Hand.h
        ../Game.cpp
        ../Game.h
        ../Card.cpp
        ../testing.cpp
)
