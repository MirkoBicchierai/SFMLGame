#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include "BaseStatistic.h"
#include <iostream>
#include "MapSearchNode.h"
#include "stlastar.h"
#include <stdio.h>
#include <math.h>
#include "MainCharacter.h"

class Enemy : public BaseStatistic {
public:
    Enemy(float x, float y);
    void drawEnemy(sf::RenderWindow &window);
    void aStarSearch(Tile tilePlayer,Tile tileEnemy,int *map,int width,int height);
private:
    sf::IntRect sourceRect;
};

#endif
