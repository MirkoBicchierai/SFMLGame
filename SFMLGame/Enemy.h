#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include <iostream>
#include "BaseStatistic.h"
#include "MapSearchNode.h"
#include "stlastar.h"
#include "MainCharacter.h"
#include "TileMap.h"
#include "Heart.h"
typedef struct {
    int x;
    int y;
}structList;

class Enemy : public BaseStatistic {

public:
    sf::Sound soundAttack;
    sf::Clock dieClock;
    sf::Clock idleClock;
    bool aniAttack;
    bool idle;
    int damage;
    Enemy(float x, float y,std::string &file,int distance,int dmg);
    void drawEnemy(sf::RenderWindow &window);
    void checkAStar(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile);
    void moveAStar(std::vector<Tile> &tile,MainCharacter &mainCharacter);
    float animationDie();
    void attackPlayer(MainCharacter &mainCharacter);
    int animationAttack(int x);
    int animationIdle();
    void takeDamage(int dmg);
    std:: string type;
private:
    Heart lifeHearth;
    sf::SoundBuffer attackBufferSound;
    sf::IntRect IdleRect;
    sf::IntRect dieRect;
    sf::IntRect swordRect;
    int aggroDistance;
    void aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height);
    void moveEnemy(char direction,MainCharacter &mainCharacter);
    std::vector<structList> path;
    sf::IntRect sourceRect;
    void soundStepControl(); // control timing for play the step track
    sf::Clock soundStepClock;
    sf::Sound soundStep;
    sf::SoundBuffer bufferStep;
};

#endif
