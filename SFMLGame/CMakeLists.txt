cmake_minimum_required(VERSION 3.12)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "SFML/include")
set(SFML_LIBRARY_DIR "SFML/lib")
set(SFML_DIR "SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(SFMLGame main.cpp MainCharacter.cpp MainCharacter.h Heart.cpp Heart.h FireBall.cpp FireBall.h Arrow.cpp Arrow.h TileMap.cpp TileMap.h Menu.cpp Menu.h Game.cpp Game.h GameState.cpp GameState.h ConcreteStateMenu.cpp ConcreteStateMenu.h ConcreteStateGame.cpp ConcreteStateGame.h ConcreteStateTutorial.cpp ConcreteStateTutorial.h)
target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system)