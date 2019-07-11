#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include <iostream>
#include "BaseStatistic.h"
#include "MapSearchNode.h"
#include "stlastar.h"
#include "MainCharacter.h"
#include "TileMap.h"
typedef struct {
    int x;
    int y;
}structList;

class Enemy : public BaseStatistic {

public:
    Enemy(float x, float y);
    void drawEnemy(sf::RenderWindow &window);
    void checkAStar(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile);
    void moveAStar(std::vector<Tile> &tile,MainCharacter &mainCharacter);
private:
    void aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height);
    void moveEnemy(char direction,MainCharacter &mainCharacter);
    std::vector<structList> path;
    sf::IntRect sourceRect;

};

#endif
