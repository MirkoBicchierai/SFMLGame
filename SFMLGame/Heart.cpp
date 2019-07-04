#include "Heart.h"
#include <SFML/Graphics.hpp>
#include "config.cpp"

Heart::Heart() {
    hearthTexture.loadFromFile(IMG_ROOT"/GUI/Heart.png");

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

void Heart::setCenter(sf::RenderWindow &window) {
    hearthSprite1.setPosition(window.getSize().x-35,5);
    hearthSprite2.setPosition(window.getSize().x-35-32-5,5);
    hearthSprite3.setPosition(window.getSize().x-35-(32*2)-(5*2),5);
}
