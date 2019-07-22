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
    bool aniAttack;
    sf::Clock dieClock;
    sf::Sound soundAttack;

    FinalBoss();
    void drawBoss(sf::RenderWindow &window);
    void checkAStarBoss(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile);
    void moveAStarBoss(std::vector<Tile> &tile,MainCharacter &mainCharacter);
    int animationAttackBoss();
    void takeDamage(int dmg);
    int animationDie();
    void doDamagePlayer(MainCharacter &mainCharacter);

private:
    int armorPoint;
    int damage;
    std::vector<structListBoss> path;
    Heart heart;
    Armor armor;
    sf::IntRect dieRect;
    sf::IntRect swordRect;
    sf::IntRect sourceRect;
    sf::SoundBuffer attackBufferSound;
    void aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height);
    void moveBoss(char direction,MainCharacter &mainCharacter);
};

#endif
