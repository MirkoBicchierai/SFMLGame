#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "MainCharacter.h"
#include "config.cpp"

MainCharacter::MainCharacter(sf::RenderWindow &window) : BaseStatistic() {
    entityTexture.loadFromFile(IMG_PLAYER_ROOT"/Normal_Player.png");
    bowTexture.loadFromFile(IMG_PLAYER_ROOT"/Bow_Player.png");
    shieldTexture.loadFromFile(IMG_PLAYER_ROOT"/Shield_Player.png");

    moveSpeed=6;

    swordRect.height = dim;
    swordRect.width = dim;
    swordRect.left = leftNormalSword;

    magicRect.height = dim;
    magicRect.width = dim;
    magicRect.left = leftNormalMagic;

    arrow = 1;
    bowRect.height = dim;
    bowRect.width = dim;
    bowRect.left = leftNormalBow;

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(sf::Vector2f(1, 1));
    sourceRect.height = dim;
    sourceRect.width = dim;
    sourceRect.top = upNormal;
    sourceRect.left = leftNormal;
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(((window.getSize().x)/2.f)+200,((window.getSize().y)/2.f)-32);
    camera.setCenter(entitySprite.getPosition().x+32,entitySprite.getPosition().y+32);
    camera.setSize(window.getSize().x, window.getSize().y);
    timeSword=40;
    sword=0;

    timeMagic=50;
    magic=0;

    timeBow=45;
    bow=0;

    aniArrow=false;
    secShield=5;
    shield = false;
    spell=false;

    //GUI
    textureGUIShield.loadFromFile(IMG_ROOT"/GUI/Shield.png");
    shieldSprite.setTexture(textureGUIShield);
    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");
    textTimeShield.setFont(font);

    textArrow.setFont(font);
    textArrow.setCharacterSize(24);
    textArrow.setFillColor(sf::Color::White);
    textArrow.setPosition((camera.getCenter().x + window.getSize().x / 2.f) - 56,camera.getCenter().y - (window.getSize().y / 2.f) + 45);
    textArrow.setString("x " + std::to_string(arrow));
    arrowGUI.setArrowGUI(camera.getCenter().x + window.getSize().x / 2.f,camera.getCenter().y - (window.getSize().y / 2.f) + 40 + 38, 180.f);
}

void MainCharacter::reset(int pos) {
    entitySprite.setTexture(entityTexture);
    sourceRect.top = pos;
    sourceRect.left = leftNormal;
    entitySprite.setTextureRect(sourceRect);
}

void MainCharacter::setTextureBow() {
    if (sourceRect.top == topMoveRight) {
        bowRect.top = RightBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveDown) {
        bowRect.top = DownBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveLeft) {
        bowRect.top = LeftBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveUp) {
        bowRect.top = UpBow;
        entitySprite.setTextureRect(bowRect);
    }
    entitySprite.setTexture(bowTexture);
    entitySprite.setTextureRect(bowRect);
}

void MainCharacter::setNormalTexture() {
    entitySprite.setTexture(entityTexture);
}

void MainCharacter::setTextureShield() {
    entitySprite.setTexture(shieldTexture);
    shield = true;
}

void MainCharacter::drawPlayer(sf::RenderWindow &window,sf::Clock clockShield) {
    window.draw(entitySprite);

    //draw timer shield e texture GUI
    if(shield) {
        shieldSprite.setPosition(-5 + camera.getCenter().x + window.getSize().x / 2.f - 32, camera.getCenter().y - (window.getSize().y / 2.f) + 40 + 40);
        window.draw(shieldSprite);
        std::string x = std::to_string(secShield-clockShield.getElapsedTime().asSeconds());
        x = x.substr(0,3);
        textTimeShield.setString(x);
        textTimeShield.setPosition(-5 + camera.getCenter().x + window.getSize().x / 2.f - 72, camera.getCenter().y - (window.getSize().y / 2.f) + 40 + 40);
        window.draw(textTimeShield);
    }

    // draw GUI
    arrowGUI.drawArrow(window);
    hearth.drawHeart(window);
    window.draw(textArrow);

    //draw della fireball o della freccia in caso sia partita l'animazione dal main
    if (ball.animationBall)
        ball.drawFireBall(window);

    if (arrowPlayer.stay)
        arrowPlayer.drawArrow(window);
}

sf::IntRect MainCharacter::getsourceRect() {
    return sourceRect; }

