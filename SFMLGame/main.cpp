#include "Game.h"
#include "ConcreteStateMenu.h"
#include "stlastar.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <exception>

int main(){
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}
