#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Tile {
public:
    sf::Sprite spriteShow;
    sf::Sprite spriteCollision;
    sf::IntRect sourceRect;
    sf::IntRect collisionRect;
    Tile(int id, std::string ty);
    std::string type;
    int idTile;
    void setTile(int i,int j, sf::Texture &txt, sf::Vector2u tileSize);
    void drawTile(sf::RenderWindow &window);
};

#endif
