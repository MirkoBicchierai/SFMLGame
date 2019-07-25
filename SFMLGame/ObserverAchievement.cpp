#include "ObserverAchievement.h"

void ObserverAchievement::printAchievement(std::string text) {

    auto itr = map.find(text);
    if(itr!=map.end()) {
        std::cout<<"Testo:"<<itr->first<<" fileName: "<<itr->second<<std::endl;
    }
}
