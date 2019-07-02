#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "MainCharacter.h"

class GameState;

class Game{
public:
    Game();
    ~Game();
    void pushState(GameState* state);
    void popState();
    GameState* CurrentState();
    void gameLoop();

    sf::RenderWindow window;
    sf::Clock clockShield;
    sf::Clock clockSword;
    sf::Clock clockBow;
    sf::Clock clockMagick;
private:
    std::vector<GameState*> states;


};

#endif