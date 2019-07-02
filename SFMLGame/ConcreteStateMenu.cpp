#include "ConcreteStateMenu.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "ConcreteStateMenu.h"
#include"GameState.h"
#include "ConcreteStateGame.h"
#include "Menu.h"
#include "ConcreteStateTutorial.h"

ConcreteStateMenu::ConcreteStateMenu(Game* game){
    this->game = game;
}

void ConcreteStateMenu::handleInput(MainCharacter &mainCharacter){
    sf::Event event{};
    mainCharacter.camera.setCenter(game->window.getSize().x / 2.f, game->window.getSize().y / 2.f);
    game->window.setView(mainCharacter.camera);
    while (game->window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            game->window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            menu.moveUp();
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                menu.moveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (menu.getSelectedItem() == 2)
                game->window.close();
            else {
                if (menu.getSelectedItem() == 1)
                    startTutorial(mainCharacter);
                else {
                    if (menu.getSelectedItem() == 0)
                        startGame(mainCharacter);
                }
            }
        }
    }

}

void ConcreteStateMenu::update(MainCharacter &mainCharacter){

}

void ConcreteStateMenu::draw(MainCharacter &mainCharacter){
    menu.draw(game->window);
}

void ConcreteStateMenu::startGame(MainCharacter &mainCharacter){
    mainCharacter.camera.setCenter((mainCharacter.getSprite().getPosition().x) + 32,((mainCharacter.getSprite().getPosition().y)) + 32);
    game->window.setView(mainCharacter.camera);
    game->pushState(new ConcreteStateGame(game));
}

void ConcreteStateMenu::startTutorial(MainCharacter &mainCharacter) {
    game->pushState(new ConcreteStateTutorial(game));
}
