#ifndef SFMLGAME_EVENT_H
#define SFMLGAME_EVENT_H

#include "MainCharacter.h"
#include "Game.h"
#include "TileMap.h"
#include <vector>
#include "Enemy.h"

class Event{
public:
    void updateEvent(MainCharacter &mainCharacter,Game* game,TileMap &map, std::vector<Enemy*> &enemyVec);
    void inputEvent(MainCharacter &mainCharacter,Game* game,TileMap &map);
    void AStarEnemy(Game* game,TileMap &map,MainCharacter &mainCharacter, std::vector<Enemy*> enemyVec);
private:
    void backToMenu(Game* game);
};

#endif
