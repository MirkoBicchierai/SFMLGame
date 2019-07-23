#include "ConcreteStateGame2.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ConcreteStateMenu.h"
#include "ConcreteStateGame3.h"
#include "ConcreteStateMenuPowerUp.h"
#include "config.cpp"
#include <fstream>
#include <regex>

ConcreteStateGame2::ConcreteStateGame2(Game* game){
    this->game = game;
}

void ConcreteStateGame2::loadFromFile(const std::string &path) {
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

void ConcreteStateGame2::draw(MainCharacter &mainCharacter){

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

void ConcreteStateGame2::update(MainCharacter &mainCharacter){
    loopEvent.updateEvent(mainCharacter,game,map,enemyVec,coinVec);
    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);

    for (int j = 0; j < map.tile.size() ; ++j) {
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(map.tile[j].spriteShow.getGlobalBounds()) && map.tile[j].end ){
            game->init=false;
            mainCharacter.resetKey();
            game->pushState(new ConcreteStateMenuPowerUp(game,new ConcreteStateGame3(game)));
            break;
        }
    }

}
void ConcreteStateGame2::handleInput(MainCharacter &mainCharacter){
    while (game->window.pollEvent(game->event)){
        loopEvent.inputEvent(mainCharacter,game,map);
    }
}

void ConcreteStateGame2::Init(MainCharacter &mainCharacter) {
    loadFromFile(MAP_ROOT_GAME"/level2.txt");
    std::string file;
    for (int j = 0; j <map.tile.size() ; ++j) {
        if(map.tile[j].i==10 && map.tile[j].j==16)
            map.tile[j].setEnd();
        if(map.tile[j].i==6 && map.tile[j].j==6)
            mainCharacter.resetPlayer(game->window,map.tile[j].spriteShow);
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
    game->window.setView(mainCharacter.camera);
    game->init=true;
}
