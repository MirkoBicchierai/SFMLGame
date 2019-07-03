#include <utility>
#include "Tile.h"

Tile::Tile(int id, std::string ty) {
    idTile=id;
    type=std::move(ty);
}

void Tile::setTile(int i, int j, sf::Texture &txt, sf::Vector2u tileSize) {
    tl.setPosition(i*tileSize.x, j*tileSize.y);
    sourceRect.top=tileSize.x*int(idTile/8);
    sourceRect.left=tileSize.x*int(idTile%8);
    sourceRect.width=tileSize.x;
    sourceRect.height=tileSize.y;
    tl.setTextureRect(sourceRect);
    tl.setTexture(txt);
}

void Tile::drawTile(sf::RenderWindow &window) {
    window.draw(tl);
}
