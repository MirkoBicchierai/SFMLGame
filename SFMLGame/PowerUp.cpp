#include "PowerUp.h"
#include "config.cpp"

PowerUp::PowerUp() {
    priceArrow=40;
    priceFireBall=50;
    priceSword=25;
    priceSpeed=20;
    float width=1088;
    float height=704;
    selectedItem=0;
    textureBackground.loadFromFile(IMG_ROOT"/sfondo.jpg");
    background.setTexture(textureBackground);
    font.loadFromFile(FONT_ROOT"/Handwritingg.ttf");
    sizeSelectedItem=54;
    sizeNotSelectedItem=30;

    nextTxt.loadFromFile(IMG_ROOT"/PowerUp/next.png");
    swordDamage.loadFromFile(IMG_ROOT"/PowerUp/sword.png");
    arrowDamage.loadFromFile(IMG_ROOT"/PowerUp/Arrow.png");
    fireBallDamage.loadFromFile(IMG_ROOT"/PowerUp/FireBall.png");
    speed.loadFromFile(IMG_ROOT"/PowerUp/speed.png");

    coinTexture.loadFromFile(IMG_ROOT"/PowerUp/coin.png");

    title.setFont(font);
    title.setString("Select a PowerUp or go next");
    title.setCharacterSize(sizeNotSelectedItem);
    title.setFillColor(sf::Color::Black);
    title.setPosition(width/2 - 136,100);

    playerCoin.setFont(font);
    playerCoin.setCharacterSize(sizeNotSelectedItem--);
    playerCoin.setFillColor(sf::Color::Black);
    playerCoin.setPosition(width/2 -64,height/2 +192);

    ImagePowerUp[0].setTexture(nextTxt);
    ImagePowerUp[0].setPosition((width/MAX_NUMBER_POWER_UP+1)*1-128 ,height/2 -128);
    ImagePowerUp[1].setTexture(speed);
    ImagePowerUp[1].setPosition((width/MAX_NUMBER_POWER_UP+1)*2-128 ,height/2 -128);
    ImagePowerUp[2].setTexture(swordDamage);
    ImagePowerUp[2].setPosition((width/MAX_NUMBER_POWER_UP+1)*3-128 ,height/2 -128);
    ImagePowerUp[3].setTexture(fireBallDamage);
    ImagePowerUp[3].setPosition((width/MAX_NUMBER_POWER_UP+1)*4-128 ,height/2 -128);
    ImagePowerUp[4].setTexture(arrowDamage);
    ImagePowerUp[4].setPosition((width/MAX_NUMBER_POWER_UP+1)*5-128 ,height/2 -128);

    Coin[0].setTexture(coinTexture);
    Coin[0].setPosition((width/MAX_NUMBER_POWER_UP+1)*2-64 ,height/2 +96);
    Coin[1].setTexture(coinTexture);
    Coin[1].setPosition((width/MAX_NUMBER_POWER_UP+1)*3-64 ,height/2 +96);
    Coin[2].setTexture(coinTexture);
    Coin[2].setPosition((width/MAX_NUMBER_POWER_UP+1)*4-64 ,height/2 +96);
    Coin[3].setTexture(coinTexture);
    Coin[3].setPosition((width/MAX_NUMBER_POWER_UP+1)*5-64 ,height/2 +96);

    CoinText[0].setString("x: "+std::to_string(priceSpeed));
    CoinText[0].setCharacterSize(sizeNotSelectedItem--);
    CoinText[0].setFont(font);
    CoinText[0].setFillColor(sf::Color::Black);
    CoinText[0].setPosition((width/MAX_NUMBER_POWER_UP+1)*2-128 ,height/2 +96);

    CoinText[1].setString("x: "+std::to_string(priceSword));
    CoinText[1].setCharacterSize(sizeNotSelectedItem--);
    CoinText[1].setFont(font);
    CoinText[1].setFillColor(sf::Color::Black);
    CoinText[1].setPosition((width/MAX_NUMBER_POWER_UP+1)*3-128 ,height/2 +96);

    CoinText[2].setString("x: "+std::to_string(priceFireBall));
    CoinText[2].setCharacterSize(sizeNotSelectedItem--);
    CoinText[2].setFont(font);
    CoinText[2].setFillColor(sf::Color::Black);
    CoinText[2].setPosition((width/MAX_NUMBER_POWER_UP+1)*4-128 ,height/2 +96);

    CoinText[3].setString("x: "+std::to_string(priceArrow));
    CoinText[3].setCharacterSize(sizeNotSelectedItem--);
    CoinText[3].setFont(font);
    CoinText[3].setFillColor(sf::Color::Black);
    CoinText[3].setPosition((width/MAX_NUMBER_POWER_UP+1)*5-128 ,height/2 +96);

    textLine[0].setFont(font);
    textLine[0].setFillColor(sf::Color::Blue);
    textLine[0].setString("Next");
    textLine[0].setPosition((width/MAX_NUMBER_POWER_UP+1)*1-128 -16,-(sizeSelectedItem-sizeNotSelectedItem)+height/2);
    textLine[0].setCharacterSize(sizeSelectedItem);

    textLine[1].setFont(font);
    textLine[1].setFillColor(sf::Color::Black);
    textLine[1].setString("+Speed");
    textLine[1].setPosition((width/MAX_NUMBER_POWER_UP+1)*2-128 -16,height/2);
    textLine[1].setCharacterSize(sizeNotSelectedItem);

    textLine[2].setFont(font);
    textLine[2].setFillColor(sf::Color::Black);
    textLine[2].setString("+Sword");
    textLine[2].setPosition((width/MAX_NUMBER_POWER_UP+1)*3 -128 -16 ,height/2);
    textLine[2].setCharacterSize(sizeNotSelectedItem);

    textLine[3].setFont(font);
    textLine[3].setFillColor(sf::Color::Black);
    textLine[3].setString("+FireBall");
    textLine[3].setPosition((width/MAX_NUMBER_POWER_UP+1)*4-128 -16 ,height/2);
    textLine[3].setCharacterSize(sizeNotSelectedItem);

    textLine[4].setFont(font);
    textLine[4].setFillColor(sf::Color::Black);
    textLine[4].setString("+Arrow");
    textLine[4].setPosition((width/MAX_NUMBER_POWER_UP+1)*5-128 -16 ,height/2);
    textLine[4].setCharacterSize(sizeNotSelectedItem);

}

