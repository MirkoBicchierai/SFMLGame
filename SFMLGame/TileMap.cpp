#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "config.cpp"

void TileMap::load(const std::string& tileSet, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int widthTmp, unsigned int heightTmp, sf::RenderWindow &window){
    texture.loadFromFile(tileSet);
    width=widthTmp;
    height=heightTmp;
    world_map=new int[width*height];
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
                type = "water";
            if((top>=topMinWall && top<=topMaxWall) ||(left==128 && top==64*18))
                type = "wall";
            if(top==topFloor)
                type="floor";
            if((top==topLeverSingle && left==leftLeverSingle) || (top==topLever && (left>=leftMinLever && left<=leftMaxLever)))
                type="lever";
            if(top>=topMinDoorClosed_silver && top<=topMaxDoorClosed_silver && left>=leftMinDoorClosed_silver && left<=leftMaxDoorClosed_silver)
                type = "closed_door_silver";
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

            world_map[i + j * width]=0;

            if(type=="wall"||type=="water" || type=="closed_door_silver" || type=="closed_door_gold" || type=="gate")
                world_map[i + j * width]=9;

            tile.emplace_back(Tile(tileNumber, type, i, j));
            n=tile.size();
            tile[n-1].setTile(texture, tileSize);

        }
    }
}

void TileMap::updateMapAStar() {
    for (int k = 0; k < tile.size(); ++k) {
        world_map[tile[k].i + tile[k].j * width]=0;
        if(tile[k].type=="wall" || tile[k].type=="water" || tile[k].type=="closed_door_silver" || tile[k].type=="closed_door_gold"){
            world_map[tile[k].i + tile[k].j * width]=9;
        }
    }
}

