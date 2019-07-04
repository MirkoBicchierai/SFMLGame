#include <SFML/Graphics.hpp>
#include "FireBall.h"
#include "config.cpp"

FireBall::FireBall() {
    ballTexture.loadFromFile(IMG_PLAYER_OBJ_ROOT"/FireBall.png");
    ballSprite.setTexture(ballTexture);
    ballRect.height = dimFireBall;
    ballRect.width = dimFireBall;
    ballRect.left = NormalLeft;
    ballSprite.setTextureRect(ballRect);
    moveSpeed=20;
    animationBall=false;
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

int FireBall::animation() {
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

    return ballRect.left;
}