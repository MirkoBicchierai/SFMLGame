#ifndef SFMLGAME_CONCRETESTATEGAME4_H
#define SFMLGAME_CONCRETESTATEGAME4_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileMap.h"
#include "Event.h"
#include "Coin.h"

class ConcreteStateGame4 : public GameState{

public:

    void draw(MainCharacter &mainCharacter) override ;
    void update(MainCharacter &mainCharacter) override;
    void handleInput(MainCharacter &mainCharacter) override;
    void Init(MainCharacter &mainCharacter) override;
    explicit ConcreteStateGame4(Game* game);

private:
    std::vector<Coin*> coinVec;
    std::vector <Enemy*> enemyVec;
    Event loopEvent;
    TileMap map{};
    std::vector <int> vec; //vector dove vengono letti gli ID da file della mappa e poi passati all'oggetto map
    void loadFromFile(const std::string &path);  //metodo per leggere gli id da FILE

};

#endif
