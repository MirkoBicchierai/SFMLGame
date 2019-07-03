#ifndef TEST2_MAINCHARACTER_H
#define TEST2_MAINCHARACTER_H

#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "Heart.h"
#include "FireBall.h"
#include "BaseStatistic.h"
#include <iostream>

class MainCharacter: public BaseStatistic {

public:

    FireBall ball;
    Arrow arrowPlayer;
    sf::View camera;

    int arrow;
    bool shield;
    bool spell;
    bool aniArrow;

    float timeSword;
    float timeBow;
    float timeMagic;

    int sword;
    int magic;
    int bow;
    float secShield;
    explicit MainCharacter(sf::RenderWindow &window);
    sf::IntRect getsourceRect();
    void drawPlayer(sf::RenderWindow &window,sf::Clock clockShield);
    void movePlayer(char direction,sf::RenderWindow &window);
    int bowAttack();
    int swordAttack();
    int magicAttack();
    void setTextureBow();
    void setTextureShield();
    void setNormalTexture();
    void reset(int pos);
    sf::Sprite getSprite();

private:
    void moveGUI(float x,float y,sf::RenderWindow &window);
    sf::Font font;
    sf::Text textTimeShield;

    Arrow arrowGUI;
    sf::Text textArrow;
    Heart hearth;

    sf::Texture textureGUIShield;
    sf::Sprite shieldSprite;
    sf::IntRect sourceRect;
    sf::Texture bowTexture;
    sf::Texture shieldTexture;
    sf::IntRect bowRect;
    sf::IntRect swordRect;
    sf::IntRect magicRect;

};

#endif
