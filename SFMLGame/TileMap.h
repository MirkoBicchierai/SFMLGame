#ifndef SFMLGAME_TILEMAP_H
#define SFMLGAME_TILEMAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "MainCharacter.h"
class TileMap{

public:
    int width;
    int height;
    int *world_map;
    std::vector<Tile> tile;
    void load(const std::string& tileSet, sf::Vector2u tileSize,std::vector<int> tiles, unsigned int width, unsigned int height, sf::RenderWindow &window);
private:

    sf::Texture texture;

};


#endif