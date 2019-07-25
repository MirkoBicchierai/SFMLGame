#ifndef SFMLGAME_CONCRETEACHIEVEMENT_H
#define SFMLGAME_CONCRETEACHIEVEMENT_H

#include "ObserverAchievement.h"

class ConcreteAchievement: public ObserverAchievement {

public:
    void addAchievement(std::string text,std::string fileName) override;

};

#endif
