#ifndef SFMLGAME_MAPSEARCHNODE_H
#define SFMLGAME_MAPSEARCHNODE_H

#include "stlastar.h"

class MapSearchNode {

public:
    int MAP_WIDTH; // width of map
    int MAP_HEIGHT; // height of map
    int *world_map; //vector of int for the map (9 can't pass, 0-5 is the cost for pass)
    int x;	 // the (x,y) positions of the node
    int y;
    MapSearchNode();
    MapSearchNode(int px, int py);

    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );
    void startNode(int width,int height, const int *map); //used on enemy to set the start node end the end node
    int GetMap( int x, int y ); //return the id on the map
    void PrintNodeInfo(); // print the info of node
private:
    void setNode(MapSearchNode &NewNode); // set the node in GetSuccessors
};

#endif
