#include "Enemy.h"
#include "config.cpp"
void Enemy::drawEnemy(sf::RenderWindow &window) {
    window.draw(entitySprite);
}

 Enemy::Enemy(float x, float y) {
    entityTexture.loadFromFile("../img/npc/npc1.png");
    entitySprite.setTexture(entityTexture);
    sourceRect.left=0;
    sourceRect.top=0;
    sourceRect.width=64;
    sourceRect.height=64;
    entitySprite.setTextureRect(sourceRect);

    entitySprite.setPosition(x,y);
}