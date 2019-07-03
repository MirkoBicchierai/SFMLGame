#include <iostream>
#include <SFML/Graphics.hpp>
#include "ConcreteStateTutorial.h"
#include "ConcreteStateMenu.h"
#include "GameState.h"

void ConcreteStateTutorial::draw(MainCharacter &mainCharacter){
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(100, 100));
    rect.setSize(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Green);
    game->window.draw(rect);
}

void ConcreteStateTutorial::update(MainCharacter &mainCharacter){

}

void ConcreteStateTutorial::handleInput(MainCharacter &mainCharacter){

    sf::Event event{};
    while (game->window.pollEvent(event)){

        if (event.type == sf::Event::Closed)
            game->window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            backToMenu();
    }

}

ConcreteStateTutorial::ConcreteStateTutorial(Game* game){
    this->game = game;
}

void ConcreteStateTutorial::backToMenu(){
    game->pushState(new ConcreteStateMenu(game));
}