void PowerUp::moveRight() {
    if(selectedItem -1 >=0){
        textLine[selectedItem].setFillColor(sf::Color::Black);
        textLine[selectedItem].setCharacterSize(sizeNotSelectedItem);
        textLine[selectedItem].setPosition(sf::Vector2f(textLine[selectedItem].getPosition().x +(sizeSelectedItem-sizeNotSelectedItem) ,(sizeSelectedItem-sizeNotSelectedItem)+textLine[selectedItem].getPosition().y));
        selectedItem--;
        textLine[selectedItem].setFillColor(sf::Color::Blue);
        textLine[selectedItem].setCharacterSize(sizeSelectedItem);
        textLine[selectedItem].setPosition(sf::Vector2f(textLine[selectedItem].getPosition().x -(sizeSelectedItem-sizeNotSelectedItem) ,-(sizeSelectedItem-sizeNotSelectedItem)+textLine[selectedItem].getPosition().y));
    }
}

void PowerUp::moveLeft() {
    if(selectedItem +1 <MAX_NUMBER_POWER_UP){
        textLine[selectedItem].setFillColor(sf::Color::Black);
        textLine[selectedItem].setCharacterSize(sizeNotSelectedItem);
        textLine[selectedItem].setPosition(sf::Vector2f(textLine[selectedItem].getPosition().x +(sizeSelectedItem-sizeNotSelectedItem) ,(sizeSelectedItem-sizeNotSelectedItem)+textLine[selectedItem].getPosition().y));
        selectedItem++;
        textLine[selectedItem].setFillColor(sf::Color::Blue);
        textLine[selectedItem].setCharacterSize(sizeSelectedItem);
        textLine[selectedItem].setPosition(sf::Vector2f(textLine[selectedItem].getPosition().x -(sizeSelectedItem-sizeNotSelectedItem),-(sizeSelectedItem-sizeNotSelectedItem)+textLine[selectedItem].getPosition().y));
    }
}

int PowerUp::getSelectedItem() {
    return selectedItem;
}

void PowerUp::draw(sf::RenderWindow &window, MainCharacter &player) {
    window.draw(background);
    for (int i = 0; i < MAX_NUMBER_POWER_UP; ++i) {
        window.draw(textLine[i]);
        window.draw(ImagePowerUp[i]);
    }
    if(player.inventory.NumberGold<priceSpeed)
        CoinText[0].setFillColor(sf::Color::Red);
    else
        CoinText[0].setFillColor(sf::Color::Green);

    if(player.inventory.NumberGold<priceSword)
        CoinText[1].setFillColor(sf::Color::Red);
    else
        CoinText[1].setFillColor(sf::Color::Green);

    if(player.inventory.NumberGold<priceFireBall)
        CoinText[2].setFillColor(sf::Color::Red);
    else
        CoinText[2].setFillColor(sf::Color::Green);

    if(player.inventory.NumberGold<priceArrow)
        CoinText[3].setFillColor(sf::Color::Red);
    else
        CoinText[3].setFillColor(sf::Color::Green);

    for (int j = 0; j < MAX_NUMBER_POWER_UP-1; ++j) {
        window.draw(Coin[j]);
        window.draw(CoinText[j]);
    }
    window.draw(title);
    playerCoin.setString("Your coins: "+std::to_string(player.inventory.NumberGold));
    window.draw(playerCoin);
}

bool PowerUp::IncrementSpeedPlayer(MainCharacter &player) {
    if(priceSpeed>player.inventory.NumberGold)
        return false;
    else{
        player.moveSpeed++;
        player.inventory.NumberGold-=priceSpeed;
        return true;
    }
}

bool PowerUp::IncrementDamageSwordPlayer(MainCharacter &player) {

    if(priceSword>player.inventory.NumberGold)
        return false;
    else{
        player.DMGSword++;
        player.inventory.NumberGold-=priceSword;
        return true;
    }

}

bool PowerUp::IncrementDamageFireBallPlayer(MainCharacter &player) {
    if(priceFireBall>player.inventory.NumberGold)
        return false;
    else{
        player.ball.damage++;
        player.inventory.NumberGold-=priceFireBall;
        return true;
    }
}

bool PowerUp::IncrementDamageArrowPlayer(MainCharacter &player) {
    if(priceArrow>player.inventory.NumberGold)
        return false;
    else{
        player.arrowPlayer.damage++;
        player.inventory.NumberGold-=priceArrow;
        return true;
    }
}



