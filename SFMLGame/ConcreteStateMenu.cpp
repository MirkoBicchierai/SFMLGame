#include "ConcreteStateMenu.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "ConcreteStateMenu.h"
#include"GameState.h"
#include "ConcreteStateGame.h"

ConcreteStateMenu::ConcreteStateMenu(Game* game){
    this->game = game;
}

void ConcreteStateMenu::handleInput()
{
    sf::Event event;

    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
                game->window.close();
                break;

                /* Change Between game states */
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    game->window.close();
                else if (event.key.code == sf::Keyboard::Return)
                    loadgame();
                break;


        }
    }

}

void ConcreteStateMenu::update(float dt)
{

}

void ConcreteStateMenu::draw(float dt)
{

}

void ConcreteStateMenu::loadgame()
{
    game->pushState(new ConcreteStateGame(game));
}
