#ifndef SFMLGAME_TILEMAP_H
#define SFMLGAME_TILEMAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"

class TileMap{

public:
    sf::Texture texture;
    std::vector<Tile> tile;
    void load(const std::string& tileSet, sf::Vector2u tileSize,std::vector<int> tiles, unsigned int width, unsigned int height, sf::RenderWindow &window);

};


#endif