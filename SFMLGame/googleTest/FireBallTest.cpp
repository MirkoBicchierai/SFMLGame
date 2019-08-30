#include "gtest/gtest.h"
#include "../FireBall.h"
#include "../MainCharacter.h"
#include "../Enemy.h"

TEST(FireBall, DamageFireBall) {
    FireBall fireball;
    sf::RenderWindow window;
    MainCharacter mainCharacter(window
    );
    std::vector<Enemy*> enemyVec;

    float x=0,y=0;
    std::string file;

    for (int i = 0; i < 10; ++i) {
        x=rand()%(64*20) + 64*5;
        y=rand()%(64*20) + 64*5;
        file="normal";
        enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    }
    x=64;
    y=50;
    file="normal";
    enemyVec.emplace_back(new Enemy(x,y,file,600,1));

    mainCharacter.entitySprite.setPosition(64,64);
    fireball.setRect(mainCharacter.getsourceRect(),mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
    fireball.animation(enemyVec,mainCharacter,NULL);
    ASSERT_EQ(2,enemyVec.back()->life);
}
