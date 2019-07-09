
#ifndef SFMLGAME_MAPSEARCHNODE_H
#define SFMLGAME_MAPSEARCHNODE_H

#include "stlastar.h"
#include "TileMap.h"


class MapSearchNode {

public:
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int *world_map;
    int x;	 // the (x,y) positions of the node
    int y;
    MapSearchNode();
    MapSearchNode(int px, int py);

    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );
    void setNode(MapSearchNode &NewNode);
    void startNode(int width,int height, const int *map);
    int GetMap( int x, int y );
    void PrintNodeInfo();
};

#endif
