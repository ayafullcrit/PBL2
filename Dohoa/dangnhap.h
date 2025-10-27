#pragma once
#include <SFML/Graphics.hpp>

class LoginScreen {
private:
    sf::Font& font;
    sf::RectangleShape box, inputUser, inputPass, loginButton;
    sf::Text title, userLabel, passLabel, loginText;

public:
    //LoginScreen();
    LoginScreen(sf::Font& f);
    bool handleEvent(const sf::Event& event, int& currentState);
    void draw(sf::RenderWindow& window);
};
