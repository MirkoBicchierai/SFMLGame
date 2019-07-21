#include "ConcreteStateGame3.h"
#include "ConcreteStateGame4.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ConcreteStateMenu.h"
#include "config.cpp"
#include <fstream>
#include <regex>

ConcreteStateGame3::ConcreteStateGame3(Game* game){
    this->game = game;
}

void ConcreteStateGame3::loadFromFile(const std::string &path) {
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

void ConcreteStateGame3::draw(MainCharacter &mainCharacter){

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

void ConcreteStateGame3::update(MainCharacter &mainCharacter){
    loopEvent.updateEvent(mainCharacter,game,map,enemyVec,coinVec);
    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);

    for (int j = 0; j < map.tile.size() ; ++j) {
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(map.tile[j].spriteShow.getGlobalBounds()) && map.tile[j].end ){
            game->init=false;
            game->pushState(new ConcreteStateGame4(game));
            break;
        }
    }

}
void ConcreteStateGame3::handleInput(MainCharacter &mainCharacter){
    while (game->window.pollEvent(game->event)){
        loopEvent.inputEvent(mainCharacter,game,map);
    }
}

void ConcreteStateGame3::Init(MainCharacter &mainCharacter) {
    loadFromFile(MAP_ROOT_GAME"/level3.txt");
    int x,y;
    std::string file;
    for (int i = 0; i < 3; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="normal";
        enemyVec.push_back(new Enemy(x,y,file,600,1));
    }
    for (int i = 0; i < 3; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="reptiles";
        enemyVec.push_back(new Enemy(x,y,file,500,1));
    }
    for (int i = 0; i < 3; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="skeleton";
        enemyVec.push_back(new Enemy(x,y,file,400,1));
    }

    for (int j = 0; j <map.tile.size() ; ++j) {
        if((map.tile[j].i==0) && (map.tile[j].j==16 || map.tile[j].j==17))
            map.tile[j].setEnd();
        if(map.tile[j].i==23 && map.tile[j].j==42)
            mainCharacter.resetPlayer(game->window,map.tile[j].spriteShow);
    }
    game->window.setView(mainCharacter.camera);
    game->init=true;
}

