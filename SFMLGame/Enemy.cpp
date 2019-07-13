#include "Enemy.h"
#include "config.cpp"
void Enemy::drawEnemy(sf::RenderWindow &window) {
    window.draw(entitySprite);
}

Enemy::Enemy(float x, float y,std::string &file,int distance,int dmg) {
    entityTexture.loadFromFile(IMG_ENEMY_ROOT"/"+file+".png");
    type=file;
    entitySprite.setTexture(entityTexture);
    sourceRect.left=0;
    sourceRect.top=0;
    sourceRect.width=dim;
    sourceRect.height=dim;
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(x,y);
    AStarColl.setFillColor(sf::Color::Red);
    AStarColl.setSize(sf::Vector2f(1,1));
    AStarColl.setPosition(entitySprite.getPosition().x+31,entitySprite.getPosition().y+31);
    moveSpeed=5;
    aggroDistance=distance;
    life = 3;
    damage=dmg;
    dieRect.left=0;
    dieRect.top=dieTopEnemy;
    dieRect.width=64;
    dieRect.height=64;
    aniAttack=false;
    swordRect.height=dim;
    swordRect.width=dim;
    swordRect.left=0;
    idle=true;
    IdleRect.width=dim;
    IdleRect.height=dim;
    IdleRect.top=0;
    IdleRect.left=0;
}

void Enemy::checkAStar(TileMap &map, MainCharacter &mainCharacter,std::vector<Tile> &tile) {
    if(life>0) {
        //distance by two point
        if(distanceBetweenTwoSprite(mainCharacter.getSprite(),entitySprite)<aggroDistance){
            entitySprite.setTextureRect(sourceRect);
            idle=false;
            Tile player;
            Tile enemy;
            mainCharacter.AStarColl.setPosition(mainCharacter.entitySprite.getPosition().x+31,mainCharacter.entitySprite.getPosition().y+60);
            for(auto& j:map.tile) {
                if(mainCharacter.AStarColl.getGlobalBounds().intersects(j.spriteCollision.getGlobalBounds()) && (j.type=="floor" || j.type=="obj")) {
                    player=j;
                    break;
                }
            }
            for(auto& k:map.tile) {
                if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds()) && (k.type=="floor" || k.type=="obj")) {
                    enemy=k;
                    break;
                }
            }
            aStarSearch(player,enemy,map.world_map,map.width,map.height);
        }
        else
            idle=true;
    }
}
void Enemy::moveAStar(std::vector<Tile> &tile,MainCharacter &mainCharacter){
    if(life > 0 && !path.empty() && !aniAttack) {
        int i = path[path.size()-1].x;
        int j = path[path.size()-1].y;
        Tile enemy;
        for(auto& k:tile) {
            if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds()) && (k.type=="floor" || k.type=="obj")) {
                enemy=k;
                break;
            }
        }
        for (int k = 0; k < tile.size(); ++k) {
            if (i == tile[k].i && j == tile[k].j) {
                if (tile[k].j>enemy.j) {
                    moveEnemy('d',mainCharacter);
                } else if (tile[k].j<enemy.j) {
                    moveEnemy('u',mainCharacter);
                } else if (tile[k].i>enemy.i) {
                    moveEnemy('r',mainCharacter);
                } else if (tile[k].i<enemy.i) {
                    moveEnemy('l',mainCharacter);
                }
                break;
            }
        }
        for(auto& k:tile) {
            if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds()) && (k.type=="floor" || k.type=="obj")) {
                enemy=k;
                break;
            }
        }
        if(enemy.i==i && enemy.j==j)
            path.pop_back();
    }
}

void Enemy::aStarSearch(Tile &tilePlayer,Tile &tileEnemy,int *map,int width,int height) {
    sf::Clock test;
    AStarSearch<MapSearchNode> aStarSearch;
    unsigned int SearchCount = 0;
    const unsigned int NumSearches = 1;
    path.clear();
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
        do{
            SearchState = aStarSearch.SearchStep();
        }while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED ){

            aStarSearch.GetSolutionStart();
            MapSearchNode *node;
            //node->PrintNodeInfo();
            for( ;; ){
                node = aStarSearch.GetSolutionNext();
                if( !node ){
                    break;
                }
                //node->PrintNodeInfo();
                structList list;
                list.x=node->x;
                list.y=node->y;
                path.emplace_back(list);
            }
            structList V[path.size()];
            int c=0;
            for (int i = 0; i < path.size(); ++i) {
                V[i]=path[path.size()-1-i];
                c++;
            }
            for (int j = 0; j <c ; ++j) {
                path[j]=V[j];
            }
            // Once you're done with the solution you can free the nodes up
            aStarSearch.FreeSolutionNodes();
        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ){
            cout << "Search terminated. Did not find goal state\n";

        }
        SearchCount ++;
        aStarSearch.EnsureMemoryFreed();
    }
}

