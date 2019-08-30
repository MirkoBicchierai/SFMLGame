#include "gtest/gtest.h"
#include "../MainCharacter.h"
#include "../Enemy.h"

TEST(Enemy, EnemyTakeDamge) {
    std::vector<Enemy*> enemyVec;
    int x, y;
    std::string file="normal";
    for (int i = 0; i < 10; ++i) {
        x=rand()%(64*20) + 64*5;
        y=rand()%(64*20) + 64*5;
        enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    }
    for (int j = 0; j < enemyVec.size(); ++j) {
        enemyVec[j]->takeDamage(1);
        ASSERT_EQ(2,enemyVec[j]->life);
    }
}

TEST(Enemy, AttackPlayer) {
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    int x, y;
    std::string file="normal";
    for (int i = 0; i < 10; ++i) {
        x=rand()%(64*20) + 64*5;
        y=rand()%(64*20) + 64*5;
        enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    }
    x=64;
    y=70;
    mainCharacter.entitySprite.setPosition(64,0);
    enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    enemyVec.back()->attackPlayer(mainCharacter);
    ASSERT_EQ(2,mainCharacter.life);
}
