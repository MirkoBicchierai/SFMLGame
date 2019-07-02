#include "ConcreteStateTutorial.h"
#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
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
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
                this->game->window.close();
                break;

                //pause game
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    PauseGame();
                break;

        }
    }


}

ConcreteStateTutorial::ConcreteStateTutorial(Game* game)
{
    this->game = game;
}

void ConcreteStateTutorial::PauseGame()
{


}