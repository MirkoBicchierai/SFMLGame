#include <utility>

#include "Event.h"
#include "config.cpp"
#include "ConcreteStateMenu.h"

void Event::updateEvent(MainCharacter &mainCharacter,Game* game,TileMap &map, std::vector<Enemy*> &enemyVec, std::vector<Coin*> &coinVec,FinalBoss* boss) {
    //time shield end
    if (mainCharacter.shield && game->clockShield.getElapsedTime().asSeconds() >= mainCharacter.secShield) {
        mainCharacter.setNormalTexture();
        mainCharacter.shield = false;
    }
    //animation sword
    if (mainCharacter.sword == 1) {
        if (game->clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
            if (mainCharacter.swordAttack() == finalSwordAttack) {
                mainCharacter.soundSword.play();
                mainCharacter.damageSword(enemyVec,boss); // final damage sword
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
        if (mainCharacter.ball.animation(enemyVec,mainCharacter,boss) == finalBallAnimation) {
            mainCharacter.ball.animationBall = false;
            mainCharacter.spell = false;
        }
        mainCharacter.ball.clock.restart();
    }
    //animation arrow
    if (mainCharacter.arrowPlayer.animationArrow) {
        if (mainCharacter.arrowPlayer.arrowFor < 8) {
            if (mainCharacter.arrowPlayer.clock.getElapsedTime().asMilliseconds() > 45.f) {
                mainCharacter.arrowPlayer.animation(map.tile,enemyVec,boss);
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
                    coinVec.emplace_back(new Coin());
                    int n=coinVec.size();
                    coinVec[n-1]->setPosition(enemyVec[i]->entitySprite);
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
            if(enemyVec[i]->AttackClock.getElapsedTime().asMilliseconds()>=50.f){
                if(enemyVec[i]->type!="normal")
                    x=maxAttackEnemyExtra;
                if(enemyVec[i]->animationAttack(x)==x){
                    enemyVec[i]->soundAttack.play();
                    enemyVec[i]->attackPlayer(mainCharacter);
                    enemyVec[i]->aniAttack=false;
                }
                enemyVec[i]->AttackClock.restart();
            }
        }
    }
    //die player
    if(mainCharacter.life<=0){
        mainCharacter.die=true;
        if(game->dieClock.getElapsedTime().asMilliseconds()>=40.f && !mainCharacter.finalDie){
            if(mainCharacter.dieAnimation()==maxLeftDiePlayer){
                mainCharacter.finalDie=true;
                mainCharacter.resetInventory();
            }
            game->dieClock.restart();
        }
    }
    //interact with tile-map
    for(auto i:map.tile){
        if(i.checkInteract()){
            if(distanceBetweenTwoSprite(i.spriteShow,mainCharacter.getSprite())<=64){
                game->interactText.setGameText("Press X",i.spriteShow);
                game->interact=true;
                game->actualInteractI=i.i;
                game->actualInteractJ = i.j;
                game->typeInteract=i.type;
            }
        }
        if(game->actualInteractI==i.i && game->actualInteractJ == i.j &&distanceBetweenTwoSprite(i.spriteShow,mainCharacter.getSprite())>=64){
            game->interact=false;
        }
    }
    //take coin on floor
    for (int j = 0; j < coinVec.size(); ++j) {
        if(mainCharacter.getSprite().getGlobalBounds().intersects(coinVec[j]->getSprite().getGlobalBounds())){
            mainCharacter.inventory.NumberGold+=coinVec[j]->getValue();
            coinVec.erase(coinVec.begin()+j);
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
        //interact with map
        if(game->interact){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                mapInteraction(mainCharacter,game,map);
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mainCharacter.spell && !mainCharacter.aniArrow) {
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

    if(game->enemyAStarMove.getElapsedTime().asMilliseconds()>=18.f) {
        for (auto &i:enemyVec) {
            i->moveAStar(map.tile,mainCharacter);
        }
        game->enemyAStarMove.restart();
    }
}

void Event::mapInteraction(MainCharacter &mainCharacter, Game *game, TileMap &map) {
        int ii, jj, n;
        sf::Vector2u tileSize(64, 64);
        bool leverActivate = false;
        if(game->typeInteract == "closed_door_silver" && mainCharacter.inventory.NumberSilverKey==0)
            return;
        if(game->typeInteract == "closed_door_gold" && mainCharacter.inventory.NumberGoldKey==0)
            return;
        if(game->typeInteract == "closed_door_silver" && mainCharacter.inventory.NumberSilverKey>0)
            mainCharacter.inventory.NumberSilverKey--;
        if(game->typeInteract == "closed_door_gold" && mainCharacter.inventory.NumberGoldKey>0)
            mainCharacter.inventory.NumberGoldKey--;
        for (int j = 0; j < map.tile.size(); ++j) {
            if (game->typeInteract == "lever") {
                if (game->actualInteractI == map.tile[j].i && game->actualInteractJ == map.tile[j].j) {
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,207);
                    game->interact = false;
                    leverActivate = true;
                }
                if (game->actualInteractI == map.tile[j].i && game->actualInteractJ - 1 == map.tile[j].j)
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,1);
                if (game->actualInteractI + 1 == map.tile[j].i && game->actualInteractJ == map.tile[j].j)
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,208);
            }
            if (game->typeInteract == "silver_key" || game->typeInteract == "gold_key") {
                if (game->actualInteractI == map.tile[j].i && game->actualInteractJ == map.tile[j].j) {
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,1);
                    game->interact=false;
                    if (game->typeInteract == "gold_key")
                        mainCharacter.inventory.NumberGoldKey++;
                    else
                        mainCharacter.inventory.NumberSilverKey++;
                    break;
                }
            }
            if (game->typeInteract == "closed_door_silver" || game->typeInteract == "closed_door_gold") {
                if (game->actualInteractI == map.tile[j].i && game->actualInteractJ - 1 == map.tile[j].j) {
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,1);
                    game->interact = false;
                }
                if (game->actualInteractI - 1 == map.tile[j].i && game->actualInteractJ == map.tile[j].j &&
                    map.tile[j].type != "wall") { //left delete
                    for (int i = 0; i < map.tile.size(); ++i) {
                        if (game->actualInteractI - 1 == map.tile[i].i && game->actualInteractJ == map.tile[i].j) {
                            deleteCreateNewTile(map.tile[i].i,map.tile[i].j,map,i,1);
                            game->interact = false;
                            break;
                        }
                    }
                    for (int i = 0; i < map.tile.size(); ++i) {
                        if (game->actualInteractI - 1 == map.tile[i].i && game->actualInteractJ - 1 == map.tile[i].j) {
                            deleteCreateNewTile(map.tile[i].i,map.tile[i].j,map,i,1);
                            game->interact = false;
                            break;
                        }
                    }
                }
                if (game->actualInteractI + 1 == map.tile[j].i && game->actualInteractJ == map.tile[j].j &&
                    map.tile[j].type != "wall") { //right delete
                    for (int i = 0; i < map.tile.size(); ++i) {
                        if (game->actualInteractI + 1 == map.tile[i].i && game->actualInteractJ - 1 == map.tile[i].j) {
                            deleteCreateNewTile(map.tile[i].i,map.tile[i].j,map,i,1);
                            game->interact = false;
                            break;
                        }
                    }
                    for (int i = 0; i < map.tile.size(); ++i) {
                        if (game->actualInteractI + 1 == map.tile[i].i && game->actualInteractJ == map.tile[i].j) {
                            deleteCreateNewTile(map.tile[i].i,map.tile[i].j,map,i,1);
                            game->interact = false;
                            break;
                        }
                    }
                }
                if (game->actualInteractI == map.tile[j].i && game->actualInteractJ == map.tile[j].j) {
                    deleteCreateNewTile(map.tile[j].i,map.tile[j].j,map,j,1);
                    game->interact = false;
                }
            }
        }

        if (leverActivate) {
            struct coordinate {
                int i;
                int j;
            };
            std::vector<coordinate> Add;
            std::vector<int> Remove;
            struct coordinate x;
            for (int j = 0; j < map.tile.size(); ++j) {
                if (map.tile[j].type == "gate") {
                    ii = map.tile[j].i;
                    jj = map.tile[j].j;
                    x.i = ii;
                    x.j = jj;
                    Add.push_back(x);
                    int k = j;
                    Remove.push_back(k);
                }
            }
            for (int k = 0; k < Remove.size(); ++k) {
                map.tile.erase(map.tile.begin() + Remove[k] - k);
            }
            for (int l = 0; l < Add.size(); ++l) {
                map.tile.emplace_back(Tile(169, "floor", Add[l].i, Add[l].j));
                n = map.tile.size();
                map.tile[n - 1].setTile(map.texture, tileSize);
            }
        }
    map.updateMapAStar();
}

void Event::deleteCreateNewTile(int iii, int jjj, TileMap &map, int iter,int idTile) {
    sf::Vector2u tileSize(64, 64);
    int ii = iii;
    int jj = jjj;
    map.tile.erase(map.tile.begin() + iter);
    map.tile.emplace_back(Tile(idTile, "obj", ii, jj));
    int n = map.tile.size();
    map.tile[n - 1].setTile(map.texture, tileSize);
}
