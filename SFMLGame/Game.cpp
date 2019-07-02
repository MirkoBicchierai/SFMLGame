#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Game.h"

Game::Game(){
    window.create(sf::VideoMode(1088, 704), "The road of Knight", sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - window.getSize().x / 2,(sf::VideoMode::getDesktopMode().height / 2) - window.getSize().y / 2);
    window.setPosition(centerWindow);
    sf::Image icon;
    icon.loadFromFile("../img/GUI/Sword.png");
    window.setIcon(32,32,icon.getPixelsPtr());
    window.setFramerateLimit(60);
}
void Game::pushState(GameState* state){
    states.push_back(state);
}

void Game::popState(){
    states.back();
    delete states.back();
    states.pop_back();
}

Game::~Game(){
    while (!states.empty())
        popState();
}

GameState* Game::CurrentState(){
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::gameLoop(){
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (CurrentState() == nullptr)
            continue;

        //get user input for current game state
        CurrentState()->handleInput();

        //update anything neccessary
        CurrentState()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        CurrentState()->draw(dt);

        window.display();
    }
}