#include "Enemy.h"
#include "config.cpp"
void Enemy::drawEnemy(sf::RenderWindow &window) {
    window.draw(entitySprite);
}

Enemy::Enemy(float x, float y) {
    entityTexture.loadFromFile("../img/npc/npc1.png");
    entitySprite.setTexture(entityTexture);
    sourceRect.left=0;
    sourceRect.top=0;
    sourceRect.width=64;
    sourceRect.height=64;
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(x,y);
    AStarColl.setFillColor(sf::Color::Red);
    AStarColl.setSize(sf::Vector2f(1,1));
    AStarColl.setPosition(entitySprite.getPosition().x+31,entitySprite.getPosition().y+31);
}

void Enemy::checkAStar(TileMap &map, MainCharacter &mainCharacter) {
    Tile player;
    Tile enemy;
    for(auto& j:map.tile) {
        if(mainCharacter.AStarColl.getGlobalBounds().intersects(j.spriteCollision.getGlobalBounds()) && j.type=="floor") {
            player=j;
            break;
        }
    }
    for(auto& k:map.tile) {
        if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds()) && k.type=="floor") {
            enemy=k;
            break;
        }
    }
    aStarSearch(player,enemy,map.world_map,map.width,map.height);
}

void Enemy::aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height) {

    AStarSearch<MapSearchNode> aStarSearch;
    unsigned int SearchCount = 0;
    const unsigned int NumSearches = 1;

    while(SearchCount < NumSearches){
        // Create a start state
        MapSearchNode nodeStart;
        nodeStart.x = tileEnemy.i;
        nodeStart.y = tileEnemy.j;

        // Define the goal state
        MapSearchNode nodeEnd;
        nodeEnd.x = tilePlayer.i;
        nodeEnd.y = tilePlayer.j;

        //set the node
        nodeStart.startNode(width,height,map);
        nodeEnd.startNode(width,height,map);

        //set algorithm A-star
        aStarSearch.SetStartAndGoalStates( nodeStart, nodeEnd );
        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do{
            SearchState = aStarSearch.SearchStep();
            SearchSteps++;
        }while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED ){

            cout << "Search found goal state\n";
            MapSearchNode *node = aStarSearch.GetSolutionStart();
            int steps = 0;
            node->PrintNodeInfo();
            for( ;; ){
                node = aStarSearch.GetSolutionNext();
                if( !node ){
                    break;
                }
                node->PrintNodeInfo();
                steps ++;

            }
            cout << "Solution steps " << steps << endl;

            // Once you're done with the solution you can free the nodes up
            aStarSearch.FreeSolutionNodes();
        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ){
            cout << "Search terminated. Did not find goal state\n";

        }

        // Display the number of loops the search went through
        cout << "SearchSteps : " << SearchSteps << "\n";
        SearchCount ++;
        aStarSearch.EnsureMemoryFreed();

    }
}