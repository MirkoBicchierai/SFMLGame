#include "Game.h"
#include "ConcreteStateMenu.h"
int main(){
    Game game;
    game.pushState(new ConcreteStateMenu(&game));
    game.gameLoop();
    return 0;
}

/*
//Creazione Finestra di gioco
sf::RenderWindow window;
window.create(sf::VideoMode(1088, 704), "The road of Knight", sf::Style::Titlebar | sf::Style::Close);
sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - window.getSize().x / 2,(sf::VideoMode::getDesktopMode().height / 2) - window.getSize().y / 2);
window.setPosition(centerWindow);
sf::Image icon;
icon.loadFromFile("../img/GUI/Sword.png");
window.setIcon(32,32,icon.getPixelsPtr());
window.setFramerateLimit(60);
// clock abiltà
sf::Clock clockShield;
sf::Clock clockSword;
sf::Clock clockBow;
sf::Clock clockMagick;

//creazione player
MainCharacter mainCharacter(window);
Arrow arrow;

//Create map
const int level1[] = {
        27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37,
        43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45,
};

TileMap map;
map.load("../map/tileset_map.png", sf::Vector2u(32, 32), level1, 34, 22);

//Menu
Menu menu(window.getSize().x, window.getSize().y);

// Main Loop
sf::Event event{};
    while (window.isOpen()) {

    if (menu.play || menu.tutorial) {

        //Event Loop
        while (window.pollEvent(event) ) {

            if (event.type == sf::Event::Closed)
                window.close();
            //muovimento del player
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                mainCharacter.movePlayer('u',window);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                mainCharacter.movePlayer('d',window);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                mainCharacter.movePlayer('l',window);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                mainCharacter.movePlayer('r',window);
            }
            //attacco con spada del player
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mainCharacter.shield) {
                mainCharacter.sword = 1;
                clockSword.restart();
            } else {
                //attacco con arco del player
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mainCharacter.arrow > 0 &&
                    !mainCharacter.shield &&
                    !mainCharacter.aniArrow) {
                    mainCharacter.setTextureBow();
                    mainCharacter.bow = 1;
                    mainCharacter.aniArrow = true;
                    mainCharacter.arrowPlayer.clock.restart();
                    clockBow.restart();
                } else {
                    // attacco SPECIALE del player
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !mainCharacter.shield &&
                        !mainCharacter.spell) {
                        mainCharacter.magic = 1;
                        clockMagick.restart();
                        mainCharacter.spell = true;
                    } else {
                        // attivazione scudo player
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mainCharacter.spell) {
                            mainCharacter.setTextureShield();
                            clockShield.restart();
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                menu.tutorial = false;
                menu.play = false;
            }

        }
        //fine tempo scudo
        if (mainCharacter.shield && clockShield.getElapsedTime().asSeconds() >= mainCharacter.secShield) {
            mainCharacter.setNormalTexture();
            mainCharacter.shield = false;
        }
        //animazione spada
        if (mainCharacter.sword == 1) {
            if (clockSword.getElapsedTime().asMilliseconds()>=mainCharacter.timeSword ) {
                if (mainCharacter.swordAttack() == 64 * 5) {
                    mainCharacter.sword = 0;
                    mainCharacter.reset(mainCharacter.getsourceRect().top);
                }
                clockSword.restart();
            }
        }
        //animazione bow
        if (mainCharacter.bow == 1) {
            if (clockBow.getElapsedTime().asMilliseconds() >= mainCharacter.timeBow ) {
                if (mainCharacter.bowAttack() == 64 * 12) {
                    mainCharacter.bow = 0;
                    mainCharacter.reset(mainCharacter.getsourceRect().top);
                    mainCharacter.arrow = mainCharacter.arrow - 1;
                    mainCharacter.arrowPlayer.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y );
                    mainCharacter.arrowPlayer.animationArrow = true;
                    mainCharacter.arrowPlayer.ciclo = 0;
                    mainCharacter.arrowPlayer.stay = true;
                }
                clockBow.restart();
            }
        }
        //animazione spell-cast
        if (mainCharacter.magic == 1) {
            if ( clockMagick.getElapsedTime().asMilliseconds() >= mainCharacter.timeMagic ) {
                if (mainCharacter.magicAttack() == 64 * 6) {
                    mainCharacter.magic = 0;
                    mainCharacter.reset(mainCharacter.getsourceRect().top);
                    mainCharacter.ball.animationBall=true;
                    mainCharacter.ball.setRect(mainCharacter.getsourceRect(), mainCharacter.getSprite().getPosition().x,mainCharacter.getSprite().getPosition().y);
                }
                clockMagick.restart();
            }
        }
        //animazione fireball
        if (mainCharacter.ball.animationBall && mainCharacter.ball.clock.getElapsedTime().asMilliseconds() >= 40.f) {
            if (mainCharacter.ball.animation() == 64 * 7) {
                mainCharacter.ball.animationBall = false;
                mainCharacter.spell = false;
            }
            mainCharacter.ball.clock.restart();
        }
        //animazione arrow
        if (mainCharacter.arrowPlayer.animationArrow) {
            if (mainCharacter.arrowPlayer.ciclo < 8) {
                if (mainCharacter.arrowPlayer.clock.getElapsedTime().asMilliseconds() > 45.f) {
                    mainCharacter.arrowPlayer.animation();
                    mainCharacter.arrowPlayer.clock.restart();
                    mainCharacter.arrowPlayer.ciclo++;
                }
            } else {
                mainCharacter.arrowPlayer.pick = true;
                mainCharacter.arrowPlayer.animationArrow = false;
                mainCharacter.aniArrow = false;
            }

        }
        //ripresa della freccia a terra
        if (mainCharacter.getSprite().getGlobalBounds().intersects(mainCharacter.arrowPlayer.arrowSprite.getGlobalBounds()) &&
                mainCharacter.arrowPlayer.pick) {
            mainCharacter.arrowPlayer.pick = false;
            mainCharacter.arrowPlayer.stay = false;
            mainCharacter.arrow = 1;
        }

        //draw oggetti nella finestra di gioco

        window.clear();
        window.draw(map);
        mainCharacter.drawPlayer(window,clockShield);
        window.display();

    } else {

        mainCharacter.camera.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
        window.setView(mainCharacter.camera);

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                menu.moveUp();
            else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    menu.moveDown();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (menu.getSelectedItem() == 2)
                    window.close();
                else {
                    if (menu.getSelectedItem() == 1)
                        menu.tutorial = true;
                    else {
                        if (menu.getSelectedItem() == 0)
                            menu.play = true;
                    }
                    mainCharacter.camera.setCenter((mainCharacter.getSprite().getPosition().x) + 32,((mainCharacter.getSprite().getPosition().y)) + 32);
                }
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
}
return 0;
*/