#include "Coin.h"
#include "config.cpp"
Coin::Coin() {
    value=rand()%10+1;
    textureCoin.loadFromFile(IMG_ROOT"/GUI/coin_gold.png");
    spriteCoin.setTexture(textureCoin);
}

void Coin::setPosition(sf::Sprite enemy) {
    spriteCoin.setPosition(enemy.getPosition().x+16,enemy.getPosition().y+16);
}

void Coin::drawCoin(sf::RenderWindow &window) {
    window.draw(spriteCoin);
}

sf::Sprite Coin::getSprite() {
    return spriteCoin;
}

int Coin::getValue() {
    return value;
}
