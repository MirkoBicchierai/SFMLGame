#ifndef SFMLGAME_GAMESTATE_H
#define SFMLGAME_GAMESTATE_H

#include "Game.h"
class GameState{
public:
    GameState()= default;
    Game* game;
    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void handleInput() = 0;
};

#endif
