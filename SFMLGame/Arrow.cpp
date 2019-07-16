#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "config.cpp"
#include "Enemy.h"
Arrow::Arrow() {
    arrowTexture.loadFromFile(IMG_PLAYER_OBJ_ROOT"/Arrow.png");
    arrowSprite.setTexture(arrowTexture);
    arrowRect.height = dimArrow;
    arrowRect.width = dimArrow;
    arrowRect.left = LeftNormalArrow;
    arrowSprite.setTextureRect(arrowRect);
    moveSpeed=45;
    animationArrow=false;
    stay=false;
    arrowFor=0;
    pick=false;
    colorSprite=arrowSprite.getColor();
    damage=2;
}

void Arrow::drawArrow(sf::RenderWindow &window) {
    if(!animationArrow && stay)
        arrowSprite.setColor(sf::Color::Yellow);
    else
        arrowSprite.setColor(colorSprite);
    window.draw(arrowSprite);
}

void Arrow::setRect(sf::IntRect player,float x, float y) {
    arrowSprite.setRotation(baseRotation);
    if (player.top == topMoveRight) {
        arrowSprite.setRotation(RightRotation);
        y=y+48;
    }
    if (player.top == topMoveDown) {
        arrowSprite.setRotation(DownRotation);
        x=x+16;
        y=y+32;
    }
    if (player.top == topMoveLeft) {
        arrowSprite.setRotation(LeftRotation);
        y=y+16;
    }
    if (player.top == topMoveUp) {
        arrowSprite.setRotation(UpRotation);
        y=y+48;
        x=x+48;
    }
    arrowRect.top=TopNormalArrow;
    arrowRect.left=LeftNormalArrow;
    clock.restart();
    arrowSprite.setTextureRect(arrowRect);
    arrowSprite.setPosition(x,y);
}

void Arrow::animation(std::vector<Tile> &tile,std::vector<Enemy*> &enemyVec) {
    float x=0,y=0;
    if (arrowSprite.getRotation() == RightRotation) {
        x=moveSpeed;
        y=0;
    }
    if (arrowSprite.getRotation() == DownRotation) {
        x=0;
        y=moveSpeed;
    }
    if (arrowSprite.getRotation() == LeftRotation) {
        x=-moveSpeed;
        y=0;
    }
    if (arrowSprite.getRotation() == UpRotation) {
        x=0;
        y=-moveSpeed;
    }
    if(!controlMove(tile)) {
        arrowFor=8;
        arrowRect.left = LeftNormalArrow;
        arrowRect.top = TopNormalArrow;
    }else{
        arrowSprite.move(x,y);

        for (int i = 0; i < enemyVec.size(); ++i) {
            if(arrowSprite.getGlobalBounds().intersects(enemyVec[i]->entitySprite.getGlobalBounds())){
                if(enemyVec[i]->life!=0) {
                    enemyVec[i]->takeDamage(damage);
                    arrowFor=8;
                    arrowRect.left = LeftNormalArrow;
                    arrowRect.top = TopNormalArrow;
                    return;
                }
            }
        }

        if(arrowRect.left==dimArrow && arrowRect.top==dimArrow) {
            arrowRect.left = LeftNormalArrow;
            arrowRect.top = TopNormalArrow;
        }else {
            if((arrowRect.left==0 && arrowRect.top==dimArrow)||(arrowRect.left==0 && arrowRect.top==0))
                arrowRect.left = dimArrow;
            else{
                if(arrowRect.left==dimArrow && arrowRect.top==0) {
                    arrowRect.left = LeftNormalArrow;
                    arrowRect.top = dimArrow;
                }
            }
        }
    }
    arrowSprite.setTextureRect(arrowRect);
}

void Arrow::setArrowGUI(float X, float Y, float rotation){
    arrowSprite.setRotation(rotation);
    arrowSprite.setPosition(X,Y);
}

bool Arrow::controlMove(std::vector<Tile> &tile) {

    bool check=true;
    for(const auto& i:tile){
        if (i.type == "wall" || i.type == "closed_door_silver" || i.type == "closed_door_gold" || i.type=="gate" || i.type=="water" ) {
            if (arrowSprite.getGlobalBounds().intersects(i.spriteCollision.getGlobalBounds()))
                check = false;
        }
    }
    return check;
}
