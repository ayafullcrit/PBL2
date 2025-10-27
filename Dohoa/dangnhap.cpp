#include "dangnhap.h"
LoginScreen::LoginScreen(sf::Font& f) 
: font(f)
{
    box.setSize({500, 300});
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color(180, 180, 180));
    box.setOutlineThickness(2);
    box.setPosition(325, 175);

    title.setFont(font);
    title.setString("Dang nhap tai khoan");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color(60, 60, 60));
    title.setStyle(sf::Text::Bold);
    title.setPosition(400, 200);

    userLabel.setFont(font);
    userLabel.setString("Ten dang nhap:");
    userLabel.setCharacterSize(20);
    userLabel.setPosition(370, 270);

    passLabel.setFont(font);
    passLabel.setString("Mat khau:");
    passLabel.setCharacterSize(20);
    passLabel.setPosition(370, 320);

    inputUser.setSize({300, 30});
    inputUser.setPosition(500, 270);
    inputUser.setFillColor(sf::Color(240, 240, 240));

    inputPass.setSize({300, 30});
    inputPass.setPosition(500, 320);
    inputPass.setFillColor(sf::Color(240, 240, 240));

    loginButton.setSize({120, 40});
    loginButton.setPosition(540, 380);
    loginButton.setFillColor(sf::Color(100, 80, 255));

    loginText.setFont(font);
    loginText.setString("Dang nhap");
    loginText.setCharacterSize(20);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(555, 387);
}

bool LoginScreen::handleEvent(const sf::Event& event, int& currentState) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentState = 0; // quay lại MAIN_MENU
        return true;
    }
    return false;
}

void LoginScreen::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(title);
    window.draw(userLabel);
    window.draw(passLabel);
    window.draw(inputUser);
    window.draw(inputPass);
    window.draw(loginButton);
    window.draw(loginText);
}
