#include "gtest/gtest.h"
#include "../MainCharacter.h"
#include "../Enemy.h"
#include "../Tile.h"
#include "../config.cpp"

TEST(MainCharacter, animationSwordTest) {
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    int x=0;
    int correct=0;
    sf::Clock clockSword;
    while(x != finalSwordAttack){
        if (clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            x=mainCharacter.swordAttack();
            correct=correct+dim;
            ASSERT_EQ(x,correct);
            if (x == finalSwordAttack) {
                ASSERT_EQ(finalSwordAttack,x);
                mainCharacter.damageSword(enemyVec,NULL); // final damage sword
                mainCharacter.sword = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
            }
            clockSword.restart();
        }
    }
    ASSERT_EQ(0,mainCharacter.sword);
}

TEST(MainCharacter, animationBowTest) {
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    sf::Clock clockBow;
    int x=0;
    int correct=0;
    while (x != finalBowAttack) {
        if (clockBow.getElapsedTime().asMilliseconds() >= mainCharacter.timeBow ) {
            x=mainCharacter.bowAttack();
            correct=correct+dim;
            ASSERT_EQ(x,correct);
            if (x == finalBowAttack) {
                ASSERT_EQ(finalBowAttack,x);
                mainCharacter.bow =0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.arrow --;
                mainCharacter.arrowPlayer.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y );
                mainCharacter.arrowPlayer.animationArrow = true;
                mainCharacter.arrowPlayer.arrowFor = 0;
                mainCharacter.arrowPlayer.stay = true;
            }
           clockBow.restart();
        }
    }

    ASSERT_TRUE(mainCharacter.arrowPlayer.stay);
    ASSERT_TRUE(mainCharacter.arrowPlayer.animationArrow);
    ASSERT_EQ(0,mainCharacter.arrow);
}

TEST(MainCharacter, animationCastTest) {
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    sf::Clock clockSpell;
    int x=0;
    int correct=0;
    while (x != finalMagicAttack) {
        if ( clockSpell.getElapsedTime().asMilliseconds() >= mainCharacter.timeMagic ) {
            x=mainCharacter.magicAttack();
            correct=correct+dim;
            ASSERT_EQ(x,correct);
            if (x == finalMagicAttack) {
                ASSERT_EQ(finalMagicAttack,x);
                mainCharacter.magic = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.ball.animationBall=true;
                mainCharacter.ball.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
            }
            clockSpell.restart();
        }
    }
    ASSERT_TRUE(mainCharacter.ball.animationBall);
}

TEST(MainCharacter, DamageSword){
    sf::RenderWindow window;
    MainCharacter mainCharacter(window);
    std::vector<Enemy*> enemyVec;
    float x=0,y=0;
    std::string file;
    for (int i = 0; i < 10; ++i) {
        x=rand()%(64*20) + 64*5;
        y=rand()%(64*20) + 64*5;
        file="normal";
        enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    }
    x=72;
    y=-5;
    file="normal";
    enemyVec.emplace_back(new Enemy(x,y,file,600,1));
    mainCharacter.entitySprite.setPosition(64,10);
    ASSERT_EQ(mainCharacter.getSprite().getPosition().x,64);
    mainCharacter.damageSword(enemyVec,NULL);
    ASSERT_EQ(3-mainCharacter.DMGSword,enemyVec.back()->life);
}