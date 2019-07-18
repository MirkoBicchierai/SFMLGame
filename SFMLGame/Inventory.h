#ifndef SFMLGAME_INVENTORY_H
#define SFMLGAME_INVENTORY_H

#include <SFML/Graphics.hpp>

class Inventory {
public:
    Inventory();
    void moveDrawInventory(sf::Sprite,sf::RenderWindow &window);
    int NumberSilverKey;
    int NumberGoldKey;
    int NumberGold;
private:
    sf::Sprite coinSprite;
    sf::Sprite goldKeySprite;
    sf::Sprite silverKeySprite;

    sf::Texture coinTexture;
    sf::Texture goldKeyTexture;
    sf::Texture silverKeyTexture;

    sf::Font font;
    sf::Text coinText;
    sf::Text goldKeyText;
    sf::Text silverKeyText;
};

#endif
