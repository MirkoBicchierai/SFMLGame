#include <SFML/Graphics.hpp>
#include "Arrow.h"

Arrow::Arrow() {
    arrowTexture.loadFromFile("../img/Player_obj/Arrow.png");
    arrowSprite.setTexture(arrowTexture);
    arrowRect.height = 32;
    arrowRect.width = 32;
    arrowRect.left = 0;
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
    arrowSprite.setRotation(0.f);
    if (player.top == 64 * 11) {
        arrowSprite.setRotation(270.f);
        y=y+48;
    }
    if (player.top == 64 * 10) {
        arrowSprite.setRotation(0.f);
        x=x+16;
    }
    if (player.top == 64 * 9) {
        arrowSprite.setRotation(90.f);
        y=y+16;
    }
    if (player.top == 64 * 8) {
        arrowSprite.setRotation(180.f);
        y=y+48;
        x=x+48;
    }
    arrowRect.top=0;
    arrowRect.left=0;
    clock.restart();
    arrowSprite.setTextureRect(arrowRect);
    arrowSprite.setPosition(x,y);
}

void Arrow::animation() {
    if (arrowSprite.getRotation() == 270.f) {
        arrowSprite.move(moveSpeed,0);
    }
    if (arrowSprite.getRotation() == 0.f) {
        arrowSprite.move(0,moveSpeed);
    }
    if (arrowSprite.getRotation() == 90.f) {
        arrowSprite.move(-moveSpeed,0);
    }
    if (arrowSprite.getRotation() == 180.f) {
        arrowSprite.move(0,-moveSpeed);
    }

    if(arrowRect.left==32 && arrowRect.top==32) {
        arrowRect.left = 0;
        arrowRect.top = 0;
    }else {
        if((arrowRect.left==0 && arrowRect.top==32)||(arrowRect.left==0 && arrowRect.top==0))
            arrowRect.left = 32;
        else{
            if(arrowRect.left==32 && arrowRect.top==0) {
                arrowRect.left = 0;
                arrowRect.top = 32;
            }
        }
    }
    arrowSprite.setTextureRect(arrowRect);
}

void Arrow::setArrowGUI(float X, float Y, float rotation){
    arrowSprite.setRotation(rotation);
    arrowSprite.setPosition(X,Y);
}