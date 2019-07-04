#include <SFML/Graphics.hpp>
#include "Arrow.h"
#include "config.cpp"

Arrow::Arrow() {
    arrowTexture.loadFromFile(IMG_PLAYER_OBJ_ROOT"/Arrow.png");
    arrowSprite.setTexture(arrowTexture);
    arrowRect.height = dimArrow;
    arrowRect.width = dimArrow;
    arrowRect.left = LeftNormalArrow;
    arrowSprite.setTextureRect(arrowRect);
    moveSpeed=40;
    animationArrow=false;
    stay=false;
    arrowFor=0;
    pick=false;
    colorSprite=arrowSprite.getColor();
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

void Arrow::animation() {
    if (arrowSprite.getRotation() == RightRotation) {
        arrowSprite.move(moveSpeed,0);
    }
    if (arrowSprite.getRotation() == DownRotation) {
        arrowSprite.move(0,moveSpeed);
    }
    if (arrowSprite.getRotation() == LeftRotation) {
        arrowSprite.move(-moveSpeed,0);
    }
    if (arrowSprite.getRotation() == UpRotation) {
        arrowSprite.move(0,-moveSpeed);
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
    arrowSprite.setTextureRect(arrowRect);
}

void Arrow::setArrowGUI(float X, float Y, float rotation){
    arrowSprite.setRotation(rotation);
    arrowSprite.setPosition(X,Y);
}