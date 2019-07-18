#include "Inventory.h"
#include "config.cpp"
Inventory::Inventory() {
    NumberGold=0;
    NumberSilverKey=0;
    NumberGoldKey=0;

    coinTexture.loadFromFile(IMG_ROOT"/GUI/coin_gold.png");
    silverKeyTexture.loadFromFile(IMG_ROOT"/GUI/Gold_Key.png");
    goldKeyTexture.loadFromFile(IMG_ROOT"/GUI/Silver_Key.png");

    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");

    coinSprite.setTexture(coinTexture);
    goldKeySprite.setTexture(goldKeyTexture);
    silverKeySprite.setTexture(silverKeyTexture);

    coinText.setFont(font);
    silverKeyText.setFont(font);
    goldKeyText.setFont(font);

    goldKeyText.setFillColor(sf::Color::White);
    silverKeyText.setFillColor(sf::Color::White);
    coinText.setFillColor(sf::Color::White);

    coinText.setScale(0.7,0.7);
    silverKeyText.setScale(0.7,0.7);
    goldKeyText.setScale(0.7,0.7);
}

void Inventory::moveDrawInventory(sf::Sprite player,sf::RenderWindow &window) {

    goldKeyText.setString("x"+std::to_string(NumberGoldKey));
    silverKeyText.setString("x"+std::to_string(NumberSilverKey));
    coinText.setString("x"+std::to_string(NumberGold));

    coinSprite.setPosition(player.getPosition().x+window.getSize().x/2,player.getPosition().y-192);
    goldKeySprite.setPosition(player.getPosition().x+window.getSize().x/2,player.getPosition().y-192 +32 +32 +5 +5);
    silverKeySprite.setPosition(player.getPosition().x+window.getSize().x/2,player.getPosition().y -192 +32 +5);

    goldKeyText.setPosition(goldKeySprite.getPosition().x-32,player.getPosition().y -192 +32 +5+5);
    silverKeyText.setPosition(silverKeySprite.getPosition().x-32,player.getPosition().y-192 +32 +32 +5 +5 +5);
    coinText.setPosition(coinSprite.getPosition().x-32,coinSprite.getPosition().y+5);

    window.draw(coinSprite);
    window.draw(goldKeySprite);
    window.draw(silverKeySprite);

    window.draw(goldKeyText);
    window.draw(silverKeyText);
    window.draw(coinText);
}
