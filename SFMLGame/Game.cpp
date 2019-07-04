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

GameState* Game::CurrentState(){
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::gameLoop(){
    MainCharacter mainCharacter(window);
    while (window.isOpen()){
        if (CurrentState() == nullptr)
            continue;

        CurrentState()->handleInput(mainCharacter);
        CurrentState()->update(mainCharacter);
        window.clear();
        CurrentState()->draw(mainCharacter);
        window.display();
    }
}