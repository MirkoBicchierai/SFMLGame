#include "gtest/gtest.h"
#include "../Arrow.h"
#include "../MainCharacter.h"
#include "../Enemy.h"
#include "../Tile.h"

TEST(Arrow, DamageArrow) {

    Arrow arrow;
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    std::vector<Tile> tile;
    float x=0,y=0;
    std::string file;

    for (int i = 0; i < 10; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="normal";
        enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    }
    x=64;
    y=50;
    file="normal";
    enemyVec.emplace_back(new Enemy(x,y,file,600,1));

    mainCharacter.entitySprite.setPosition(64,64);
    arrow.setRect(mainCharacter.getsourceRect(),mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
    arrow.animation(tile,enemyVec);
    ASSERT_EQ(1,enemyVec.back()->life);
}