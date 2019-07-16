#ifndef SFMLGAME_FIREBALL_H
#define SFMLGAME_FIREBALL_H

#include <SFML/Graphics.hpp>
class MainCharacter;
class Enemy;
class FireBall {
public:
    bool animationBall;
    sf::Clock clock;
    FireBall();
    void drawFireBall(sf::RenderWindow &window);
    void setRect(sf::IntRect player,float x, float y);
    int animation(std::vector<Enemy*> &enemyVec,MainCharacter &mainCharacter); //animation fireball, switch rect of image

private:
    int damage;
    int moveSpeed;
    sf::IntRect ballRect;
    sf::Texture ballTexture;
    sf::Sprite ballSprite;
};

#endif //SFMLGAME_FIREBALL_H
