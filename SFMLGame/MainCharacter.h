#ifndef TEST2_MAINCHARACTER_H
#define TEST2_MAINCHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Arrow.h"
#include "Heart.h"
#include "FireBall.h"
#include "BaseStatistic.h"
#include <iostream>
#include "Tile.h"
#include <vector>

class MainCharacter: public BaseStatistic {

public:

    sf::Sound soundArrow;
    sf::Sound soundFireBall;

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
    void movePlayer(char direction,sf::RenderWindow &window,std::vector<Tile>tile);
    int bowAttack();
    int swordAttack();
    int magicAttack();
    void setTextureBow();
    void setTextureShield();
    void setNormalTexture();
    void reset(int pos);
    void resetPlayer(sf::RenderWindow &window);
    sf::Sprite getSprite();
    bool controlMove(std::vector<Tile> &tile,char direction);
private:
    sf::SoundBuffer bufferArrow;
    sf::SoundBuffer bufferFireBall;
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

    void moveGUI(float x, float y,sf::RenderWindow &window);

};

#endif
