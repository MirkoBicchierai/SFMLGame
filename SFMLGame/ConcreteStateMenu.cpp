#include "SFML/Graphics.hpp"
#include "ConcreteStateMenu.h"
#include "ConcreteStateGame.h"
#include "ConcreteStateTutorial.h"
#include "config.cpp"

ConcreteStateMenu::ConcreteStateMenu(Game* game){
    this->game = game;
}

void ConcreteStateMenu::handleInput(MainCharacter &mainCharacter){
    sf::Event event{};
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
    if(game->Achievement->map.size()==totAch) {
        game->Achievement->addAchievement("Platinum","Plat.png");
    }
}

void ConcreteStateMenu::draw(MainCharacter &mainCharacter){
    menu.draw(game->window);
}

void ConcreteStateMenu::startGame(MainCharacter &mainCharacter){ // switch state to Game
    game->init=false;
    mainCharacter.resetStatistic();
    auto x =new ConcreteStateGame(game);
    x->actualLevel=1;
    game->pushState(x);
}

void ConcreteStateMenu::startTutorial(MainCharacter &mainCharacter) { // switch state to tutorial
    game->init=false;
    game->pushState(new ConcreteStateTutorial(game));
}

void ConcreteStateMenu::Init(MainCharacter &mainCharacter) {
    game->init=false;
    mainCharacter.camera.setCenter(game->window.getSize().x / 2.f, game->window.getSize().y / 2.f);
    game->window.setView(mainCharacter.camera);
}
