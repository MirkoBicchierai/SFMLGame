#ifndef SFMLGAME_CONCRETESTATEGAME_H
#define SFMLGAME_CONCRETESTATEGAME_H

#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
class ConcreteStateGame : public GameState{
public:

     void draw(MainCharacter &mainCharacter) override ;
     void update(MainCharacter &mainCharacter) override;
     void handleInput(MainCharacter &mainCharacter) override;

     explicit ConcreteStateGame(Game* game);

private:
    void PauseGame();
};

#endif
