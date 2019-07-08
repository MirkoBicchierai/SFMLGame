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
}

void Enemy::aStarSearch(Tile tilePlayer,Tile tileEnemy,int *map,int width,int height) {
    AStarSearch<MapSearchNode> astarsearch;
    unsigned int SearchCount = 0;

    const unsigned int NumSearches = 1;
    std::cout<<"PlayerX:" <<std::endl;
    std::cout<<tilePlayer.i <<std::endl;

    std::cout<<"PlayerY:" <<std::endl;
    std::cout<<tilePlayer.j <<std::endl;

    std::cout<<"EnemyX:" <<std::endl;
    std::cout<<tileEnemy.i <<std::endl;
    std::cout<<"EnemyY:" <<std::endl;
    std::cout<<tileEnemy.j <<std::endl;

    while(SearchCount < NumSearches){
        // Create a start state
        MapSearchNode nodeStart;
        nodeStart.x = tileEnemy.i;
        nodeStart.y = tileEnemy.j;

        // Define the goal state
        MapSearchNode nodeEnd;
        nodeEnd.x = tilePlayer.i;
        nodeEnd.y = tilePlayer.j;
        // Set Start and goal states
     /*   for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                nodeStart.world_map[i + j * width] = map[i + j * width];
                nodeEnd.world_map[i + j * width] = map[i + j * width];
            }
        }
        */
        astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do{
            SearchState = astarsearch.SearchStep();
            SearchSteps++;

        }
        while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
        {
            cout << "Search found goal state\n";

            MapSearchNode *node = astarsearch.GetSolutionStart();

            int steps = 0;

            node->PrintNodeInfo();
            for( ;; )
            {
                node = astarsearch.GetSolutionNext();

                if( !node )
                {
                    break;
                }

                node->PrintNodeInfo();
                steps ++;

            };

            cout << "Solution steps " << steps << endl;

            // Once you're done with the solution you can free the nodes up
            astarsearch.FreeSolutionNodes();


        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
        {
            cout << "Search terminated. Did not find goal state\n";

        }

        // Display the number of loops the search went through
        cout << "SearchSteps : " << SearchSteps << "\n";

        SearchCount ++;

        astarsearch.EnsureMemoryFreed();

    }
}
