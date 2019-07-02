#ifndef SFMLGAME_GAMESTATE_H
#define SFMLGAME_GAMESTATE_H

#include "Game.h"
#include "MainCharacter.h"
class GameState{
public:
    GameState()= default;
    Game* game;
    virtual void draw(MainCharacter &mainCharacter) = 0;
    virtual void update(MainCharacter &mainCharacter) = 0;
    virtual void handleInput(MainCharacter &mainCharacter) = 0;
};

#endif
