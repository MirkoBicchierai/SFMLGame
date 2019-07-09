#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <SFML/Graphics.hpp>
class Tile {
public:
    int i,j;
    sf::Sprite spriteShow;
    sf::Sprite spriteCollision;
    Tile()= default;
    Tile(int id, std::string ty,int i, int j);
    std::string type;
    int idTile;
    void setTile(sf::Texture &txt, sf::Vector2u tileSize);
    void drawTile(sf::RenderWindow &window);

private:
    sf::IntRect sourceRect;
    sf::IntRect collisionRect;
};

#endif
