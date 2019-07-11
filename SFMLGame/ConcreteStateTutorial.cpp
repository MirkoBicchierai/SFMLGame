#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConcreteStateTutorial.h"
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "Enemy.h"
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
   map.load(MAP_ROOT"/tile-set.png", sf::Vector2u(64, 64), vec, c, r,game->window);
}

void ConcreteStateTutorial::draw(MainCharacter &mainCharacter){

    for(auto i:map.tile){
        i.drawTile(game->window);
    }
    for(auto i:enemyVec){
        i->drawEnemy(game->window);
    }
    mainCharacter.drawPlayer(game->window,game->clockShield);
}

void ConcreteStateTutorial::update(MainCharacter &mainCharacter){
    if(!mainCharacter.die){
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
                mainCharacter.soundArrow.play();
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
                mainCharacter.soundFireBall.play();
                mainCharacter.magic = 0;
                mainCharacter.reset(mainCharacter.getsourceRect().top);
                mainCharacter.ball.animationBall=true;
                mainCharacter.ball.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
            }
            game->clockSpell.restart();
        }
    }
    //animation fireball
    if (mainCharacter.ball.animationBall && mainCharacter.ball.clock.getElapsedTime().asMilliseconds() >= 55.f) {
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
                mainCharacter.arrowPlayer.animation(map.tile);
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
    //A-star Enemy
    if(game->enemyAStar.getElapsedTime().asMilliseconds()>=500.f) {
        for (auto &i:enemyVec) {
            i->checkAStar(map, mainCharacter, map.tile);
        }
        game->enemyAStar.restart();
    }

    if(game->enemyAStarMove.getElapsedTime().asMilliseconds()>=15.f) {
        for (auto &i:enemyVec) {
            i->moveAStar(map.tile,mainCharacter);
        }
        game->enemyAStarMove.restart();
    }
    }
    if(mainCharacter.die && mainCharacter.AnimationDie  && mainCharacter.checkDie){
        if (game->diePlayer.getElapsedTime().asMilliseconds() > 45.f) {
            if(mainCharacter.dieAnimation()==aniDieMax){
                mainCharacter.AnimationDie=false;
            }
            game->diePlayer.restart();
        }
    }
}

void ConcreteStateTutorial::handleInput(MainCharacter &mainCharacter){

    sf::Event event{};
    while (this->game->window.pollEvent(event)){

        if (event.type == sf::Event::Closed)
            game->window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            backToMenu();

        if(!mainCharacter.die){
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
        } else{
            mainCharacter.checkDie=true;
        }
    }
}

ConcreteStateTutorial::ConcreteStateTutorial(Game* game){
    this->game = game;
}

void ConcreteStateTutorial::backToMenu(){
    game->init=false;
    game->pushState(new ConcreteStateMenu(game));
}

void ConcreteStateTutorial::Init() {
    loadFromFile(MAP_ROOT_TUTORIAL"/Tutorial.txt");
    float x=0,y=0;
    for (int i = 0; i < 10; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        enemyVec.push_back(new Enemy(x,y));
    }
    game->init=true;

}


