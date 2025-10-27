#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.hpp"
#include "LoginScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1150, 650), "TutorConnect",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Không tìm thấy font arial.ttf\n";
        return -1;
    }

    AppState currentState = MAIN_MENU;
    MainMenu mainMenu(font);
    LoginScreen login(font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MAIN_MENU) {
                currentState = mainMenu.handleEvent(window, event);
            } else {
                login.handleEvent(event, (int&)currentState);
            }
        }

        window.clear(sf::Color(245, 247, 250));
        if (currentState == MAIN_MENU)
            mainMenu.draw(window);
        else
            login.draw(window);
        window.display();
    }

    return 0;
}
