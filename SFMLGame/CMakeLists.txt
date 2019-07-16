cmake_minimum_required(VERSION 3.12)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googleTest)

set(SFML_INCLUDE_DIR "lib/SFML/include")
set(SFML_LIBRARY_DIR "lib/SFML/lib")
set(SFML_DIR "lib/SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

set(SOURCE_FILES main.cpp MainCharacter.cpp MainCharacter.h Heart.cpp Heart.h FireBall.cpp FireBall.h Arrow.cpp Arrow.h TileMap.cpp TileMap.h Menu.cpp Menu.h Game.cpp Game.h GameState.cpp GameState.h ConcreteStateMenu.cpp ConcreteStateMenu.h ConcreteStateGame.cpp ConcreteStateGame.h ConcreteStateTutorial.cpp ConcreteStateTutorial.h BaseStatistic.cpp BaseStatistic.h Tile.cpp Tile.h config.cpp stlastar.h fsa.h Enemy.cpp Enemy.h MapSearchNode.cpp MapSearchNode.h Event.cpp Event.h )

include_directories(${SFML_INCLUDE_DIR})
add_executable(SFMLGame main.cpp MainCharacter.cpp MainCharacter.h Heart.cpp Heart.h FireBall.cpp FireBall.h Arrow.cpp Arrow.h TileMap.cpp TileMap.h Menu.cpp Menu.h Game.cpp Game.h GameState.cpp GameState.h ConcreteStateMenu.cpp ConcreteStateMenu.h ConcreteStateGame.cpp ConcreteStateGame.h ConcreteStateTutorial.cpp ConcreteStateTutorial.h BaseStatistic.cpp BaseStatistic.h Tile.cpp Tile.h config.cpp stlastar.h fsa.h Enemy.cpp Enemy.h MapSearchNode.cpp MapSearchNode.h Event.cpp Event.h)
add_library(core ${SOURCE_FILES})

target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system sfml-audio)

target_link_libraries(SFMLGame core)


