#ifndef SFMLGAME_MENU_H
#define SFMLGAME_MENU_H

#include <SFML/Graphics.hpp>
#define MAX_NUMBER_ITEMS 3

class Menu {

public:

    Menu(float widht, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItem();
    bool play;
    bool tutorial;

private:

    int selectedItemIndex;
    int sizeSelectedItem;
    int sizeNotSelectedItem;
    sf::Font font;
    sf::Text title;
    sf::Text menu[MAX_NUMBER_ITEMS];
    sf::Texture texture;
    sf::Sprite titleSprite1;
    sf::Sprite titleSprite2;
    sf::Sprite sprite;
    sf::Texture textureBackground;
    sf::Sprite background;

};

#endif //SFMLGAME_MENU_H