void Enemy::moveEnemy(char direction,MainCharacter &mainCharacter) {

    if(distanceBetweenTwoSprite(mainCharacter.getSprite(),entitySprite)>64){
        if (sourceRect.left == moveFinalEnemy)
            sourceRect.left = leftNormalEnemy;
        else
            sourceRect.left += leftNormalEnemy+dimEnemy;

        if (direction=='u') {
            entitySprite.move(0,-moveSpeed);
            sourceRect.top =topMoveUpEnemy;
            AStarColl.setPosition(entitySprite.getPosition().x+31,entitySprite.getPosition().y+61);
        }
        if (direction=='d') {
            entitySprite.move(0,moveSpeed);
            sourceRect.top =topMoveDownEnemy;
            AStarColl.setPosition(entitySprite.getPosition().x+31,entitySprite.getPosition().y);
        }
        if (direction=='l') {
            entitySprite.move(-moveSpeed,0);
            sourceRect.top =topMoveLeftEnemy;
            AStarColl.setPosition(entitySprite.getPosition().x+61,entitySprite.getPosition().y+31);
        }
        if (direction=='r') {
            entitySprite.move(moveSpeed,0);
            sourceRect.top =topMoveRightEnemy;
            AStarColl.setPosition(entitySprite.getPosition().x,entitySprite.getPosition().y+31);
        }
        entitySprite.setTextureRect(sourceRect);
    } else
        aniAttack=true;
}

float Enemy::animationDie(){
    entitySprite.setTextureRect(dieRect);
    float x=dieRect.left;
    dieRect.left=dieRect.left+dim;
    return x;
}

void Enemy::attackPlayer(MainCharacter &mainCharacter){

    sf::RectangleShape swordRec;
    swordRec.setPosition(entitySprite.getPosition());

    if (sourceRect.top == topMoveUp) {
        swordRec.setSize(sf::Vector2f(48,10));
        swordRec.setPosition(swordRec.getPosition().x+8,swordRec.getPosition().y-10);
    }
    if (sourceRect.top == topMoveDown) {
        swordRec.setSize(sf::Vector2f(48,10));
        swordRec.setPosition(swordRec.getPosition().x+8,swordRec.getPosition().y+64);
    }
    if (sourceRect.top == topMoveLeft) {
        swordRec.setSize(sf::Vector2f(10,48));
        swordRec.setPosition(swordRec.getPosition().x-10,swordRec.getPosition().y+8);
    }
    if (sourceRect.top == topMoveRight) {
        swordRec.setSize(sf::Vector2f(10,48));
        swordRec.setPosition(swordRec.getPosition().x+64,swordRec.getPosition().y+8);
    }

    if(!mainCharacter.shield)
        if(mainCharacter.entitySprite.getGlobalBounds().intersects(swordRec.getGlobalBounds()))
            mainCharacter.life=mainCharacter.life-damage;
}

int Enemy::animationAttack(int x) {
    if (swordRect.left == x)
        swordRect.left = leftNormalSword;
    else
        swordRect.left += dim;

    if (sourceRect.top == topMoveRight) {
        swordRect.top = rightSwordEnemy;
    }
    if (sourceRect.top == topMoveDown) {
        swordRect.top = downSwordEnemy;
    }
    if (sourceRect.top == topMoveLeft) {
        swordRect.top = leftSwordEnemy;
    }
    if (sourceRect.top == topMoveUp) {
        swordRect.top = upSwordEnemy;
    }
    if(type!="normal")
        swordRect.top = swordRect.top+offset;

    entitySprite.setTextureRect(swordRect);
    return swordRect.left;
}

int Enemy::animationIdle() {
    if (swordRect.left == MaxLeftIdle)
        swordRect.left = 0;
    else
        swordRect.left += dim;

    if (sourceRect.top == topMoveRight) {
        swordRect.top = IdleRightTop;
    }
    if (sourceRect.top == topMoveDown) {
        swordRect.top = IdleDownTop;
    }
    if (sourceRect.top == topMoveLeft) {
        swordRect.top = IdleLeftTop;
    }
    if (sourceRect.top == topMoveUp) {
        swordRect.top = IdleTopUp;
    }

    entitySprite.setTextureRect(swordRect);
    return swordRect.left;
}
