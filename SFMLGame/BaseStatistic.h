#ifndef SFMLGAME_BASESTATISTIC_H
#define SFMLGAME_BASESTATISTIC_H

#include <SFML/Graphics.hpp>

class BaseStatistic { //dad class for Enemy and MainCharacter
public:
    int life;
    float moveSpeed;
    sf::Texture entityTexture;
    sf::Sprite entitySprite;
    sf::RectangleShape AStarColl;
private:
};

#endif
