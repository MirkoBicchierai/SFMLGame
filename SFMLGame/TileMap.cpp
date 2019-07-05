#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "config.cpp"
void TileMap::load(const std::string& tileSet, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height, sf::RenderWindow &window){
    texture.loadFromFile(tileSet);
    int n=0;
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

            int tileNumber = tiles[i + j * width];
            int tv = tileNumber / (texture.getSize().x / tileSize.x);
            int top=tv * tileSize.y;
            if(top>=topMin && top<=topMax)
                tile.emplace_back(Tile(tileNumber,"wall"));
            else
                tile.emplace_back(Tile(tileNumber,"floor"));

            n=tile.size();
            tile[n-1].setTile(i, j, texture, tileSize);
        }
    }
}
