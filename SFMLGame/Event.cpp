#include <utility>

#include "Event.h"
#include "config.cpp"
#include "ConcreteStateMenu.h"

void Event::updateEvent(MainCharacter &mainCharacter,Game* game,TileMap &map, std::vector<Enemy*> &enemyVec) {
    //time shield end
    if (mainCharacter.shield && game->clockShield.getElapsedTime().asSeconds() >= mainCharacter.secShield) {
        mainCharacter.setNormalTexture();
        mainCharacter.shield = false;
    }
    //animation sword
    if (mainCharacter.sword == 1) {
        if (game->clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            if (mainCharacter.swordAttack() == finalSwordAttack) {
                mainCharacter.damageSword(enemyVec); // final damage sword
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
        if (mainCharacter.ball.animation(enemyVec,mainCharacter) == finalBallAnimation) {
            mainCharacter.ball.animationBall = false;
            mainCharacter.spell = false;
        }
        mainCharacter.ball.clock.restart();
    }
    //animation arrow
    if (mainCharacter.arrowPlayer.animationArrow) {
        if (mainCharacter.arrowPlayer.arrowFor < 8) {
            if (mainCharacter.arrowPlayer.clock.getElapsedTime().asMilliseconds() > 45.f) {
                mainCharacter.arrowPlayer.animation(map.tile,enemyVec);
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

    //idle enemy
    for (int i = 0; i < enemyVec.size(); ++i) {
        if(enemyVec[i]->idle){
            if(enemyVec[i]->idleClock.getElapsedTime().asMilliseconds()>=100.f){
                enemyVec[i]->animationIdle();
                enemyVec[i]->idleClock.restart();
            }
        }
    }
    //animation die Enemy and remove if is die to the enemy vector
    for (int i = 0; i < enemyVec.size(); ++i) {
        if(enemyVec[i]->life<=0){
            if(enemyVec[i]->dieClock.getElapsedTime().asMilliseconds()>=45.f){
                if(enemyVec[i]->animationDie()==dieMaxEnemy){
                    enemyVec.erase(enemyVec.begin()+i);
                }
                enemyVec[i]->dieClock.restart();
            }
        }
    }
    //attack enemy
    int x;
    for (int i = 0; i < enemyVec.size(); ++i) {
        x=maxAttackEnemyNormal;
        if(enemyVec[i]->aniAttack){
            if(enemyVec[i]->dieClock.getElapsedTime().asMilliseconds()>=50.f){
                if(enemyVec[i]->type!="normal")
                    x=maxAttackEnemyExtra;
                if(enemyVec[i]->animationAttack(x)==x){
                    enemyVec[i]->attackPlayer(mainCharacter);
                    enemyVec[i]->aniAttack=false;
                }
                enemyVec[i]->dieClock.restart();
            }
        }
    }
    //die player
    if(mainCharacter.life<=0){
        mainCharacter.die=true;
        if(game->dieClock.getElapsedTime().asMilliseconds()>=40.f && !mainCharacter.finalDie){
            if(mainCharacter.dieAnimation()==maxLeftDiePlayer){
                mainCharacter.finalDie=true;
            }
            game->dieClock.restart();
        }
    }
}

void Event::inputEvent(MainCharacter &mainCharacter, Game* game,TileMap &map) {
    if (game->event.type == sf::Event::Closed)
        game->window.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        backToMenu(game);
        mainCharacter.die=false;
        mainCharacter.finalDie=false;
        mainCharacter.resetPlayer(game->window);
    }
    //player movement
    if(!mainCharacter.die){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mainCharacter.movePlayer('u', game->window, map.tile);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mainCharacter.movePlayer('d', game->window, map.tile);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mainCharacter.movePlayer('l', game->window, map.tile);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mainCharacter.movePlayer('r', game->window, map.tile);
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

void Event::backToMenu(Game* game){ //switch state to menu
    game->init=false;
    game->pushState(new ConcreteStateMenu(game));
}

void Event::AStarEnemy(Game* game,TileMap &map,MainCharacter &mainCharacter, std::vector<Enemy*> enemyVec){
    if(game->enemyAStar.getElapsedTime().asMilliseconds()>=500.f) {
        for (auto &i:enemyVec) {
            i->checkAStar(map, mainCharacter, map.tile);
        }
        game->enemyAStar.restart();
    }

    if(game->enemyAStarMove.getElapsedTime().asMilliseconds()>=25.f) {
        for (auto &i:enemyVec) {
            i->moveAStar(map.tile,mainCharacter);
        }
        game->enemyAStarMove.restart();
    }
}