#ifndef SFMLGAME_COIN_H
#define SFMLGAME_COIN_H

#include <SFML/Graphics.hpp>

class Coin {
public:
    Coin();
    void setPosition(sf::Sprite enemy);
    void drawCoin(sf::RenderWindow &window);
    sf::Sprite getSprite();
    int getValue();
private:
    int value;
    sf::Texture textureCoin;
    sf::Sprite spriteCoin;
};

#endif
