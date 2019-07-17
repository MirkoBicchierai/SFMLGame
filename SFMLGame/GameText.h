#ifndef SFMLGAME_GAMETEXT_H
#define SFMLGAME_GAMETEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainCharacter.h"
class GameText {
public:
    void setGameText(std::string text,sf::Sprite &sprite);
    GameText()= default;
    GameText(std::string text,MainCharacter &mainCharacter);
    void moveText(MainCharacter &mainCharacter);
    void drawGameText(sf::RenderWindow &window);
    void checkString();
private:
    float dimension;
    sf::Clock advanceText;
    std::string text;
    sf::Text drawText;
    sf::Font font;
};

#endif
