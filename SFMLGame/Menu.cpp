#include "Menu.h"
#include "config.cpp"
Menu::Menu() {

    float width=1088;
    float height=704;

    sizeSelectedItem=54;
    sizeNotSelectedItem=30;
    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f((width/2)-32 ,-(sizeSelectedItem-sizeNotSelectedItem)+32+height/(MAX_NUMBER_ITEMS_MENU+1)*1));
    menu[0].setCharacterSize(sizeSelectedItem);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("Tutorial");
    menu[1].setPosition(sf::Vector2f((width/2)-32,32+height/(MAX_NUMBER_ITEMS_MENU+1)*2));
    menu[1].setCharacterSize(sizeNotSelectedItem);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f((width/2)-32,32+height/(MAX_NUMBER_ITEMS_MENU+1)*3));
    menu[2].setCharacterSize(sizeNotSelectedItem);

    selectedItemIndex=0;

    texture.loadFromFile(IMG_PLAYER_ROOT"/Bow_Player.png");
    sprite.setTexture(texture);
    sf::IntRect rect;
    rect.left=64*8;
    rect.width=64;
    rect.height=64;
    rect.top=64*19;
    sprite.setTextureRect(rect);
    sprite.setPosition((width/2)-128,12+ height/(MAX_NUMBER_ITEMS_MENU+1)*1);

    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setString(TITLE);
    title.setPosition(width/2 -112,height/10);
    titleSprite1.setTexture(texture);
    titleSprite2.setTexture(texture);
    rect.left=64*2;
    rect.width=64;
    rect.height=64;
    rect.top=64*20;
    titleSprite1.setTextureRect(rect);
    titleSprite2.setTextureRect(rect);
    titleSprite1.setPosition(width/3 -32,-32+ height/10);
    titleSprite2.setPosition((width-width/3)-48,-32+height/10);

    textureBackground.loadFromFile(IMG_ROOT"/sfondo.jpg");
    background.setTexture(textureBackground);
}
void Menu::moveDown(){
    if(selectedItemIndex +1 <MAX_NUMBER_ITEMS_MENU){
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        menu[selectedItemIndex].setCharacterSize(sizeNotSelectedItem);
        menu[selectedItemIndex].setPosition(sf::Vector2f(menu[selectedItemIndex].getPosition().x ,(sizeSelectedItem-sizeNotSelectedItem)+menu[selectedItemIndex].getPosition().y));
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        menu[selectedItemIndex].setCharacterSize(sizeSelectedItem);
        menu[selectedItemIndex].setPosition(sf::Vector2f(menu[selectedItemIndex].getPosition().x ,-(sizeSelectedItem-sizeNotSelectedItem)+menu[selectedItemIndex].getPosition().y));
        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y +172);
    }
}
void Menu::moveUp(){
    if(selectedItemIndex -1 >=0){
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        menu[selectedItemIndex].setCharacterSize(sizeNotSelectedItem);
        menu[selectedItemIndex].setPosition(sf::Vector2f(menu[selectedItemIndex].getPosition().x ,(sizeSelectedItem-sizeNotSelectedItem)+menu[selectedItemIndex].getPosition().y));
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
        menu[selectedItemIndex].setCharacterSize(sizeSelectedItem);
        menu[selectedItemIndex].setPosition(sf::Vector2f(menu[selectedItemIndex].getPosition().x ,-(sizeSelectedItem-sizeNotSelectedItem)+menu[selectedItemIndex].getPosition().y));
        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y -172);
    }
}
void Menu::draw(sf::RenderWindow &window){
    window.draw(background);
    for (int i = 0; i < MAX_NUMBER_ITEMS_MENU; ++i) {
        window.draw(menu[i]);
    }
    window.draw(sprite);
    window.draw(title);
    window.draw(titleSprite1);
    window.draw(titleSprite2);
}

int Menu::getSelectedItem(){
    return selectedItemIndex;
}