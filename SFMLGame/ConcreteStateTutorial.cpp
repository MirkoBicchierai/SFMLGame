#include <SFML/Graphics.hpp>
#include "ConcreteStateTutorial.h"
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "config.cpp"
#include <fstream>
#include <regex>

void ConcreteStateTutorial::loadFromFile(const std::string &path) {
    std::string s;
    std::ifstream infile(path);
    int c=0;
    int r=0;
    while (std::getline(infile, s)){
        std::regex ws_re(",");
        std::vector<std::string> result{ std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), {}};
        c=0;
        for (const auto & i : result) {
            std::stringstream geek(i);
            int x = 0;
            geek >> x;
            vec.push_back(x);
            c++;
        }
        r++;
    }
   map.load("../map/tileset_map.png", sf::Vector2u(32, 32), vec, c, r,game->window);
}

void ConcreteStateTutorial::draw(MainCharacter &mainCharacter){
    if(!loadMap) {
        loadMap=true;
        loadFromFile("../map/tutorial/tutorial.txt");
    }
    for(auto i:map.tile){
        i.drawTile(game->window);
    }
    mainCharacter.drawPlayer(game->window,game->clockShield);
}

void ConcreteStateTutorial::update(MainCharacter &mainCharacter){
    //time shield end
    if (mainCharacter.shield && game->clockShield.getElapsedTime().asSeconds() >= mainCharacter.secShield) {
        mainCharacter.setNormalTexture();
        mainCharacter.shield = false;
    }
    //animation sword
    if (mainCharacter.sword == 1) {
        if (game->clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            if (mainCharacter.swordAttack() == finalSwordAttack) {
                mainCharacter.sword = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
            }
            game->clockSword.restart();
        }
    }
    //animation bow
    if (mainCharacter.bow == 1) {
        if (game->clockBow.getElapsedTime().asMilliseconds() >= mainCharacter.timeBow ) {
            if (mainCharacter.bowAttack() == finalBowAttack) {
                mainCharacter.bow = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.arrow = mainCharacter.arrow - 1;
                mainCharacter.arrowPlayer.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y );
                mainCharacter.arrowPlayer.animationArrow = true;
                mainCharacter.arrowPlayer.arrowFor = 0;
                mainCharacter.arrowPlayer.stay = true;
            }
            game->clockBow.restart();
        }
    }
    //animation spell-cast
    if (mainCharacter.magic == 1) {
        if ( game->clockSpell.getElapsedTime().asMilliseconds() >= mainCharacter.timeMagic ) {
            if (mainCharacter.magicAttack() == finalMagicAttack) {
                mainCharacter.magic = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.ball.animationBall=true;
                mainCharacter.ball.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
            }
            game->clockSpell.restart();
        }
    }
    //animation fireball
    if (mainCharacter.ball.animationBall && mainCharacter.ball.clock.getElapsedTime().asMilliseconds() >= 40.f) {
        if (mainCharacter.ball.animation() == finalBallAnimation) {
            mainCharacter.ball.animationBall = false;
            mainCharacter.spell = false;
        }
        mainCharacter.ball.clock.restart();
    }
    //animation arrow
    if (mainCharacter.arrowPlayer.animationArrow) {
        if (mainCharacter.arrowPlayer.arrowFor < 8) {
            if (mainCharacter.arrowPlayer.clock.getElapsedTime().asMilliseconds() > 45.f) {
                mainCharacter.arrowPlayer.animation();
                mainCharacter.arrowPlayer.clock.restart();
                mainCharacter.arrowPlayer.arrowFor++;
            }
        } else {
            mainCharacter.arrowPlayer.pick = true;
            mainCharacter.arrowPlayer.animationArrow = false;
            mainCharacter.aniArrow = false;
        }

    }
    //take arrow by floor
    if (mainCharacter.getSprite().getGlobalBounds().intersects(mainCharacter.arrowPlayer.arrowSprite.getGlobalBounds()) &&
        mainCharacter.arrowPlayer.pick) {
        mainCharacter.arrowPlayer.pick = false;
        mainCharacter.arrowPlayer.stay = false;
        mainCharacter.arrow = 1;
    }
}

void ConcreteStateTutorial::handleInput(MainCharacter &mainCharacter){

    sf::Event event{};

    while (this->game->window.pollEvent(event)){

        if (event.type == sf::Event::Closed)
            game->window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            backToMenu();

        //player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mainCharacter.movePlayer('u',game->window,map.tile);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mainCharacter.movePlayer('d',game->window,map.tile);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mainCharacter.movePlayer('l',game->window,map.tile);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mainCharacter.movePlayer('r',game->window,map.tile);
        }

        //sword attack plaYER
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mainCharacter.shield) {
            mainCharacter.sword = 1;
            game->clockSword.restart();
        } else {
            //bow attack player
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mainCharacter.arrow > 0 &&
                !mainCharacter.shield &&
                !mainCharacter.aniArrow) {
                mainCharacter.setTextureBow();
                mainCharacter.bow = 1;
                mainCharacter.aniArrow = true;
                mainCharacter.arrowPlayer.clock.restart();
                game->clockBow.restart();
            } else {
                // special attack player
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !mainCharacter.shield &&
                    !mainCharacter.spell) {
                    mainCharacter.magic = 1;
                    game->clockSpell.restart();
                    mainCharacter.spell = true;
                } else {
                    // activate shield player
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mainCharacter.spell) {
                        mainCharacter.setTextureShield();
                        game->clockShield.restart();
                    }
                }
            }
        }

    }

}

ConcreteStateTutorial::ConcreteStateTutorial(Game* game){
    this->game = game;
}

void ConcreteStateTutorial::backToMenu(){
    game->pushState(new ConcreteStateMenu(game));
}


