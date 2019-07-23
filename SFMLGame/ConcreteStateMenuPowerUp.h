#ifndef SFMLGAME_CONCRETESTATEMENUPOWERUP_H
#define SFMLGAME_CONCRETESTATEMENUPOWERUP_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "PowerUp.h"

class ConcreteStateMenuPowerUp : public GameState {
public:
    GameState* newState;
    explicit ConcreteStateMenuPowerUp(Game* game,GameState* x);
    void draw(MainCharacter &mainCharacter) override;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    void Init(MainCharacter &mainCharacter) override;
private:
    PowerUp menu;
};

#endif
