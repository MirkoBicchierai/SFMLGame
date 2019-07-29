#include <iostream>
#include <SFML/Graphics.hpp>
#include "ConcreteStateGame.h"
#include "ConcreteStateMenu.h"
#include "config.cpp"
#include <fstream>
#include <regex>
#include "ConcreteStateGame2.h"
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

    mainCharacter.drawPlayer(game->window,game->clockShield);

    if(game->interact)
        game->interactText.drawGameText(game->window);
}

void ConcreteStateGame::update(MainCharacter &mainCharacter){
    loopEvent.updateEvent(mainCharacter,game,map,enemyVec,coinVec);
    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);
    for (int j = 0; j < map.tile.size() ; ++j) {
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(map.tile[j].spriteShow.getGlobalBounds()) && map.tile[j].end ){
            game->init=false;
            mainCharacter.resetKey();
            game->pushState(new ConcreteStateMenuPowerUp(game,new ConcreteStateGame2(game)));
            if(mainCharacter.life==3)
                game->Achievement->addAchievement("Perfect level","FlawLess.png");
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
    loadFromFile(MAP_ROOT_GAME"/level1.txt");
    int x,y;
    std::string file;
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

    for (int j = 0; j <map.tile.size() ; ++j) {
        if((map.tile[j].i==8 || map.tile[j].i==9) && map.tile[j].j==1)
            map.tile[j].setEnd();
        if(map.tile[j].i==5 && map.tile[j].j==5)
            mainCharacter.resetPlayer(game->window,map.tile[j].spriteShow);
    }
    game->window.setView(mainCharacter.camera);
    game->init=true;
}
