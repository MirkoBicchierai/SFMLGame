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
    loopEvent.updateEvent(mainCharacter,game,map);
    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);
}

void ConcreteStateTutorial::handleInput(MainCharacter &mainCharacter){
    while (game->window.pollEvent(game->event)){
        loopEvent.inputEvent(mainCharacter,game,map);
    }
}

ConcreteStateTutorial::ConcreteStateTutorial(Game* game){
    this->game = game;
}

void ConcreteStateTutorial::Init() {
    loadFromFile(MAP_ROOT_TUTORIAL"/Tutorial.txt");
    float x=0,y=0;
    std::string file;
    for (int i = 0; i < 2; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="normal";
        enemyVec.push_back(new Enemy(x,y,file,600));
    }
    for (int i = 0; i < 2; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="reptiles";
        enemyVec.push_back(new Enemy(x,y,file,500));
    }
    for (int i = 0; i < 2; ++i) {
        x=rand()%1200 + 1200;
        y=rand()%1200 + 1200;
        file="skeleton";
        enemyVec.push_back(new Enemy(x,y,file,400));
    }
    game->init=true;
}


