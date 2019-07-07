#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "MainCharacter.h"

class GameState;

class Game{
public:
    Game();
    void pushState(GameState* state);
    GameState* CurrentState();
    void gameLoop();

    sf::RenderWindow window;
    sf::Clock clockShield;
    sf::Clock clockSword;
    sf::Clock clockBow;
    sf::Clock clockSpell;
    bool init;
private:
    std::vector<GameState*> states;
};

#endif