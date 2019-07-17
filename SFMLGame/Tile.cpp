#include "Tile.h"

Tile::Tile(int id, std::string ty,int i, int j) {
    idTile=id;
    type=std::move(ty);
    this->i=i;
    this->j=j;
}

void Tile::setTile(sf::Texture &txt, sf::Vector2u tileSize) {

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

    collisionRect.width = tileSize.x;
    collisionRect.height = tileSize.y;
    spriteCollision.setPosition(i*tileSize.x, j*tileSize.y);
    spriteCollision.setTextureRect(collisionRect);
    spriteCollision.setTexture(txt);
}

void Tile::drawTile(sf::RenderWindow &window) {
    window.draw(spriteShow);
}

bool Tile::checkInteract() {
    if(type=="lever"||type=="gold_key" || type=="silver_key")
        return true;
    else
        return false;
}
