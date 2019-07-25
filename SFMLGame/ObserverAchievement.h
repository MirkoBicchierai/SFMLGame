#ifndef SFMLGAME_OBSERVERACHIEVEMENT_H
#define SFMLGAME_OBSERVERACHIEVEMENT_H

#include <iostream>
#include <map>
#include <vector>
#include "Achievement.h"
#include "MainCharacter.h"
class ObserverAchievement {

public:
    std::map<std::string,std::string> map;
    std::vector<Achievement*> achievementPrint;
    virtual void addAchievement(std::string text,std::string fileName)=0;
    void drawVectorAchievement(sf::RenderWindow &window,MainCharacter &mainCharacter);
    void updateAchievement();
protected:
    void printAchievement(std::string text);
};

#endif
