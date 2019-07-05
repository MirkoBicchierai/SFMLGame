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
            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);
            int top=tv * tileSize.y;
            int left =tu * tileSize.x;

            std::string type="obj";

            if(top>=topMinWater && top<=topMaxWater)
                type="water";
            if(top>=topMinWall && top<=topMaxWall)
                type="wall";
            if(top==topFloor)
                type="floor";
            if( (top>=topChestMin && top<=topChestMax && left>=leftChestMin) || (top==topSingleChest && left==leftSingleChest) )
                type="chest";
            if((top==topLeverSingle && left==leftLeverSingle) || (top==topLever && left>=leftMinLever &&left<=leftMaxLever) )
                type="lever";
            if(top>=topMinDoorClosed_silver && top<=topMaxDoorClosed_silver && left>=leftMinDoorClosed_silver && left<=leftMaxDoorClosed_silver)
                type="closed_door_silver";
            if(top>=topMinDoorClosed_gold && top<=topMaxDoorClosed_gold && left>=leftMinDoorClosed_gold && left<=leftMaxDoorClosed_gold)
                type="closed_door_gold";
            if(top>=topMinDoorOpened && top<=topMaxDoorOpened && left>=leftMinDoorOpened && left<=leftMaxDoorOpened)
                type="opened_door";
            if(left==LeftGate && top>=topMinGate && top <=topMaxGate)
                type="gate";
            if(left==goldKeyLeft && top==goldKeyTop)
                type="gold_key";
            if(left==silverKeyLeft && top==silverKeyTop)
                type="silver_key";

            tile.emplace_back(Tile(tileNumber, type));
            n=tile.size();
            tile[n-1].setTile(i, j, texture, tileSize);
        }
    }
}
