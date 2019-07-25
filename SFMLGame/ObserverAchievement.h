#ifndef SFMLGAME_OBSERVERACHIEVEMENT_H
#define SFMLGAME_OBSERVERACHIEVEMENT_H

#include <iostream>
#include <map>
class ObserverAchievement {

public:
    std::map<std::string,std::string> map;
    virtual void addAchievement(std::string text,std::string fileName)=0;

protected:
    void printAchievement(std::string text);
};

#endif
