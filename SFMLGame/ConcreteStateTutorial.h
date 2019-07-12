#ifndef SFMLGAME_CONCRETESTATETUTORIAL_H
#define SFMLGAME_CONCRETESTATETUTORIAL_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "TileMap.h"
#include "Enemy.h"
#include "Event.h"
class ConcreteStateTutorial: public GameState {
public:
    void draw(MainCharacter &mainCharacter) override ;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    void Init() override;
    explicit ConcreteStateTutorial(Game* game);

private:
    Event loopEvent;
    std::vector <Enemy*> enemyVec;  //vector dei nemici presenti nel Tutorial
    TileMap map{};  // object map connected to a object Tile for draw the map
    std::vector <int> vec; //vector dove vengono letti gli ID da file della mappa e poi passati all'oggetto map
    void loadFromFile(const std::string &path);
};


#endif
