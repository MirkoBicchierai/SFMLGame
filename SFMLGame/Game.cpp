#include "SFML/Graphics.hpp"
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "Game.h"
#include "config.cpp"
Game::Game(){
    init=false;
    window.create(sf::VideoMode(1088, 704), TITLE, sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - window.getSize().x / 2,(sf::VideoMode::getDesktopMode().height / 2) - window.getSize().y / 2);
    window.setPosition(centerWindow);
    sf::Image icon;
    icon.loadFromFile(IMG_ROOT"/GUI/Sword.png");
    window.setIcon(32,32,icon.getPixelsPtr());
    window.setFramerateLimit(60);
    interact=false;
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

        if(!init)
           CurrentState()->Init(mainCharacter);
        if (CurrentState() == nullptr)
            break;

        CurrentState()->handleInput(mainCharacter);
        Achievement->updateAchievement();
        CurrentState()->update(mainCharacter);
        window.clear();
        CurrentState()->draw(mainCharacter);
        Achievement->drawVectorAchievement(window,mainCharacter);
        window.display();
    }

}


