#ifndef SFMLGAME_TILEMAP_H
#define SFMLGAME_TILEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "MainCharacter.h"

class TileMap{

public:
    int width; //map width
    int height; // map height
    int *world_map; // vector of id for A-star
    std::vector<Tile> tile; // vector of all tile in the current map
    void load(const std::string& tileSet, sf::Vector2u tileSize,std::vector<int> tiles, unsigned int width, unsigned int height, sf::RenderWindow &window); // load all object Tile of the map by a vector
private:

    sf::Texture texture;

};


#endif