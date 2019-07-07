#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include "BaseStatistic.h"
#include <iostream>

class Enemy : public BaseStatistic {
public:
    Enemy(float x, float y);
    void drawEnemy(sf::RenderWindow &window);

private:
    sf::IntRect sourceRect;
};

#endif
