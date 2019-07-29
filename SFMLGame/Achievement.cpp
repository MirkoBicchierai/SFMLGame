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
    textDraw.setFillColor(sf::Color::Green);
    textDraw.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width+5,sprite.getPosition().y+15);
    textDraw.setCharacterSize(20);
}

void Achievement::drawAchievement(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(textDraw);
}

void Achievement::changePosition(int i,sf::RenderWindow &window ,MainCharacter &player) {
    sprite.setPosition(sprite.getPosition().x,i*(sprite.getGlobalBounds().height+5));
    textDraw.setPosition(textDraw.getPosition().x,+i*(textDraw.getGlobalBounds().height+15));
    sprite.setPosition(5+player.camera.getCenter().x - window.getSize().x / 2.f,5 +player.camera.getCenter().y - window.getSize().y / 2.f +5 + sprite.getPosition().y );
    textDraw.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width+5,sprite.getPosition().y+15);
}
