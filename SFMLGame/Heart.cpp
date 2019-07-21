#include "Heart.h"
#include <SFML/Graphics.hpp>
#include "config.cpp"
#include <iostream>

Heart::Heart() {
    hearthTexture.loadFromFile(IMG_ROOT"/GUI/Heart.png");
    brokenHeart.loadFromFile(IMG_ROOT"/GUI/heartBroke.png");

    hearthSprite1.setTexture(hearthTexture);
    hearthSprite1.setScale(sf::Vector2f(1, 1));
    hearthSprite1.setPosition(1088-35,5);

    hearthSprite2.setTexture(hearthTexture);
    hearthSprite2.setScale(sf::Vector2f(1, 1));
    hearthSprite2.setPosition(1088-35-32-5,5);

    hearthSprite3.setTexture(hearthTexture);
    hearthSprite3.setScale(sf::Vector2f(1, 1));
    hearthSprite3.setPosition(1088-35-(32*2)-(5*2),5);
}
void Heart:: drawHeart(sf::RenderWindow &window){
    window.draw(hearthSprite1);
    window.draw(hearthSprite2);
    window.draw(hearthSprite3);
}

void Heart::moveHeart(float x,float y){
    hearthSprite1.move(x,y);
    hearthSprite2.move(x,y);
    hearthSprite3.move(x,y);
}

void Heart::setCenter(sf::RenderWindow &window,sf::Sprite player) {
    hearthSprite1.setPosition(player.getPosition().x + window.getSize().x / 2.f-35 +32,5 +player.getPosition().y - window.getSize().y / 2.f +32);
    hearthSprite2.setPosition(player.getPosition().x + window.getSize().x / 2.f-35-32-5 +32,5+player.getPosition().y - window.getSize().y / 2.f +32);
    hearthSprite3.setPosition(player.getPosition().x + window.getSize().x / 2.f-35-(32*2)-(5*2) +32,5+player.getPosition().y - window.getSize().y / 2.f +32);
}

void Heart::damageControl(int life) {
    if(life==2){
        hearthSprite1.setTexture(hearthTexture);
        hearthSprite1.setScale(hearthSprite1.getScale().x,hearthSprite1.getScale().y);
        hearthSprite2.setTexture(hearthTexture);
        hearthSprite2.setScale(hearthSprite2.getScale().x,hearthSprite2.getScale().y);
        hearthSprite3.setTexture(brokenHeart);
        hearthSprite3.setScale(hearthSprite3.getScale().x,hearthSprite3.getScale().y);
    }
    if(life==1){
        hearthSprite1.setTexture(hearthTexture);
        hearthSprite1.setScale(hearthSprite1.getScale().x,hearthSprite1.getScale().y);
        hearthSprite2.setTexture(brokenHeart);
        hearthSprite2.setScale(hearthSprite2.getScale().x,hearthSprite2.getScale().y);
        hearthSprite3.setTexture(brokenHeart);
        hearthSprite3.setScale(hearthSprite3.getScale().x,hearthSprite3.getScale().y);
    }
    if(life<=0){
        hearthSprite1.setTexture(brokenHeart);
        hearthSprite1.setScale(hearthSprite1.getScale().x,hearthSprite1.getScale().y);
        hearthSprite2.setTexture(brokenHeart);
        hearthSprite2.setScale(hearthSprite2.getScale().x,hearthSprite2.getScale().y);
        hearthSprite3.setTexture(brokenHeart);
        hearthSprite3.setScale(hearthSprite3.getScale().x,hearthSprite3.getScale().y);
    }
}

void Heart::reset() {
    hearthSprite1.setTexture(hearthTexture);
    hearthSprite1.setScale(sf::Vector2f(1, 1));

    hearthSprite2.setTexture(hearthTexture);
    hearthSprite2.setScale(sf::Vector2f(1, 1));

    hearthSprite3.setTexture(hearthTexture);
    hearthSprite3.setScale(sf::Vector2f(1, 1));
}

void Heart::setHearthEnemy(sf::Vector2f enemy) {
    hearthSprite1.setScale(sf::Vector2f(0.5, 0.5));
    hearthSprite1.setPosition(enemy.x+8,enemy.y-10);

    hearthSprite2.setScale(sf::Vector2f(0.5, 0.5));
    hearthSprite2.setPosition(enemy.x+16+8,enemy.y-10);

    hearthSprite3.setScale(sf::Vector2f(0.5, 0.5));
    hearthSprite3.setPosition(enemy.x+16+16+8,enemy.y-10);
}
