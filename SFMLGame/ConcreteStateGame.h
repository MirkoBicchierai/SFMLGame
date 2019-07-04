#ifndef SFMLGAME_CONCRETESTATEGAME_H
#define SFMLGAME_CONCRETESTATEGAME_H

#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileMap.h"
class ConcreteStateGame : public GameState{
public:

     void draw(MainCharacter &mainCharacter) override ;
     void update(MainCharacter &mainCharacter) override;
     void handleInput(MainCharacter &mainCharacter) override;
     bool loadMap=false;
     explicit ConcreteStateGame(Game* game);

private:
    TileMap map{};
    std::vector <int> vec;
    void backToMenu();
    void loadFromFile(const std::string &path);
};

#endif
