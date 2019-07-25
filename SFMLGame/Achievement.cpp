#include "Achievement.h"
#include "config.cpp"
#include <iostream>
Achievement::Achievement(std::string text, std::string file) {
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setScale(0.15,0.15);
    sprite.setPosition(0,0);
    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");
    textDraw.setFont(font);
    textDraw.setString(text);
    textDraw.setFillColor(sf::Color::Blue);
    textDraw.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width+5,sprite.getPosition().y);
    textDraw.scale(0.8,0.8);
}

void Achievement::drawAchievement(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(textDraw);
}

void Achievement::changePosition(int i,sf::RenderWindow &window ,MainCharacter &player) {
    sprite.setPosition(sprite.getPosition().x,i*(sprite.getGlobalBounds().height+5));
    textDraw.setPosition(textDraw.getPosition().x,+i*(textDraw.getGlobalBounds().height+5));
    sprite.setPosition(player.entitySprite.getPosition().x - window.getSize().x / 2.f +40,5 +player.entitySprite.getPosition().y - window.getSize().y / 2.f +5 + sprite.getPosition().y +25);
    textDraw.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width+5,sprite.getPosition().y);
}
