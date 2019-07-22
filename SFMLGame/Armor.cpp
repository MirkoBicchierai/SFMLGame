#include "Armor.h"
#include "config.cpp"
Armor::Armor() {
    textureArmor.loadFromFile(IMG_ROOT"/GUI/Armor.png");
    ArmorSprite1.setTexture(textureArmor);
    ArmorSprite2.setTexture(textureArmor);
    ArmorSprite3.setTexture(textureArmor);
}

void Armor::drawArmor(sf::RenderWindow &window) {
    window.draw(ArmorSprite1);
    window.draw(ArmorSprite2);
    window.draw(ArmorSprite3);
}

void Armor::moveArmor(float x, float y) {
    ArmorSprite1.move(x,y);
    ArmorSprite2.move(x,y);
    ArmorSprite3.move(x,y);
}

void Armor::setPosition(sf::Sprite boss) {
    ArmorSprite1.setPosition(boss.getPosition().x+12+64,boss.getPosition().y-10 +5 +32);
    ArmorSprite2.setPosition(boss.getPosition().x+32+8+8+64,boss.getPosition().y-10 +5 +32);
    ArmorSprite3.setPosition(boss.getPosition().x+32+32+4+16+64,boss.getPosition().y-10 + 5 +32);
}
