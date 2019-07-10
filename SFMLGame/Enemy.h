#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include "BaseStatistic.h"
#include <iostream>
#include "MapSearchNode.h"
#include "stlastar.h"
#include <stdio.h>
#include <math.h>
#include "MainCharacter.h"

typedef struct {
    int x;
    int y;
}structList;

class Enemy : public BaseStatistic {

public:
    Enemy(float x, float y);
    void drawEnemy(sf::RenderWindow &window);
    void checkAStar(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile);
    void moveAStar(std::vector<Tile> &tile);
private:
    void aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height);
    void moveEnemy(char direction);
    std::vector<structList> path;
    sf::IntRect sourceRect;

};

#endif
