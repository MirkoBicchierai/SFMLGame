#include "Game.h"
#include "ConcreteStateMenu.h"

int main(){
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}
