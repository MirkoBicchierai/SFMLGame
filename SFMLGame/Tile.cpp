#include "Tile.h"

Tile::Tile(int id, std::string ty) {
    idTile=id;
    type=std::move(ty);
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

    spriteCollision.setPosition(i*tileSize.x, j*tileSize.y);

    collisionRect.top=tv * tileSize.y;
    collisionRect.left=tu * tileSize.x;
    collisionRect.width=6;
    collisionRect.height=6;
    spriteCollision.setTextureRect(collisionRect);
    spriteCollision.setTexture(txt);
}

void Tile::drawTile(sf::RenderWindow &window) {
    window.draw(spriteShow);
}
