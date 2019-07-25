#include "ConcreteAchievement.h"

void ConcreteAchievement::addAchievement(std::string text,std::string fileName) {
    if (map.count(text) == 0) {
        map.insert(make_pair(text,fileName));
        printAchievement(text);
    }
}

