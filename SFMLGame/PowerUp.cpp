#include "PowerUp.h"
#include "config.cpp"
#define MAX_NUMBER_POWER_UP 3

PowerUp::PowerUp() {
    selectedItem=1;
    textureBackground.loadFromFile(IMG_ROOT"/sfondo.jpg");
    background.setTexture(textureBackground);
}

void PowerUp::moveRight() {

}

void PowerUp::moveLeft() {

}

int PowerUp::getSelectedItem() {
    return 0;
}

void PowerUp::draw(sf::RenderWindow &window) {
    window.draw(background);
}


