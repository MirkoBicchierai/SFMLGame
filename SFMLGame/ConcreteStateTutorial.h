#ifndef SFMLGAME_CONCRETESTATETUTORIAL_H
#define SFMLGAME_CONCRETESTATETUTORIAL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "TileMap.h"

class ConcreteStateTutorial: public GameState {
public:
    bool loadMap=false;
    void draw(MainCharacter &mainCharacter) override ;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    explicit ConcreteStateTutorial(Game* game);

private:
    TileMap map{};
    std::vector <int> vec;
    void backToMenu();
    void loadFromFile(const std::string &path);
};


#endif
