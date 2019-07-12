#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "MainCharacter.h"

class GameState;

class Game{
public:
    Game();
    void pushState(GameState* state); //for change state
    GameState* CurrentState(); // return the current concrete state
    void gameLoop(); //general method for call all virtual method of GameState
    sf::Event event{};

    // global variable for all concrete state
    sf::RenderWindow window;
    sf::Clock clockShield;
    sf::Clock clockSword;
    sf::Clock clockBow;
    sf::Clock clockSpell;
    sf::Clock enemyAStar;
    sf::Clock enemyAStarMove;
    sf::Clock diePlayer;
    bool init;
private:
    std::vector<GameState*> states;
};

#endif