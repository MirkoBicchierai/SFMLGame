#include "FinalBoss.h"
#include "config.cpp"

FinalBoss::FinalBoss() {

    entityTexture.loadFromFile(IMG_ENEMY_ROOT"/FinalBoss.png");

    heart.setHearthBoss(sf::Vector2f(spawnBossX,spawnBossY));

    swordRect.height=dimBos;
    swordRect.width=dimBos;

    sourceRect.width=dimBos;
    sourceRect.height=dimBos;
    sourceRect.left=0;
    sourceRect.top=topBossDown;

    entitySprite.setTexture(entityTexture);
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(spawnBossX,spawnBossY);

    attackBufferSound.loadFromFile(AUDIO_ROOT"/AttackEnemy.wav");
    soundAttack.setBuffer(attackBufferSound);
    soundAttack.setVolume(3);

    bufferStep.loadFromFile(AUDIO_ROOT"/Step.wav");
    soundStep.setBuffer(bufferStep);
    soundStep.setVolume(0.5);

    life=10;
    moveSpeed=5;

    damage=2;
    AStarColl.setSize(sf::Vector2f(1,1));
    AStarColl.setPosition(entitySprite.getPosition().x+127,entitySprite.getPosition().y+127);
    AStarColl.setFillColor(sf::Color::Red);
    aniAttack=false;

    armor.setPosition(entitySprite);
    armorPoint=3;
}

void FinalBoss::drawBoss(sf::RenderWindow &window) {
    armor.drawArmor(window);
    heart.drawHeart(window);
    window.draw(entitySprite);
}

void FinalBoss::aStarSearch(Tile &tilePlayer, Tile &tileEnemy, int *map, int width, int height) {
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
                structListBoss list;
                list.x=node->x;
                list.y=node->y;
                path.emplace_back(list);
            }
            structListBoss V[path.size()];
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

void FinalBoss::checkAStarBoss(TileMap &map, MainCharacter &mainCharacter, std::vector<Tile> &tile) {
    if(life>0) {
            entitySprite.setTextureRect(sourceRect);
            Tile player;
            Tile enemy;
            mainCharacter.AStarColl.setPosition(mainCharacter.entitySprite.getPosition().x+31,mainCharacter.entitySprite.getPosition().y+60);
            for(auto& j:map.tile) {
                if(mainCharacter.AStarColl.getGlobalBounds().intersects(j.spriteCollision.getGlobalBounds())) {
                    player=j;
                    break;
                }
            }
            for(auto& k:map.tile) {
                if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds())) {
                    enemy=k;
                    break;
                }
            }
            aStarSearch(player,enemy,map.world_map,map.width,map.height);
    }
}

void FinalBoss::moveAStarBoss(std::vector<Tile> &tile, MainCharacter &mainCharacter) {
    if(distanceBetweenTwoSprite(mainCharacter.getSprite(),entitySprite)<80){
        aniAttack=true;
        return;
    }
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
                    moveBoss('d',mainCharacter);
                } else if (tile[k].j<enemy.j) {
                    moveBoss('u',mainCharacter);
                } else if (tile[k].i>enemy.i) {
                    moveBoss('r',mainCharacter);
                } else if (tile[k].i<enemy.i) {
                    moveBoss('l',mainCharacter);
                }
                break;
            }
        }
        for(auto& k:tile) {
            if(AStarColl.getGlobalBounds().intersects(k.spriteCollision.getGlobalBounds())&& (k.type=="floor" || k.type=="obj" || k.type=="gold_key" || k.type=="silver_key")) {
                enemy=k;
                break;
            }
        }
        if(enemy.i==i && enemy.j==j)
            path.pop_back();
    }
}

void FinalBoss::moveBoss(char direction, MainCharacter &mainCharacter) {

    sf::Sprite test;
    test.setPosition(AStarColl.getPosition());
    test.setTextureRect(sf::IntRect(AStarColl.getSize().x,AStarColl.getSize().y,0,0));

    if(distanceBetweenTwoSprite(mainCharacter.getSprite(),test)>80){
        if (sourceRect.left == maxLeftMove)
            sourceRect.left = 0;
        else
            sourceRect.left += dimBos;

        if (direction=='u') {
            entitySprite.move(0,-moveSpeed);
            heart.moveHeart(0,-moveSpeed);
            armor.moveArmor(0,-moveSpeed);
            sourceRect.top =topBossUp;
        }
        if (direction=='d') {
            entitySprite.move(0,moveSpeed);
            heart.moveHeart(0,moveSpeed);
            armor.moveArmor(0,moveSpeed);
            sourceRect.top =topBossDown;
        }
        if (direction=='l') {
            entitySprite.move(-moveSpeed,0);
            heart.moveHeart(-moveSpeed,0);
            armor.moveArmor(-moveSpeed,0);
            sourceRect.top =topBossLeft;
        }
        if (direction=='r') {
            entitySprite.move(moveSpeed,0);
            heart.moveHeart(moveSpeed,0);
            armor.moveArmor(moveSpeed,0);
            sourceRect.top =topBossRight;
        }
        entitySprite.setTextureRect(sourceRect);
        soundStepControl();
        AStarColl.setPosition(entitySprite.getPosition().x+127,entitySprite.getPosition().y+127);
    } else
        aniAttack=true;
}

int FinalBoss::animationAttackBoss() {
    if (swordRect.left == maxLeftAttack)
        swordRect.left = 0;
    else
        swordRect.left += dimBos;

    if (sourceRect.top == topBossRight) {
        swordRect.top = topSwordRightBoss;
    }
    if (sourceRect.top == topBossDown) {
        swordRect.top = topSwordDownBoss;
    }
    if (sourceRect.top == topBossLeft) {
        swordRect.top = topSwordLeftBoss;
    }
    if (sourceRect.top == topBossUp) {
        swordRect.top = topSwordUpBoss;
    }

    entitySprite.setTextureRect(swordRect);
    return swordRect.left;
}

void FinalBoss::takeDamage(int dmg) {
    if(armorPoint<=0){
        life=life-dmg;
        heart.damageControl(life);
    }else{
        armorPoint=armorPoint-dmg;
        armor.damageControl(armorPoint);
    }
}
