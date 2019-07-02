#ifndef SFMLGAME_CONCRETESTATEMENU_H
#define SFMLGAME_CONCRETESTATEMENU_H

#include "GameState.h"

class ConcreteStateMenu : public GameState{

public:
    explicit ConcreteStateMenu(Game* game);
    void draw(float dt) override;
    void update(float dt) override;
    void handleInput() override;

private:
    sf::View view;
    void loadgame();
};

#endif