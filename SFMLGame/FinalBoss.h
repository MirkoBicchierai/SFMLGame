#ifndef SFMLGAME_FINALBOSS_H
#define SFMLGAME_FINALBOSS_H

#include <SFML/Graphics.hpp>
#include "BaseStatistic.h"
#include "Tile.h"
#include "MainCharacter.h"
#include "TileMap.h"
#include "MapSearchNode.h"
#include "stlastar.h"
#include "Armor.h"
typedef struct {
    int x;
    int y;
}structListBoss;

class FinalBoss : public BaseStatistic{
public:
    bool die;
    bool finish;
    sf::Clock dieClock;
    sf::Sound soundAttack;
    bool aniAttack;
    FinalBoss();
    void drawBoss(sf::RenderWindow &window);
    void checkAStarBoss(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile);
    void moveAStarBoss(std::vector<Tile> &tile,MainCharacter &mainCharacter);
    int animationAttackBoss();
    void takeDamage(int dmg);
    int animationDie();
private:
    int armorPoint;
    Heart heart;
    Armor armor;
    void aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height);
    void moveBoss(char direction,MainCharacter &mainCharacter);
    std::vector<structListBoss> path;
    int damage;
    sf::IntRect dieRect;
    sf::IntRect swordRect;
    sf::SoundBuffer attackBufferSound;
    sf::IntRect sourceRect;
};

#endif
