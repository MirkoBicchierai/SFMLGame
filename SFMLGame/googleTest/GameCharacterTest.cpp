#include "gtest/gtest.h"
#include "../MainCharacter.h"
#include "../Enemy.h"
#include "../Tile.h"
#include "../config.cpp"

sf::RenderWindow window;
MainCharacter mainCharacter(window);

TEST(MainCharacter, animationSwordTest) {
    int x=0;
    int correct=0;
    std::vector<Enemy*> enemyVec;
    sf::Clock clockSword;
    while(x != finalSwordAttack){
        if (clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            x=mainCharacter.swordAttack();
            correct=correct+dim;
            ASSERT_EQ(x,correct);
            if (x == finalSwordAttack) {
                ASSERT_EQ(finalSwordAttack,x);
                mainCharacter.damageSword(enemyVec); // final damage sword
                mainCharacter.sword = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
            }
            clockSword.restart();
        }
    }
    ASSERT_EQ(0,mainCharacter.sword);
}

TEST(MainCharacter, animationBowTest) {
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

}