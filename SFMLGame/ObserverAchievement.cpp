#include "ObserverAchievement.h"
#include "config.cpp"

void ObserverAchievement::printAchievement(std::string text) {
    auto itr = map.find(text);
    if(itr!=map.end()) {
        std::string file=IMG_ROOT_ACHIEVEMENT"/"+itr->second;
        std::string textAchievement=itr->first;
        achievementPrint.push_back(new Achievement(textAchievement,file));
        int n =achievementPrint.size();
        achievementPrint[n-1]->AchievementClock.restart();
    }
}

void ObserverAchievement::drawVectorAchievement(sf::RenderWindow &window,MainCharacter &mainCharacter) {
    for (int i = 0; i <achievementPrint.size() ; ++i) {
        achievementPrint[i]->changePosition(i,window, mainCharacter);
        achievementPrint[i]->drawAchievement(window);
    }
}

void ObserverAchievement::updateAchievement() {
    for (int i = 0; i <achievementPrint.size() ; ++i) {
        if(achievementPrint[i]->AchievementClock.getElapsedTime().asSeconds()>=3.f)
            achievementPrint.erase(achievementPrint.begin()+i);
    }
}
