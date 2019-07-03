#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
void TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height, sf::RenderWindow &window){

    texture.loadFromFile(tileset);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            int tileNumber = tiles[i + j * width];
            if(tileNumber==27 || tileNumber==28 || tileNumber==29|| tileNumber==37 || tileNumber==35 ||tileNumber==43 ||tileNumber==44 || tileNumber==45)
                tile.emplace_back(tileNumber,"wall");
            else
                tile.emplace_back(tileNumber,"floor");
                (--tile.end())->setTile(i, j, texture, tileSize);
        }
    }
}
