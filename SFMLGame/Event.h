#ifndef SFMLGAME_EVENT_H
#define SFMLGAME_EVENT_H

#include "MainCharacter.h"
#include "Game.h"
#include "TileMap.h"
#include <vector>
#include "Enemy.h"
#include "Coin.h"
class Event{
public:
    void updateEvent(MainCharacter &mainCharacter,Game* game,TileMap &map, std::vector<Enemy*> &enemyVec, std::vector<Coin*> &coinVec);
    void inputEvent(MainCharacter &mainCharacter,Game* game,TileMap &map);
    void AStarEnemy(Game* game,TileMap &map,MainCharacter &mainCharacter, std::vector<Enemy*> enemyVec);
    void backToMenu(Game* game);
    void mapInteraction(MainCharacter &mainCharacter,Game* game,TileMap &map);
private:
    void deleteCreateNewTile(int i, int j,TileMap &map,int iter,int idTile);
};

#endif
