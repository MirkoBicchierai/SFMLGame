#ifndef SFMLGAME_ARROW_H
#define SFMLGAME_ARROW_H
#include <SFML/Graphics.hpp>
#include "Tile.h"
class Enemy;
class FinalBoss;
class Arrow {
public:
    sf::Sprite arrowSprite;
    sf::Clock clock;
    bool pick;   //used for pick the arrow by player
    bool stay;  //arrow on floor
    int arrowFor;  //number of for the animation bow
    bool animationArrow;  //if animation arrow is started
    Arrow();
    void setArrowGUI(float X, float Y, float rotation);  //lock a arrow for the GUI
    void drawArrow(sf::RenderWindow &window);
    void setRect(sf::IntRect player,float x, float y);
    void animation(std::vector<Tile> &tile,std::vector<Enemy*> &enemyVec,FinalBoss* boss);  //arrow animation , and collision with wall
private:
    int damage;
    bool controlMove(std::vector<Tile> &tile); //control move of arrow
    int moveSpeed; //arrow speed
    sf::Color colorSprite;
    sf::IntRect arrowRect;
    sf::Texture arrowTexture;
};


#endif
