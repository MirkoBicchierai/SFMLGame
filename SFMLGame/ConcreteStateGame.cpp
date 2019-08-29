#include <iostream>
#include <SFML/Graphics.hpp>
#include "ConcreteStateGame.h"
#include "ConcreteStateMenu.h"
#include "config.cpp"
#include <fstream>
#include <regex>
#include "ConcreteStateMenuPowerUp.h"
ConcreteStateGame::ConcreteStateGame(Game* game){
    this->game = game;
}

void ConcreteStateGame::loadFromFile(const std::string &path) {
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

void ConcreteStateGame::draw(MainCharacter &mainCharacter){

    for(auto i:map.tile){
        i.drawTile(game->window);
    }
    for(auto i:enemyVec){
        i->drawEnemy(game->window);
    }
    for(auto i:coinVec){
        i->drawCoin(game->window);
    }

    if(bossLevel)
        boss.drawBoss(game->window);

    mainCharacter.drawPlayer(game->window,game->clockShield);

    if(game->interact)
        game->interactText.drawGameText(game->window);
}

void ConcreteStateGame::update(MainCharacter &mainCharacter){
    if(bossLevel){
        loopEvent.updateEvent(mainCharacter,game,map,enemyVec,coinVec,&boss);
        if(bossAStar.getElapsedTime().asMilliseconds()>=500.f && !boss.die) {
            boss.checkAStarBoss(map, mainCharacter, map.tile);
            bossAStar.restart();
        }

        if(bossAStarMove.getElapsedTime().asMilliseconds()>=18.f && !boss.die) {
            boss.moveAStarBoss(map.tile,mainCharacter);
            bossAStarMove.restart();
        }

        if(boss.aniAttack) {
            if(swordAttackBoss.getElapsedTime().asMilliseconds()>=40.f){
                if(boss.animationAttackBoss()==maxLeftAttack){
                    boss.soundAttack.play();
                    boss.aniAttack=false;
                    boss.doDamagePlayer(mainCharacter);
                }
                swordAttackBoss.restart();
            }
        }

        if(boss.life<=0){
            boss.die=true;
            boss.aniAttack=false;
            if(boss.dieClock.getElapsedTime().asMilliseconds()>=45.f){
                if(boss.animationDie()==maxLeftAttack){
                    boss.finish=true;
                    mainCharacter.inventory.NumberGoldKey++;
                }
                boss.dieClock.restart();
            }
        }
    }
    else
        loopEvent.updateEvent(mainCharacter,game,map,enemyVec,coinVec);

    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);

    for (int j = 0; j < map.tile.size() ; ++j) {
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(map.tile[j].spriteShow.getGlobalBounds()) && map.tile[j].end  && actualLevel==4){
            game->init=false;
            loopEvent.backToMenu(game);
            game->Achievement->addAchievement("Kill Boss","KillBoss.png");
            if(mainCharacter.life==3)
                game->Achievement->addAchievement("Perfect level","FlawLess.png");
            return;
        }
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(map.tile[j].spriteShow.getGlobalBounds()) && map.tile[j].end ){
            game->init=false;
            actualLevel++;
            mainCharacter.resetKey();
            game->pushState(new ConcreteStateMenuPowerUp(game,this));
            if(mainCharacter.life==3)
                game->Achievement->addAchievement("Perfect level","FlawLess.png");
            enemyVec.clear();
            map.tile.clear();
            coinVec.clear();
            vec.clear();
            break;
        }
    }

}

void ConcreteStateGame::handleInput(MainCharacter &mainCharacter){
    while (game->window.pollEvent(game->event)){
        loopEvent.inputEvent(mainCharacter,game,map);
    }
}

void ConcreteStateGame::Init(MainCharacter &mainCharacter) {
    bossLevel=false;
    if(actualLevel==4)
        bossLevel=true;
    loadFromFile(MAP_ROOT_GAME"/Level"+to_string(actualLevel)+".txt");
    spawnEnemy();
    setEndPoint();
    setSpawnPoint(mainCharacter);
    game->window.setView(mainCharacter.camera);
    game->init=true;
}

