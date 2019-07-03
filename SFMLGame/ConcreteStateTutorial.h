#ifndef SFMLGAME_CONCRETESTATETUTORIAL_H
#define SFMLGAME_CONCRETESTATETUTORIAL_H

#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class ConcreteStateTutorial: public GameState {
public:

    void draw(MainCharacter &mainCharacter) override ;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    explicit ConcreteStateTutorial(Game* game);

private:
    void backToMenu();
};


#endif
