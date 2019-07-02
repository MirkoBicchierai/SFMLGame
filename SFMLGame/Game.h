#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <vector>
#include "SFML/Graphics.hpp"

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

private:
    std::vector<GameState*> states;


};

#endif