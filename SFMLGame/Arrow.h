#ifndef SFMLGAME_ARROW_H
#define SFMLGAME_ARROW_H
#include <SFML/Graphics.hpp>

class Arrow {
public:
    sf::Sprite arrowSprite;
    sf::Clock clock;
    bool pick;
    bool stay;
    int arrowFor;
    bool animationArrow;
    Arrow();
    void setArrowGUI(float X, float Y, float rotation);
    void drawArrow(sf::RenderWindow &window);
    void setRect(sf::IntRect player,float x, float y);
    void animation();
private:
    int moveSpeed;
    sf::Color colorSprite;
    sf::IntRect arrowRect;
    sf::Texture arrowTexture;
};


#endif
