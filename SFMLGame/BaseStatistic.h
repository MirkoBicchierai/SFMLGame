#ifndef SFMLGAME_BASESTATISTIC_H
#define SFMLGAME_BASESTATISTIC_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class BaseStatistic { //dad class for Enemy and MainCharacter
public:
    int life;
    float moveSpeed;
    sf::Sound soundStep;
    sf::SoundBuffer bufferStep;
    sf::Texture entityTexture;
    sf::Sprite entitySprite;
    sf::RectangleShape AStarColl;
    void soundStepControl(); // control timing for play the step track
private:
    sf::Clock soundStepClock;
};

#endif
