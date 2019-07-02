#ifndef SFMLGAME_CONCRETESTATEGAME_H
#define SFMLGAME_CONCRETESTATEGAME_H

#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
class ConcreteStateGame : public GameState{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

     explicit ConcreteStateGame(Game* game);

private:
    void PauseGame();
};

#endif
