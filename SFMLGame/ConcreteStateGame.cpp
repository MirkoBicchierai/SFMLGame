#include "ConcreteStateGame.h"
#include "ConcreteStateMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"


void ConcreteStateGame::draw(MainCharacter &mainCharacter)
{
    mainCharacter.drawPlayer(game->window,game->clockShield);
}

void ConcreteStateGame::update(MainCharacter &mainCharacter){
    //fine tempo scudo
    if (mainCharacter.shield && game->clockShield.getElapsedTime().asSeconds() >= mainCharacter.secShield) {
        mainCharacter.setNormalTexture();
        mainCharacter.shield = false;
    }
    //animazione spada
    if (mainCharacter.sword == 1) {
        if (game->clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            if (mainCharacter.swordAttack() == 64 * 5) {
                mainCharacter.sword = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
            }
            game->clockSword.restart();
        }
    }
    //animazione bow
    if (mainCharacter.bow == 1) {
        if (game->clockBow.getElapsedTime().asMilliseconds() >= mainCharacter.timeBow ) {
            if (mainCharacter.bowAttack() == 64 * 12) {
                mainCharacter.bow = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.arrow = mainCharacter.arrow - 1;
                mainCharacter.arrowPlayer.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y );
                mainCharacter.arrowPlayer.animationArrow = true;
                mainCharacter.arrowPlayer.ciclo = 0;
                mainCharacter.arrowPlayer.stay = true;
            }
            game->clockBow.restart();
        }
    }
    //animazione spell-cast
    if (mainCharacter.magic == 1) {
        if ( game->clockMagick.getElapsedTime().asMilliseconds() >= mainCharacter.timeMagic ) {
            if (mainCharacter.magicAttack() == 64 * 6) {
                mainCharacter.magic = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.ball.animationBall=true;
                mainCharacter.ball.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
            }
            game->clockMagick.restart();
        }
    }
    //animazione fireball
    if (mainCharacter.ball.animationBall && mainCharacter.ball.clock.getElapsedTime().asMilliseconds() >= 40.f) {
        if (mainCharacter.ball.animation() == 64 * 7) {
            mainCharacter.ball.animationBall = false;
            mainCharacter.spell = false;
        }
        mainCharacter.ball.clock.restart();
    }
    //animazione arrow
    if (mainCharacter.arrowPlayer.animationArrow) {
        if (mainCharacter.arrowPlayer.ciclo < 8) {
            if (mainCharacter.arrowPlayer.clock.getElapsedTime().asMilliseconds() > 45.f) {
                mainCharacter.arrowPlayer.animation();
                mainCharacter.arrowPlayer.clock.restart();
                mainCharacter.arrowPlayer.ciclo++;
            }
        } else {
            mainCharacter.arrowPlayer.pick = true;
            mainCharacter.arrowPlayer.animationArrow = false;
            mainCharacter.aniArrow = false;
        }

    }
    //ripresa della freccia a terra
    if (mainCharacter.getSprite().getGlobalBounds().intersects(mainCharacter.arrowPlayer.arrowSprite.getGlobalBounds()) &&
        mainCharacter.arrowPlayer.pick) {
        mainCharacter.arrowPlayer.pick = false;
        mainCharacter.arrowPlayer.stay = false;
        mainCharacter.arrow = 1;
    }
}

void ConcreteStateGame::handleInput(MainCharacter &mainCharacter)
{
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->window.close();
        //muovimento del player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mainCharacter.movePlayer('u',game->window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mainCharacter.movePlayer('d',game->window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mainCharacter.movePlayer('l',game->window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mainCharacter.movePlayer('r',game->window);
        }
        //attacco con spada del player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mainCharacter.shield) {
            mainCharacter.sword = 1;
            game->clockSword.restart();
        } else {
            //attacco con arco del player
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mainCharacter.arrow > 0 &&
                !mainCharacter.shield &&
                !mainCharacter.aniArrow) {
                mainCharacter.setTextureBow();
                mainCharacter.bow = 1;
                mainCharacter.aniArrow = true;
                mainCharacter.arrowPlayer.clock.restart();
                game->clockBow.restart();
            } else {
                // attacco SPECIALE del player
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !mainCharacter.shield &&
                    !mainCharacter.spell) {
                    mainCharacter.magic = 1;
                    game->clockMagick.restart();
                    mainCharacter.spell = true;
                } else {
                    // attivazione scudo player
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mainCharacter.spell) {
                        mainCharacter.setTextureShield();
                        game->clockShield.restart();
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game->pushState(new ConcreteStateMenu(game));
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
