#include "Game.h"
#include "ConcreteStateMenu.h"
#include "Enemy.h"
#include "config.cpp"
int main(){
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}
