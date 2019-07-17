#ifndef SFMLGAME_GAMESTATE_H
#define SFMLGAME_GAMESTATE_H

#include "Game.h"
#include "MainCharacter.h"
//interface
class GameState{
public:
    GameState()= default;
    Game* game{};

    //all virtual method that override in the concrete state of game
    virtual void draw(MainCharacter &mainCharacter) = 0;
    virtual void update(MainCharacter &mainCharacter) = 0;
    virtual void handleInput(MainCharacter &mainCharacter) = 0;
    virtual void Init(MainCharacter &mainCharacter) = 0;
};

#endif
