#ifndef SFMLGAME_POWERUP_H
#define SFMLGAME_POWERUP_H
#define MAX_NUMBER_POWER_UP 5

#include <SFML/Graphics.hpp>
#include "MainCharacter.h"

class PowerUp {
public:
    int priceSpeed,priceSword,priceArrow,priceFireBall;
    PowerUp();
    void moveRight();
    void moveLeft();
    int getSelectedItem();
    void draw(sf::RenderWindow &window, MainCharacter &player);
    bool IncrementSpeedPlayer(MainCharacter &player);
    bool IncrementDamageSwordPlayer(MainCharacter &player);
    bool IncrementDamageFireBallPlayer(MainCharacter &player);
    bool IncrementDamageArrowPlayer(MainCharacter &player);
private:
    int sizeSelectedItem;
    int sizeNotSelectedItem;
    int selectedItem;
    sf::Sprite ImagePowerUp[MAX_NUMBER_POWER_UP];
    sf::Sprite Coin[MAX_NUMBER_POWER_UP-1];
    sf::Text CoinText[MAX_NUMBER_POWER_UP-1];
    sf::Text textLine[MAX_NUMBER_POWER_UP];
    sf::Texture textureBackground;
    sf::Sprite background;

    sf::Font font;
    sf::Text title;
    sf::Texture speed;
    sf::Texture swordDamage;
    sf::Texture arrowDamage;
    sf::Texture fireBallDamage;
    sf::Texture nextTxt;
    sf::Texture coinTexture;

    sf::Text playerCoin;
};

#endif
