#include "MapSearchNode.h"
#include "stlastar.h"
#include <iostream>
using namespace std;

bool MapSearchNode::IsSameState( MapSearchNode &rhs ){
    // same state in a maze search is simply when (x,y) are the same
    if( x == rhs.x && y == rhs.y ){
        return true;
    }
    else{
        return false;
    }
}

void MapSearchNode::PrintNodeInfo(){
    char str[100];
    sprintf( str, "Node position : (%d,%d)\n", x,y );
    cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal ){
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal ){
    if((x == nodeGoal.x) && y == nodeGoal.y){
        return true;
    }
    return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node ){

    int parent_x = -1;
    int parent_y = -1;

    if( parent_node ){
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }

    MapSearchNode NewNode;

    // push each possible move except allowing the search to go backwards

    if( (GetMap( x-1, y ) < 9) && !((parent_x == x-1) && (parent_y == y))){
        NewNode = MapSearchNode( x-1, y);
        setNode(NewNode);
        astarsearch->AddSuccessor( NewNode );
    }

    if( (GetMap( x, y-1 ) < 9) && !((parent_x == x) && (parent_y == y-1))){
        NewNode = MapSearchNode( x, y-1);
        setNode(NewNode);
        astarsearch->AddSuccessor( NewNode );
    }

    if( (GetMap( x+1, y ) < 9) && !((parent_x == x+1) && (parent_y == y))){
        NewNode = MapSearchNode( x+1, y);
        setNode(NewNode);
        astarsearch->AddSuccessor( NewNode );
    }

    if( (GetMap( x, y+1 ) < 9) && !((parent_x == x) && (parent_y == y+1))){
        NewNode = MapSearchNode( x, y+1);
        setNode(NewNode);
        astarsearch->AddSuccessor( NewNode );
    }

    return true;
}

float MapSearchNode::GetCost( MapSearchNode &successor ) {
    return (float) GetMap(x, y);
}

int MapSearchNode::GetMap( int xx, int yy ){
    if( xx < 0 || xx >= (MAP_WIDTH) || yy < 0 || yy >=(MAP_HEIGHT)){
        return 9;
    }
    return world_map[(yy*(MAP_WIDTH))+xx];
}

void MapSearchNode::setNode(MapSearchNode &NewNode){
    NewNode.MAP_WIDTH=this->MAP_WIDTH;
    NewNode.MAP_HEIGHT=this->MAP_HEIGHT;
    NewNode.world_map=new int[MAP_WIDTH*MAP_HEIGHT];
    for (unsigned int i = 0; i < MAP_WIDTH; ++i) {
        for (unsigned int j = 0; j < MAP_HEIGHT; ++j) {
            NewNode.world_map[i + j * MAP_WIDTH] = this->world_map[i + j * MAP_WIDTH];
        }
    }
}
MapSearchNode::MapSearchNode() {
    MAP_HEIGHT=MAP_WIDTH=0;
    x = y = 0;
    world_map= nullptr;
}

MapSearchNode::MapSearchNode(int px, int py) {
    MAP_HEIGHT=MAP_WIDTH=0;
    x=px;
    y=py;
    world_map=nullptr;
}

void MapSearchNode::startNode(int width,int height, const int *map) {
    MAP_HEIGHT=height;
    MAP_WIDTH=width;
    world_map=new int[height*width];
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            world_map[i + j * width] = map[i + j * width];
        }
    }
}




