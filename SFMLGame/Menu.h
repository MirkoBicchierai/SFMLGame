#ifndef SFMLGAME_MENU_H
#define SFMLGAME_MENU_H
#define MAX_NUMBER_ITEMS_MENU 3

#include <SFML/Graphics.hpp>

class Menu {

public:

    Menu();
    void draw(sf::RenderWindow &window);
    void moveUp(); // scroll up the menu
    void moveDown(); // scroll down the menu
    int getSelectedItem(); // return the item selected after click return

private:

    int selectedItemIndex;
    int sizeSelectedItem;
    int sizeNotSelectedItem;
    sf::Font font;
    sf::Text title;
    sf::Text menu[MAX_NUMBER_ITEMS_MENU];
    sf::Texture texture;
    sf::Sprite titleSprite1;
    sf::Sprite titleSprite2;
    sf::Sprite sprite;
    sf::Texture textureBackground;
    sf::Sprite background;

};

#endif
