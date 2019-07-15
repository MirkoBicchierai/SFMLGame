#ifndef TEST2_MAINCHARACTER_H
#define TEST2_MAINCHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Arrow.h"
#include "Heart.h"
#include "FireBall.h"
#include "BaseStatistic.h"
#include "Tile.h"

class MainCharacter: public BaseStatistic {

public:

    sf::Sound soundArrow;
    sf::Sound soundFireBall;
    sf::Sound soundSword;

    FireBall ball;
    Arrow arrowPlayer;
    sf::View camera;

    //bool attributes for check the state of the player animation used on the calling method
    bool finalDie;
    bool die;
    int arrow;
    bool shield;
    bool spell;
    bool aniArrow;

    //time for ability
    float timeSword;
    float timeBow;
    float timeMagic;
    float secShield;

    int DMGSword;
    int sword;
    int magic;
    int bow;

    explicit MainCharacter(sf::RenderWindow &window);
    void drawPlayer(sf::RenderWindow &window,sf::Clock clockShield);
    void movePlayer(char direction,sf::RenderWindow &window,std::vector<Tile>tile); // move the player
    int bowAttack(); //animation bow
    int swordAttack(); //animation sword
    int magicAttack(); // animation spell
    void setTextureBow(); //change texture to use bow
    void setTextureShield(); //change texture to use shield
    void setNormalTexture(); //reset texture
    void reset(int pos); // reset the player position
    void resetPlayer(sf::RenderWindow &window); //reset the player state
    void damageSword(std::vector<Enemy*> &enemyVec);
    int dieAnimation(); //animation die
    sf::IntRect getsourceRect();
    sf::Sprite getSprite();
    void takeDamage(int damage);

private:

    sf::Clock soundStepClock;
    sf::Sound soundStep;
    sf::SoundBuffer bufferSword;
    sf::SoundBuffer bufferArrow;
    sf::SoundBuffer bufferFireBall;
    sf::SoundBuffer bufferStep;
    sf::Font font;
    sf::Text textTimeShield;

    Arrow arrowGUI;
    sf::Text textArrow;
    Heart hearth;

    sf::Texture textureGUIShield;
    sf::Sprite shieldSprite;
    sf::IntRect sourceRect;
    sf::Texture bowTexture;
    sf::IntRect dieRect;
    sf::Texture shieldTexture;
    sf::IntRect bowRect;
    sf::IntRect swordRect;
    sf::IntRect magicRect;

    void moveGUI(float x, float y,sf::RenderWindow &window); // move gui of player
    bool controlMove(std::vector<Tile> &tile,char direction); // control if the player can move or not
    void soundStepControl(); // control timing for play the step track


};

#endif
