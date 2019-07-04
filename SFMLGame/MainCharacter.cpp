#include <utility>

#include "MainCharacter.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
MainCharacter::MainCharacter(sf::RenderWindow &window) : BaseStatistic() {
    entityTexture.loadFromFile("../img/Player/Normal_Player.png");
    bowTexture.loadFromFile("../img/Player/Bow_Player.png");
    shieldTexture.loadFromFile("../img/Player/Shield_Player.png");

    moveSpeed=6;

    swordRect.height = 64;
    swordRect.width = 64;
    swordRect.left = 0;

    magicRect.height = 64;
    magicRect.width = 64;
    magicRect.left = 0;

    arrow = 1;
    bowRect.height = 64;
    bowRect.width = 64;
    bowRect.left = 0;

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(sf::Vector2f(1, 1));
    sourceRect.height = 64;
    sourceRect.width = 64;
    sourceRect.top = 64 * 8;
    sourceRect.left = 0;
    entitySprite.setTextureRect(sourceRect);
    entitySprite.setPosition(((window.getSize().x)/2.f)-32,((window.getSize().y)/2.f)-32);
    camera.setCenter(entitySprite.getPosition().x+32,entitySprite.getPosition().y+32);
    camera.setSize(1088.f, 704.f);
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
    textureGUIShield.loadFromFile("../img/GUI/Shield.png");
    shieldSprite.setTexture(textureGUIShield);
    font.loadFromFile("../font/Handwritingg.ttf");
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
    sourceRect.height = 64;
    sourceRect.width = 64;
    sourceRect.top = pos;
    sourceRect.left = 0;
    entitySprite.setTextureRect(sourceRect);
}
void MainCharacter::setTextureBow() {
    if (sourceRect.top == 64 * 11) {
        bowRect.top = 64 * 19;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 10) {
        bowRect.top = 64 * 18;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 9) {
        bowRect.top = 64 * 17;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 8) {
        bowRect.top = 64 * 16;
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
    if (swordRect.left == 64 * 5)
        swordRect.left = 0;
    else
        swordRect.left += 64;

    if (sourceRect.top == 64 * 11) {
        swordRect.top = 64 * 15;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == 64 * 10) {
        swordRect.top = 64 * 14;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == 64 * 9) {
        swordRect.top = 64 * 13;
        entitySprite.setTextureRect(swordRect);
    }
    if (sourceRect.top == 64 * 8) {
        swordRect.top = 64 * 12;
        entitySprite.setTextureRect(swordRect);
    }
    return swordRect.left;
}

int MainCharacter::magicAttack() {
    if (magicRect.left == 64 * 6)
        magicRect.left = 0;
    else
        magicRect.left += 64;

    if (sourceRect.top == 64 * 11) {
        magicRect.top = 64 * 3;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == 64 * 10) {
        magicRect.top = 64 * 2;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == 64 * 9) {
        magicRect.top = 64 * 1;
        entitySprite.setTextureRect(magicRect);
    }
    if (sourceRect.top == 64 * 8) {
        magicRect.top = 64 * 0;
        entitySprite.setTextureRect(magicRect);
    }
    return magicRect.left;
}

int MainCharacter::bowAttack() {
    if (bowRect.left == 64 * 12)
        bowRect.left = 0;
    else
        bowRect.left += 64;

    if (sourceRect.top == 64 * 11) {
        bowRect.top = 64 * 19;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 10) {
        bowRect.top = 64 * 18;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 9) {
        bowRect.top = 64 * 17;
        entitySprite.setTextureRect(bowRect);
    }
    if (sourceRect.top == 64 * 8) {
        bowRect.top = 64 * 16;
        entitySprite.setTextureRect(bowRect);
    }
    return bowRect.left;
}

void MainCharacter::movePlayer(char direction, sf::RenderWindow &window,std::vector<Tile>tile) {
    float x=0,y=0;

    if (sourceRect.left == 64 * 8)
        sourceRect.left = 0;
    else
        sourceRect.left += 64;

    if (direction == 'u') {
        sourceRect.top = 64 * 8;
        x=0;
        y=-moveSpeed;
    } else if (direction == 'd') {
        sourceRect.top = 64 * 10;
        x=0;
        y=moveSpeed;
    } else if (direction == 'l') {
        sourceRect.top = 64 * 9;
        x=-moveSpeed;
        y=0;
    } else if (direction == 'r') {
        sourceRect.top = 64 * 11;
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
    sf::Sprite clone(entitySprite);

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

    clone.move(x,y);
    bool check=true;
    for(const auto& i:tile){
        if (i.type == "wall") {
            if (clone.getGlobalBounds().intersects(i.spriteCollision.getGlobalBounds()))
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

    sourceRect.top = 64 * 8;
    sourceRect.left = 0;
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

