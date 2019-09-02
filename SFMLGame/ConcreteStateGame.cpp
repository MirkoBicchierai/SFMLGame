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
    std::string s;
    std::ifstream infile(MAP_ROOT_GAME"/configLevel"+to_string(actualLevel)+".txt");
    int x,y;
    std::string file;
    int randN=0;
    bool randNN=false;
    int randR=0;
    bool randRR=false;
    int randS=0;
    bool randSS=false;
    int fin=0;
    struct cord{
        int x;
        int y;
        std::string file;
        int range;
    };
    struct cord tmp;
    std::vector<struct cord> cord;
    tmp.x=0;
    tmp.y=0;
    tmp.file="normal";
    tmp.range=0;
    bool randC;
    bool next;
    bool stat;
    while (std::getline(infile, s)){
        std::regex ws_re(",");
        std::vector<std::string> result{ std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), {}};
        randC=false;
        next=false;
        stat=false;
        for (const auto & i : result) {
            std::stringstream geek(i);
            x = 0;
            geek >> x;
            if(fin==2){
                if(x==-2 || x==-3 || x==-4){
                    randC=true;
                }
                if(randC){
                    if(randNN){
                        randN=x;
                        randNN=false;
                    }
                    if(x==-2){
                        randNN=true;
                    }
                    if(randRR){
                        randR=x;
                        randRR=false;
                    }
                    if(x==-3){
                        randRR=true;
                    }
                    if(randSS){
                        randS=x;
                        randSS=false;
                    }
                    if(x==-4){
                        randSS=true;
                    }
                }else{
                    if(stat){
                        if(x==2) {
                            tmp.file = "normal";
                            tmp.range=rangeN;
                        }
                        if(x==3){
                            tmp.file="reptiles";
                            tmp.range=rangeR;
                        }
                        if(x==4){
                            tmp.file="skeleton";
                            tmp.range=rangeS;
                        }
                        cord.push_back(tmp);
                        stat=false;
                    }
                    if(!next)
                        tmp.x=x;
                    else {
                        tmp.y = x;
                        stat=true;
                    }
                    next=true;
                }
            }
            if(x==-1)
                fin++;
        }
    }
    for (int i = 0; i < randN; ++i) {
        x=rand()%(randCC) + randSUM;
        y=rand()%(randCC) + randSUM;
        file="normal";
        enemyVec.push_back(new Enemy(x,y,file,rangeN,1));
    }
    for (int i = 0; i < randR; ++i) {
        x=rand()%(randCC) + randSUM;
        y=rand()%(randCC) + randSUM;
        file="reptiles";
        enemyVec.push_back(new Enemy(x,y,file,rangeR,1));
    }
    for (int i = 0; i < randS; ++i) {
        x=rand()%(randCC) + randSUM;
        y=rand()%(randCC) + randSUM;
        file="skeleton";
        enemyVec.push_back(new Enemy(x,y,file,rangeS,1));
    }

    for (int j = 0; j < cord.size(); ++j) {
        for (int k = 0; k <map.tile.size() ; ++k) {
            if(map.tile[k].i==cord[j].x && map.tile[k].j==cord[j].y){
                enemyVec.push_back(new Enemy(map.tile[k].spriteShow.getPosition().x,map.tile[k].spriteShow.getPosition().y,cord[j].file,cord[j].range,1));
            }
        }
    }

}

void ConcreteStateGame::setSpawnPoint(MainCharacter &mainCharacter) {

    std::string s;
    std::ifstream infile(MAP_ROOT_GAME"/configLevel"+to_string(actualLevel)+".txt");
    std::vector<int> cord;
    while (std::getline(infile, s)){
        std::regex ws_re(",");
        std::vector<std::string> result{ std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), {}};
        for (const auto & i : result) {
            std::stringstream geek(i);
            int x = 0;
            geek >> x;
            cord.push_back(x);
        }
        break;
    }
    for (int j = 0; j <map.tile.size() ; ++j) {
        if(map.tile[j].i==cord[0] && map.tile[j].j==cord[1]) {
            mainCharacter.resetPlayer(game->window, map.tile[j].spriteShow);
            return;
        }
    }
}

void ConcreteStateGame::setEndPoint() {

    std::string s;
    std::ifstream infile(MAP_ROOT_GAME"/configLevel"+to_string(actualLevel)+".txt");
    struct cord{
        int x;
        int y;
    };
    struct cord tmp;
    tmp.x=0;
    tmp.y=0;
    std::vector<struct cord> cord;
    int fin=0;
    bool next;
    while (std::getline(infile, s)){
        std::regex ws_re(",");
        std::vector<std::string> result{ std::sregex_token_iterator(s.begin(), s.end(), ws_re, -1), {}};
        next=false;
        for (const auto & i : result) {
            std::stringstream geek(i);
            int x = 0;
            geek >> x;
            if(x==-1)
                fin++;
            if(fin==1){
                if(!next)
                    tmp.x=x;
                else {
                    tmp.y = x;
                    cord.push_back(tmp);
                }
                next=true;
            }
        }
    }
    for (int k = 0; k < cord.size(); ++k) {
        for (int j = 0; j <map.tile.size() ; ++j) {
            if((map.tile[j].i==cord[k].x && map.tile[j].j==cord[k].y))
                map.tile[j].setEnd();
        }
    }
}