#ifndef SFMLGAME_TILEMAP_H
#define SFMLGAME_TILEMAP_H
#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable{

public:

    void load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif