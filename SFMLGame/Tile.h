#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <SFML/Graphics.hpp>
class Tile {
public:
    int i,j; // i and j are the indices of line and column of the vector of id tile
    std::string type; //type of tyle
    int idTile; // id of tile
    sf::Sprite spriteShow;
    sf::Sprite spriteCollision;
    bool end;
    Tile()= default;
    Tile(int id, std::string ty,int i, int j);
    void setTile(sf::Texture &txt, sf::Vector2u tileSize); //set the texture and the draw position of the tile
    void drawTile(sf::RenderWindow &window);
    bool checkInteract();
    void setEnd();

private:
    float factor;
    sf::IntRect sourceRect;
    sf::IntRect collisionRect;
};

#endif