void ConcreteStateGame::spawnEnemy() {
    int x,y;
    std::string file;
    if(actualLevel==1) {
        for (int i = 0; i < 2; ++i) {
            x=rand()%1200 + 1200;
            y=rand()%1200 + 1200;
            file="normal";
            enemyVec.push_back(new Enemy(x,y,file,600,1));
        }
        for (int i = 0; i < 2; ++i) {
            x=rand()%1200 + 1200;
            y=rand()%1200 + 1200;
            file="reptiles";
            enemyVec.push_back(new Enemy(x,y,file,500,1));
        }
        for (int i = 0; i < 2; ++i) {
            x=rand()%1200 + 1200;
            y=rand()%1200 + 1200;
            file="skeleton";
            enemyVec.push_back(new Enemy(x,y,file,400,1));
        }
    }
    if(actualLevel==2) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==1 && map.tile[j].j==2) || (map.tile[j].i==20 && map.tile[j].j==41) || (map.tile[j].i==28 && map.tile[j].j==44) || (map.tile[j].i==3 && map.tile[j].j==29) || (map.tile[j].i==5 && map.tile[j].j==23) ){
                file="normal";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,600,1));
            }
            if((map.tile[j].i==4 && map.tile[j].j==45) || (map.tile[j].i==44 && map.tile[j].j==45) || (map.tile[j].i==22 && map.tile[j].j==29)){
                file="reptiles";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,500,1));
            }
            if((map.tile[j].i==39 && map.tile[j].j==19) || (map.tile[j].i==46 && map.tile[j].j==23) || (map.tile[j].i==46 && map.tile[j].j==15)){
                file="skeleton";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,400,1));
            }
        }
    }
    if(actualLevel==3) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==4 && map.tile[j].j==46) || (map.tile[j].i==44 && map.tile[j].j==46) || (map.tile[j].i==22 && map.tile[j].j==37) || (map.tile[j].i==23 && map.tile[j].j==37) || (map.tile[j].i==20 && map.tile[j].j==7) ){
                file="normal";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,600,1));
            }
            if((map.tile[j].i==2 && map.tile[j].j==30) || (map.tile[j].i==42 && map.tile[j].j==29) || (map.tile[j].i==22 && map.tile[j].j==23)){
                file="reptiles";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,500,1));
            }
            if((map.tile[j].i==2 && map.tile[j].j==8) || (map.tile[j].i==2 && map.tile[j].j==4) || (map.tile[j].i==42 && map.tile[j].j==20)|| (map.tile[j].i==38 && map.tile[j].j==14)){
                file="skeleton";
                enemyVec.push_back(new Enemy(map.tile[j].spriteShow.getPosition().x,map.tile[j].spriteShow.getPosition().y,file,400,1));
            }
        }
    }
    if(actualLevel==4) {
        for (int i = 0; i < 2; ++i) {
            x=rand()%1200 + 600;
            y=rand()%1200 + 600;
            file="normal";
            enemyVec.push_back(new Enemy(x,y,file,600,1));
        }
        boss.reset();
    }
}

void ConcreteStateGame::setSpawnPoint(MainCharacter &mainCharacter) {
    int x=1, y=1;
    if(actualLevel==1)
        x=y=5;
    if(actualLevel==2)
        x=y=6;
    if(actualLevel==3) {
        x =23;
        y = 42;
    }
    if(actualLevel==4) {
        x =20;
        y = 20;
    }
    for (int j = 0; j <map.tile.size() ; ++j) {
        if(map.tile[j].i==x && map.tile[j].j==y) {
            mainCharacter.resetPlayer(game->window, map.tile[j].spriteShow);
            return;
        }
    }
}

void ConcreteStateGame::setEndPoint() {
    if(actualLevel==1) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==8 || map.tile[j].i==9) && map.tile[j].j==1)
                map.tile[j].setEnd();
        }
    }
    if(actualLevel==2) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if(map.tile[j].i==10 && map.tile[j].j==16)
                map.tile[j].setEnd();
        }
    }
    if(actualLevel==3) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==0) && (map.tile[j].j==16 || map.tile[j].j==17))
                map.tile[j].setEnd();
        }
    }
    if(actualLevel==4) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==19 || map.tile[j].i==20) && map.tile[j].j==3)
                map.tile[j].setEnd();
        }
    }
}

