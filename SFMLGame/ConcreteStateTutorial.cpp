#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConcreteStateTutorial.h"
#include "ConcreteStateMenu.h"
#include "GameState.h"
#include "Enemy.h"
#include "config.cpp"
#include <fstream>
#include <regex>

ConcreteStateTutorial::ConcreteStateTutorial(Game* game){
    this->game = game;
}

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

    for(int i=0; i<tutorialTextVec.size();++i){
        tutorialTextVec[i]->drawGameText(game->window);
        if(textClock.getElapsedTime().asSeconds()>=6){
            tutorialTextVec.erase(tutorialTextVec.begin());
            textClock.restart();
        }
        break;
    }
    if(game->interact)
        game->interactText.drawGameText(game->window);
}

void ConcreteStateTutorial::update(MainCharacter &mainCharacter){
    loopEvent.updateEvent(mainCharacter,game,map,enemyVec);
    loopEvent.AStarEnemy(game,map,mainCharacter,enemyVec);
    for(auto i:tutorialTextVec){
        i->moveText(mainCharacter);
    }
    for(auto i:tutorialTextVec){
        i->checkString();
        break;
    }

}

void ConcreteStateTutorial::handleInput(MainCharacter &mainCharacter){
    while (game->window.pollEvent(game->event)){
        loopEvent.inputEvent(mainCharacter,game,map);
    }
}

void ConcreteStateTutorial::Init(MainCharacter &mainCharacter) {
    loadFromFile(MAP_ROOT_TUTORIAL"/Tutorial.txt");
    float x=0,y=0;
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

    std::string text;
    text="use the arrow keys to move the character";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use Q,W,E,R for use the ability";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use Q for attack the enemy with a sword";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use W for use your bow, you have only a arrow remember that!";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use E for pick a shield and become immortal for a few seconds";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use R to launch a special fireball";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="use X interact with the map (lever,door...)";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="Press 'esc' to return to menu";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="Remember the lever open all Gate";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="and the key open only a relative door";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    text="and now explore the map and complete the tutorial!!!";
    tutorialTextVec.push_back(new GameText(text,mainCharacter));
    game->init=true;
}


