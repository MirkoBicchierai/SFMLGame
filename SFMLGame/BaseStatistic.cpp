#include "BaseStatistic.h"

void BaseStatistic::soundStepControl() {
    if(soundStepClock.getElapsedTime().asMilliseconds()>=180.f){
        soundStep.play();
        soundStepClock.restart();
    }
}