int MainCharacter::swordAttack() {
    if (swordRect.left == finalSwordAttack)
        swordRect.left = leftNormalSword;
    else
        swordRect.left += dim;

    if (sourceRect.top == topMoveRight) {
        swordRect.top = RightSword;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == topMoveDown) {
        swordRect.top = DownSword;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == topMoveLeft) {
        swordRect.top = LeftSword;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == topMoveUp) {
        swordRect.top = UpSword;
        entitySprite.setTextureRect(swordRect);
    }
    return swordRect.left;
}

int MainCharacter::magicAttack() {
    if (magicRect.left == finalMagicAttack)
        magicRect.left = leftNormalMagic;
    else
        magicRect.left += dim;

    if (sourceRect.top == topMoveRight) {
        magicRect.top = RightMagic;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == topMoveDown) {
        magicRect.top = DownMagic;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == topMoveLeft) {
        magicRect.top = LeftMagic;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == topMoveUp) {
        magicRect.top = UpMagic;
        entitySprite.setTextureRect(magicRect);
    }
    return magicRect.left;
}

int MainCharacter::bowAttack() {
    if (bowRect.left == finalBowAttack)
        bowRect.left = leftNormalBow;
    else
        bowRect.left += dim;

    if (sourceRect.top == topMoveRight) {
        bowRect.top = RightBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveDown) {
        bowRect.top = DownBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveLeft) {
        bowRect.top = LeftBow;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == topMoveUp) {
        bowRect.top = UpBow;
        entitySprite.setTextureRect(bowRect);
    }
    return bowRect.left;
}

void MainCharacter::movePlayer(char direction, sf::RenderWindow &window,std::vector<Tile>tile) {
    float x=0,y=0;

    if (sourceRect.left == moveFinal)
        sourceRect.left = leftNormal;
    else
        sourceRect.left += leftNormal+dim;

    if (direction == 'u') {
        sourceRect.top = topMoveUp;
        x=0;
        y=-moveSpeed;
    } else if (direction == 'd') {
        sourceRect.top = topMoveDown;
        x=0;
        y=moveSpeed;
    } else if (direction == 'l') {
        sourceRect.top = topMoveLeft;
        x=-moveSpeed;
        y=0;
    } else if (direction == 'r') {
        sourceRect.top = topMoveRight;
        x=moveSpeed;
        y=0;
    }
    if(!controlMove(tile,direction)){
        x=0;
        y=0;
    }
    entitySprite.setTextureRect(sourceRect);
    entitySprite.move(x,y);
    moveGUI(x,y,window);
}

bool MainCharacter::controlMove(std::vector<Tile> &tile,char direction) {

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(32, 48));
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(entitySprite.getPosition().x+16,entitySprite.getPosition().y+8);

    float x=0,y=0;
    if (direction == 'u') {
        x=0;
        y=-moveSpeed;
    } else if (direction == 'd') {
        x=0;
        y=moveSpeed;
    } else if (direction == 'l') {
        x=-moveSpeed;
        y=0;
    } else if (direction == 'r') {
        x=moveSpeed;
        y=0;
    }

    rectangle.move(x,y);
    bool check=true;
    for(const auto& i:tile){
        if (i.type == "wall") {
            if (rectangle.getGlobalBounds().intersects(i.spriteShow.getGlobalBounds()))
                 check = false;
        }
    }
    return check;
}

void MainCharacter::moveGUI(float x, float y,sf::RenderWindow &window) {
    camera.move(x, y);
    arrowGUI.arrowSprite.move(x,y);
    textArrow.move(x,y);
    textArrow.setString("x " + std::to_string(arrow));
    hearth.moveHeart(x,y);
    window.setView(camera);
}

sf::Sprite MainCharacter::getSprite() {
    return entitySprite;
}

void MainCharacter::resetPlayer(sf::RenderWindow &window) {
    moveSpeed=6;
    arrow = 1;

    sourceRect.top = upNormal;
    sourceRect.left = leftNormal;
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(((window.getSize().x)/2.f)-32,((window.getSize().y)/2.f)-32);
    camera.setCenter(entitySprite.getPosition().x+32,entitySprite.getPosition().y+32);

    sword=0;
    magic=0;
    bow=0;

    aniArrow=false;
    shield = false;
    spell=false;

    //GUI
    textArrow.setPosition((camera.getCenter().x + window.getSize().x / 2.f) - 56,camera.getCenter().y - (window.getSize().y / 2.f) + 45);
    textArrow.setString("x " + std::to_string(arrow));
    arrowGUI.setArrowGUI(camera.getCenter().x + window.getSize().x / 2.f,camera.getCenter().y - (window.getSize().y / 2.f) + 40 + 38, 180.f);
    hearth.setCenter(window);
}

