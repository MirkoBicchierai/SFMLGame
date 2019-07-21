#include "gtest/gtest.h"
#include <SFML/Graphics.hpp>
#include "../MainCharacter.h"
#include "../Tile.h"
#include "../TileMap.h"
#include "../Event.h"
#include "../config.cpp"
#include "../Game.h"
#include "../ConcreteStateTutorial.h"
TEST(Inventory, PickKeyTest) {
    Game* game = new Game();
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    TileMap tileMap;
    Event loopEvent;
    game->interact=true;
    game->typeInteract="silver_key";
    game->actualInteractI=0;
    game->actualInteractJ=0;
    const int level[] ={
        226, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    std::vector<int> level1;
    for (int i = 0; i <(16*8) ; ++i) {
        level1.push_back(level[i]);
    }
    std::string tile_set=MAP_ROOT"/tile-set.png";
    tileMap.load(tile_set,sf::Vector2u(64,64),level1,16, 8,window);
    mainCharacter.entitySprite.setPosition(0,0);
    loopEvent.mapInteraction(mainCharacter,game,tileMap);
    ASSERT_EQ(1,mainCharacter.inventory.NumberSilverKey);
}