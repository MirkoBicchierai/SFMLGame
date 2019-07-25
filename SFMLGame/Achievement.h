#ifndef SFMLGAME_ACHIEVEMENT_H
#define SFMLGAME_ACHIEVEMENT_H

#include <SFML/Graphics.hpp>
#include "MainCharacter.h"
class Achievement {
public:
    Achievement(std::string text,std::string file);
    void drawAchievement(sf::RenderWindow &window);
    void changePosition(int i,sf::RenderWindow &window ,MainCharacter &player);
    sf::Clock AchievementClock;
private:

    sf::Font font;
    sf::Text textDraw;

    sf::Texture texture;
    sf::Sprite sprite;


};

#endif
