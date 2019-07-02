#ifndef SFMLGAME_CONCRETESTATEMENU_H
#define SFMLGAME_CONCRETESTATEMENU_H

#include "GameState.h"
#include "Menu.h"

class ConcreteStateMenu : public GameState{

public:
    explicit ConcreteStateMenu(Game* game);
    void draw(MainCharacter &mainCharacter) override;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;

private:
    Menu menu;
    void startGame(MainCharacter &mainCharacter);
    void startTutorial(MainCharacter &mainCharacter);
};

#endif