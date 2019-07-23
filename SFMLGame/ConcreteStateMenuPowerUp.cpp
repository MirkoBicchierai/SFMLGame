#include "ConcreteStateMenuPowerUp.h"
#include "SFML/Graphics.hpp"

ConcreteStateMenuPowerUp::ConcreteStateMenuPowerUp(Game* game,GameState* x){
    newState=x;
    this->game = game;
}

void ConcreteStateMenuPowerUp::handleInput(MainCharacter &mainCharacter){
    sf::Event event{};
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            game->window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            game->pushState(newState);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            menu.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            menu.moveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {  //GESTIONE SELEZIONE ITEM DAL MENU
            if (menu.getSelectedItem() == 2)
                game->window.close();
            if (menu.getSelectedItem() == 1){

            }
            if (menu.getSelectedItem() == 0){

            }
        }
    }
}

void ConcreteStateMenuPowerUp::update(MainCharacter &mainCharacter){

}

void ConcreteStateMenuPowerUp::draw(MainCharacter &mainCharacter){
    menu.draw(game->window);
}

void ConcreteStateMenuPowerUp::Init(MainCharacter &mainCharacter) {
    mainCharacter.camera.setCenter(game->window.getSize().x / 2.f, game->window.getSize().y / 2.f);
    game->window.setView(mainCharacter.camera);
    game->init=false;
}