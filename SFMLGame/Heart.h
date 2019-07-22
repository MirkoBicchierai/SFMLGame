#ifndef SFMLGAME_HEART_H
#define SFMLGAME_HEART_H

#include <SFML/Graphics.hpp>

class Heart {
public:
    Heart();
    void drawHeart(sf::RenderWindow &window);
    void moveHeart(float x,float y); //move hearth of the gui
    void setCenter(sf::RenderWindow &window,sf::Sprite player); //reset position
    void damageControl(int life);
    void reset();
    void setHearthEnemy(sf::Vector2f enemy);
    void setHearthBoss(sf::Vector2f boss);
private:
    sf::Texture brokenHeart;
    sf::Texture hearthTexture;
    sf::Sprite hearthSprite1;
    sf::Sprite hearthSprite2;
    sf::Sprite hearthSprite3;
};


#endif
