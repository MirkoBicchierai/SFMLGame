#include "FireBall.h"
#include <SFML/Graphics.hpp>
#include <iostream>

FireBall::FireBall() {
    ballTexture.loadFromFile("../img/Player_obj/FireBall.png");
    ballSprite.setTexture(ballTexture);
    ballRect.height = 64;
    ballRect.width = 64;
    ballRect.left = 0;
    ballSprite.setTextureRect(ballRect);
    moveSpeed=20;
    animationBall=false;
}

void FireBall::drawFireBall(sf::RenderWindow &window) {
    window.draw(ballSprite);
}
void FireBall::setRect(sf::IntRect player,float x, float y) {
    if (player.top == 64 * 11) {
        ballRect.top = 64 * 4;
    }
    if (player.top == 64 * 10) {
        ballRect.top = 64 * 6;
    }
    if (player.top == 64 * 9) {
        ballRect.top = 64 * 0;
    }
    if (player.top == 64 * 8) {
        ballRect.top = 64 * 2;
    }
    ballRect.left=0;
    clock.restart();
    ballSprite.setTextureRect(ballRect);
    ballSprite.setPosition(x,y);
}

int FireBall::animation() {
    if (ballRect.top == 64 * 4) {
        ballSprite.move(moveSpeed,0);
    }
    if (ballRect.top == 64 * 6) {
        ballSprite.move(0,moveSpeed);
    }
    if (ballRect.top == 64 * 0) {
        ballSprite.move(-moveSpeed,0);
    }
    if (ballRect.top == 64 * 2) {
        ballSprite.move(0,-moveSpeed);
    }

    ballRect.left=ballRect.left+64;

    return ballRect.left;
}