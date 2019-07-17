#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "MainCharacter.h"
#include "GameText.h"
class GameState;

class Game{
public:
    bool interact;
    int actualInteractI, actualInteractJ;
    GameText interactText;
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
    sf::Clock dieClock;
    bool init;
private:
    std::vector<GameState*> states;
};

#endif