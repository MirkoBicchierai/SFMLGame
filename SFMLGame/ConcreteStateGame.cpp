#include "ConcreteStateGame.h"
#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"


void ConcreteStateGame::draw(const float dt)
{
    //for shits and giggles let's draw a rectangle to make sure this works.
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(100, 100));
    rect.setSize(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Green);

    game->window.draw(rect);

}

void ConcreteStateGame::update(const float dt)
{

}

void ConcreteStateGame::handleInput()
{
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

ConcreteStateGame::ConcreteStateGame(Game* game)
{
    this->game = game;
}

void ConcreteStateGame::PauseGame()
{


}
