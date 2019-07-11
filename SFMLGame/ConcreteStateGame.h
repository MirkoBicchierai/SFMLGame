#ifndef SFMLGAME_CONCRETESTATEGAME_H
#define SFMLGAME_CONCRETESTATEGAME_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileMap.h"

class ConcreteStateGame : public GameState{
public:

     void draw(MainCharacter &mainCharacter) override ;
     void update(MainCharacter &mainCharacter) override;
     void handleInput(MainCharacter &mainCharacter) override;
     void Init() override;
     explicit ConcreteStateGame(Game* game);

private:
    TileMap map{};
    std::vector <int> vec; //vector dove vengono letti gli ID da file della mappa e poi passati all'oggetto map
    void backToMenu();
    void loadFromFile(const std::string &path);  //metodo per leggere gli id da FILE
};

#endif
