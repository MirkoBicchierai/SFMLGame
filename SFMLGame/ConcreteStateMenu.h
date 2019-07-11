#ifndef SFMLGAME_CONCRETESTATEMENU_H
#define SFMLGAME_CONCRETESTATEMENU_H

#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Menu.h"

class ConcreteStateMenu : public GameState{

public:
    explicit ConcreteStateMenu(Game* game);
    void draw(MainCharacter &mainCharacter) override;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    void Init() override;

private:
    Menu menu;
    void startGame(MainCharacter &mainCharacter); //switch state to Game
    void startTutorial(MainCharacter &mainCharacter);  //switch state to Tutorial
};

#endif