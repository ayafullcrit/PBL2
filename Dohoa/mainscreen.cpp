#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(sf::Font& f) : font(f) {
    title1.setFont(font);
    title1.setString("Chao mung den voi ");
    title1.setCharacterSize(48);
    title1.setFillColor(sf::Color(40, 40, 40));
    title1.setPosition(220, 60);

    title2.setFont(font);
    title2.setString("TutorConnect");
    title2.setCharacterSize(48);
    title2.setFillColor(sf::Color(100, 80, 255));
    title2.setPosition(title1.getPosition().x + title1.getGlobalBounds().width + 5, 60);

    desc.setFont(font);
    desc.setString("Vui long chon vai tro cua ban de bat dau hanh trinh day va hoc.");
    desc.setCharacterSize(22);
    desc.setFillColor(sf::Color(100, 100, 100));
    desc.setPosition(220, 130);

    tutorBox.setSize({400, 200});
    tutorBox.setPosition(180, 280);
    tutorBox.setFillColor(sf::Color::White);
    tutorBox.setOutlineThickness(2);
    tutorBox.setOutlineColor(sf::Color(220, 220, 220));

    studentBox.setSize({400, 200});
    studentBox.setPosition(630, 280);
    studentBox.setFillColor(sf::Color::White);
    studentBox.setOutlineThickness(2);
    studentBox.setOutlineColor(sf::Color(220, 220, 220));

    tutorIcon.setRadius(25);
    tutorIcon.setFillColor(sf::Color(120, 100, 255));
    tutorIcon.setPosition(180 + 400 / 2.f - 25, 300);

    studentIcon.setSize({50, 50});
    studentIcon.setFillColor(sf::Color(120, 100, 255));
    studentIcon.setPosition(630 + 400 / 2.f - 25, 300);

    tutorTitle.setFont(font);
    tutorTitle.setString("Toi la Gia su");
    tutorTitle.setCharacterSize(26);
    tutorTitle.setFillColor(sf::Color::Black);
    tutorTitle.setStyle(sf::Text::Bold);
    tutorTitle.setPosition(180 + 400 / 2.f - tutorTitle.getGlobalBounds().width / 2.f, 360);

    studentTitle.setFont(font);
    studentTitle.setString("Toi la Hoc vien");
    studentTitle.setCharacterSize(26);
    studentTitle.setFillColor(sf::Color::Black);
    studentTitle.setStyle(sf::Text::Bold);
    studentTitle.setPosition(630 + 400 / 2.f - studentTitle.getGlobalBounds().width / 2.f, 360);
}

AppState MainMenu::handleEvent(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (tutorBox.getGlobalBounds().contains(mousePos))
            return LOGIN_TUTOR;
        else if (studentBox.getGlobalBounds().contains(mousePos))
            return LOGIN_STUDENT;
    }
    return MAIN_MENU;
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(title1);
    window.draw(title2);
    window.draw(desc);
    window.draw(tutorBox);
    window.draw(studentBox);
    window.draw(tutorIcon);
    window.draw(studentIcon);
    window.draw(tutorTitle);
    window.draw(studentTitle);
}
