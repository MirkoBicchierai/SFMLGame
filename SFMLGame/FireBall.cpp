#include <SFML/Graphics.hpp>
#include "FireBall.h"
#include "config.cpp"
#include "Enemy.h"
#include "MainCharacter.h"
#include "FinalBoss.h"
FireBall::FireBall() {
    ballTexture.loadFromFile(IMG_PLAYER_OBJ_ROOT"/FireBall.png");
    ballSprite.setTexture(ballTexture);
    ballRect.height = dimFireBall;
    ballRect.width = dimFireBall;
    ballRect.left = NormalLeft;
    ballSprite.setTextureRect(ballRect);
    moveSpeed=45;
    animationBall=false;
    damage=1;
}

void FireBall::drawFireBall(sf::RenderWindow &window) {
    window.draw(ballSprite);
}

void FireBall::setRect(sf::IntRect player,float x, float y) {
    if (player.top == topMoveRight) {
        ballRect.top = RightFireBall;
    }
    if (player.top == topMoveDown) {
        ballRect.top = DownFireBall;
    }
    if (player.top == topMoveLeft) {
        ballRect.top = LeftFireBall;
    }
    if (player.top == topMoveUp) {
        ballRect.top = UpFireBall;
    }
    ballRect.left=NormalLeft;
    clock.restart();
    ballSprite.setTextureRect(ballRect);
    ballSprite.setPosition(x,y);
}

int FireBall::animation(std::vector<Enemy*> &enemyVec,MainCharacter &mainCharacter,FinalBoss* boss) {
    if (ballRect.top == RightFireBall) {
        ballSprite.move(moveSpeed,0);
    }
    if (ballRect.top == DownFireBall) {
        ballSprite.move(0,moveSpeed);
    }
    if (ballRect.top == LeftFireBall) {
        ballSprite.move(-moveSpeed,0);
    }
    if (ballRect.top == UpFireBall) {
        ballSprite.move(0,-moveSpeed);
    }

    ballRect.left=ballRect.left+dim;
    for (int i = 0; i < enemyVec.size(); ++i) {
       if(ballSprite.getGlobalBounds().intersects(enemyVec[i]->entitySprite.getGlobalBounds())){
           if(enemyVec[i]->life!=0) {
               enemyVec[i]->takeDamage(damage);
               animationBall=false;
               mainCharacter.spell=false;
               break;
           }
       }
    }
    if(boss!=NULL){
        if(ballSprite.getGlobalBounds().intersects(boss->entitySprite.getGlobalBounds())){
            if(boss->life!=0) {
                boss->takeDamage(damage);
                animationBall=false;
                mainCharacter.spell=false;
            }
        }
    }
    return ballRect.left;
}