#include "Tile.h"

Tile::Tile(int id, std::string ty) {
    idTile=id;
    type=std::move(ty);
    playerUp=false;
}

void Tile::setTile(int i, int j, sf::Texture &txt, sf::Vector2u tileSize) {

    int tu = idTile % (txt.getSize().x / tileSize.x);
    int tv = idTile / (txt.getSize().x / tileSize.x);
    spriteShow.setPosition(i*tileSize.x, j*tileSize.y);
    sourceRect.top=tv * tileSize.y;
    sourceRect.left=tu * tileSize.x;

    sourceRect.width=tileSize.x;
    sourceRect.height=tileSize.y;
    spriteShow.setTextureRect(sourceRect);
    spriteShow.setTexture(txt);

    collisionRect.top=tv * tileSize.y;
    collisionRect.left=tu * tileSize.x;
    if(type=="gate" || type=="closed_door_gold" || type=="closed_door_silver" ) {
        collisionRect.width = tileSize.x;
        collisionRect.height = tileSize.y-32;
        spriteCollision.setPosition(i*tileSize.x, j*tileSize.y+32);
    }else{
        collisionRect.width = tileSize.x;
        collisionRect.height = tileSize.y;
        spriteCollision.setPosition(i*tileSize.x, j*tileSize.y);
    }
    spriteCollision.setTextureRect(collisionRect);
    spriteCollision.setTexture(txt);
}

void Tile::drawTile(sf::RenderWindow &window) {
    window.draw(spriteShow);
}
