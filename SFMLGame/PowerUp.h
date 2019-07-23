#ifndef SFMLGAME_POWERUP_H
#define SFMLGAME_POWERUP_H

#include <SFML/Graphics.hpp>

class PowerUp {
public:
    PowerUp();
    void moveRight();
    void moveLeft();
    int getSelectedItem();
    void draw(sf::RenderWindow &window);
private:
    int selectedItem;
    sf::Texture textureBackground;
    sf::Sprite background;
};

#endif
