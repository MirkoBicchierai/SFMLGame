#include "ObserverAchievement.h"
#include "config.cpp"
void ObserverAchievement::printAchievement(std::string text) {
    auto itr = map.find(text);
    if(itr!=map.end()) {
        std::string file=IMG_ROOT_ACHIEVEMENT"/"+itr->second;
        std::string textAchievement=itr->first;
        std::cout<<"Testo:"<<textAchievement<<" fileName: "<<file<<std::endl;
    }
}
