#include "Tile.h"

Tile::Tile(int id, std::string ty) {
    idTile=id;
    type=std::move(ty);
}

void Tile::setTile(int i, int j, sf::Texture &txt, sf::Vector2u tileSize) {
    spriteShow.setPosition(i*tileSize.x, j*tileSize.y);
    sourceRect.top=tileSize.x*int(idTile/8);
    sourceRect.left=tileSize.x*int(idTile%8);
    sourceRect.width=tileSize.x;
    sourceRect.height=tileSize.y;
    spriteShow.setTextureRect(sourceRect);
    spriteShow.setTexture(txt);

    spriteCollision.setPosition(i*tileSize.x, j*tileSize.y);
    if(type=="wall") {
        if (idTile == 43 || idTile == 44 || idTile == 45 || idTile == 37 || idTile == 29)
            spriteCollision.setPosition(spriteShow.getPosition().x + tileSize.x,
                                        spriteShow.getPosition().y + tileSize.y);
    }

    collisionRect.top=tileSize.x*int(idTile/8);
    collisionRect.left=tileSize.x*int(idTile%8);
    collisionRect.width=6;
    collisionRect.height=6;
    spriteCollision.setTextureRect(collisionRect);
    spriteCollision.setTexture(txt);
}

void Tile::drawTile(sf::RenderWindow &window) {
    window.draw(spriteShow);
}
