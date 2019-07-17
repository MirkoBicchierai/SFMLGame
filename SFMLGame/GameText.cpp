#include "GameText.h"
#include "config.cpp"

void GameText::drawGameText(sf::RenderWindow &window) {
    window.draw(drawText);
}

GameText::GameText(std::string text,MainCharacter &mainCharacter) {
    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");
    drawText.setFont(font);
    drawText.setString(text);
    dimension = drawText.getGlobalBounds().left+drawText.getGlobalBounds().width;
    drawText.setString(text[0]);
    drawText.setPosition(mainCharacter.getSprite().getPosition().x- (dimension/2) +64,mainCharacter.getSprite().getPosition().y-64);
    drawText.setScale(0.8,0.8);
    this->text=std::move(text);
}

void GameText::checkString() {
    if(advanceText.getElapsedTime().asMilliseconds()>=80.f){
        int sizeText = text.size();
        int sizeDraw=drawText.getString().getSize();
        if(sizeText!=sizeDraw){
            drawText.setString(drawText.getString()+text[sizeDraw]);
        }
        advanceText.restart();
    }
}

void GameText::moveText(MainCharacter &mainCharacter) {
    drawText.setPosition(mainCharacter.getSprite().getPosition().x- (dimension/2) +64,mainCharacter.getSprite().getPosition().y-64);
}
