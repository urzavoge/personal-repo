cmake_minimum_required(VERSION 3.24)
project(text_game)

set(CMAKE_CXX_STANDARD 20)

file(GLOB all_SRCS "${PROJECT_SOURCE_DIR}/saved/*.txt")

add_executable(text_game main.cpp src/game.cpp src/player.cpp src/room.cpp src/npc.cpp src/interface.cpp src/command.cpp src/items.cpp)
