cmake_minimum_required(VERSION 3.14)
project(snake)

set(CMAKE_CXX_STANDARD 17)


add_executable(packman src/GameProcessWorking src/GameSelect.cpp src/Music.cpp src/bonus.cpp src/bots.cpp src/endgame.cpp src/exit.cpp src/field.cpp src/gameprocess.cpp src/gameselection.cpp src/ghost.cpp src/hero.cpp src/maps.cpp src/menu.cpp src/menuBase.cpp src/packman.cpp src/pause.cpp src/settings.cpp src/main.cpp)
target_link_libraries(packman sfml-graphics sfml-window sfml-system sfml-audio)
