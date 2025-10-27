#pragma once
#include <SFML/Graphics.hpp>

enum AppState { MAIN_MENU, LOGIN_TUTOR, LOGIN_STUDENT };

class MainMenu {
private:
    sf::Font& font;
    sf::Text title1, title2, desc, tutorTitle, studentTitle;
    sf::RectangleShape tutorBox, studentBox;
    sf::CircleShape tutorIcon;
    sf::RectangleShape studentIcon;

public:
    MainMenu(sf::Font& f);
    AppState handleEvent(sf::RenderWindow& window, const sf::Event& event);
    void draw(sf::RenderWindow& window);
};
