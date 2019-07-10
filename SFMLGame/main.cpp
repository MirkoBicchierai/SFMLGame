#include "Game.h"
#include "ConcreteStateMenu.h"
#include "Enemy.h"
#include "config.cpp"
sf::Texture Enemy::txt;
int main(){
    Enemy:: txt.loadFromFile(IMG_ENEMY_ROOT"/normal.png");
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}
