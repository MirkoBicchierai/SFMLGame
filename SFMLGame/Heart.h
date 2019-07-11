#ifndef SFMLGAME_HEART_H
#define SFMLGAME_HEART_H

#include <SFML/Graphics.hpp>

class Heart {
public:
    Heart();
    void drawHeart(sf::RenderWindow &window);
    void moveHeart(float x,float y); //move hearth of the gui
    void setCenter(sf::RenderWindow &window); //reset position
private:
    sf::Texture hearthTexture;
    sf::Sprite hearthSprite1;
    sf::Sprite hearthSprite2;
    sf::Sprite hearthSprite3;
};


#endif
