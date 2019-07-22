#include "Game.h"
#include "ConcreteStateMenu.h"
#include <windows.h>
int main(){
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}
