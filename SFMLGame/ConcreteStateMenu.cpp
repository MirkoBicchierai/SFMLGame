#include "SFML/Graphics.hpp"
#include "ConcreteStateMenu.h"
#include "ConcreteStateGame3.h"
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            menu.moveDown();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {  //GESTIONE SELEZIONE ITEM DAL MENU
            if (menu.getSelectedItem() == 2)
                game->window.close();
            if (menu.getSelectedItem() == 1)
                startTutorial(mainCharacter);
            if (menu.getSelectedItem() == 0)
                startGame(mainCharacter);
        }
    }
}

void ConcreteStateMenu::update(MainCharacter &mainCharacter){

}

void ConcreteStateMenu::draw(MainCharacter &mainCharacter){
    menu.draw(game->window);
}

void ConcreteStateMenu::startGame(MainCharacter &mainCharacter){ // switch state to Game
    game->init=false;
    game->pushState(new ConcreteStateGame3(game));
}

void ConcreteStateMenu::startTutorial(MainCharacter &mainCharacter) { // switch state to tutorial
    game->init=false;
    game->pushState(new ConcreteStateTutorial(game));
}

void ConcreteStateMenu::Init(MainCharacter &mainCharacter) {

}
