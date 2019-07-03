#ifndef SFMLGAME_CONCRETESTATETUTORIAL_H
#define SFMLGAME_CONCRETESTATETUTORIAL_H

#include "ConcreteStateMenu.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileMap.h"

class ConcreteStateTutorial: public GameState {
public:
    bool loadmap=false;
    void draw(MainCharacter &mainCharacter) override ;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    explicit ConcreteStateTutorial(Game* game);

private:
    TileMap map{};
    std::vector <int> vec;
    void backToMenu();
    void loadFromFile(const std::string &path);
};


#endif
