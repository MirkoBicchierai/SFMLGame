#ifndef SFMLGAME_ARMOR_H
#define SFMLGAME_ARMOR_H

#include <SFML/Graphics.hpp>
class Armor {
public:
    Armor();
    void drawArmor(sf::RenderWindow &window);
    void moveArmor(float x, float y);
    void setPosition(sf::Sprite boss);
    void damageControl(int armor);
private:
    sf::Texture textureArmor;
    sf::Sprite ArmorSprite1;
    sf::Sprite ArmorSprite2;
    sf::Sprite ArmorSprite3;
};

#endif