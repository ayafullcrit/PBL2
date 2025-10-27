#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
#include <codecvt>

enum AppState { MAIN_MENU, LOGIN_TUTOR, LOGIN_STUDENT };

// Hàm tiện ích để chuyển chuỗi UTF-8 sang sf::String (hỗ trợ tiếng Việt)
sf::String toSfString(const std::wstring& wstr) {
    return sf::String(wstr);
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1150, 650), L"TutorConnectLL",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("NotoSans_Condensed-Black.ttf")) {
        std::cout << L"Không tìm thấy font NotoSans_Condensed-Black.ttf\n";
        return -1;
    }

    AppState currentState = MAIN_MENU;

    // --- Màu chủ đạo ---
    sf::Color bgColor(10, 17, 40);
    sf::Color boxColor(22, 36, 71);
    sf::Color borderColor(40, 55, 95);
    sf::Color accentColor(255, 195, 0);
    sf::Color textLight(230, 230, 230);
    sf::Color textGray(180, 180, 180);

    // --- Tiêu đề ---
    sf::Text title1(toSfString(L"Chào mừng đến với "), font, 48);
    title1.setFillColor(textLight);
    title1.setStyle(sf::Text::Bold);
    title1.setPosition(220, 60);

    sf::Text title2(L"TutorConnect", font, 48);
    title2.setFillColor(accentColor);
    title2.setStyle(sf::Text::Bold);
    title2.setPosition(title1.getPosition().x + title1.getGlobalBounds().width + 5, 60);

    sf::Text desc(toSfString(L"Vui lòng chọn vai trò của bạn để bắt đầu hành trình dạy và học."), font, 22);
    desc.setFillColor(textGray);
    desc.setPosition(250, 130);

    // --- Hai hộp chọn ---
    sf::RectangleShape tutorBox(sf::Vector2f(400, 200));
    tutorBox.setPosition(180, 280);
    tutorBox.setFillColor(boxColor);
    tutorBox.setOutlineThickness(2);
    tutorBox.setOutlineColor(borderColor);

    sf::RectangleShape studentBox(sf::Vector2f(400, 200));
    studentBox.setPosition(630, 280);
    studentBox.setFillColor(boxColor);
    studentBox.setOutlineThickness(2);
    studentBox.setOutlineColor(borderColor);

    // --- Biểu tượng ---
    sf::CircleShape tutorIcon(25);
    tutorIcon.setFillColor(accentColor);
    tutorIcon.setPosition(180 + 400 / 2.f - 25, 300);

    sf::RectangleShape studentIcon(sf::Vector2f(50, 30));
    studentIcon.setFillColor(accentColor);
    studentIcon.setPosition(630 + 400 / 2.f - 25, 305);

    // --- Văn bản hộp 1 ---
    sf::Text tutorTitle(toSfString(L"Tôi là Gia sư"), font, 26);
    tutorTitle.setFillColor(textLight);
    tutorTitle.setStyle(sf::Text::Bold);
    tutorTitle.setPosition(180 + 400 / 2.f - tutorTitle.getGlobalBounds().width / 2.f, 360);

    sf::Text tutorDesc(toSfString(L"Quản lý lớp học\nDuyệt học viên\nTheo dõi tiến độ học tập"), font, 18);
    tutorDesc.setFillColor(textGray);
    tutorDesc.setPosition(180 + 400 / 2.f - tutorDesc.getGlobalBounds().width / 2.f, 400);

    // --- Văn bản hộp 2 ---
    sf::Text studentTitle(toSfString(L"Tôi là Học viên"), font, 26);
    studentTitle.setFillColor(textLight);
    studentTitle.setStyle(sf::Text::Bold);
    studentTitle.setPosition(630 + 400 / 2.f - studentTitle.getGlobalBounds().width / 2.f, 360);

    sf::Text studentDesc(toSfString(L"Tìm kiếm gia sư phù hợp\nĐăng ký môn học theo mong muốn"), font, 18);
    studentDesc.setFillColor(textGray);
    studentDesc.setPosition(630 + 400 / 2.f - studentDesc.getGlobalBounds().width / 2.f, 400);

    // --- FORM ĐĂNG NHẬP ---
    sf::RectangleShape loginBox(sf::Vector2f(500, 300));
    loginBox.setFillColor(boxColor);
    loginBox.setOutlineColor(accentColor);
    loginBox.setOutlineThickness(2);
    loginBox.setPosition(325, 175);

    sf::Text loginTitle(toSfString(L"Đăng nhập tài khoản"), font, 32);
    loginTitle.setFillColor(accentColor);
    loginTitle.setStyle(sf::Text::Bold);
    loginTitle.setPosition(400, 200);

    sf::Text usernameLabel(toSfString(L"Tên đăng nhập:"), font, 20);
    usernameLabel.setFillColor(textLight);
    usernameLabel.setPosition(370, 270);

    sf::Text passwordLabel(toSfString(L"Mật khẩu:"), font, 20);
    passwordLabel.setFillColor(textLight);
    passwordLabel.setPosition(370, 320);

    sf::RectangleShape inputUser(sf::Vector2f(300, 30));
    inputUser.setPosition(500, 270);
    inputUser.setFillColor(sf::Color(25, 35, 70));

    sf::RectangleShape inputPass(sf::Vector2f(300, 30));
    inputPass.setPosition(500, 320);
    inputPass.setFillColor(sf::Color(25, 35, 70));

    sf::RectangleShape loginButton(sf::Vector2f(120, 40));
    loginButton.setPosition(540, 380);
    loginButton.setFillColor(accentColor);

    sf::Text loginText(toSfString(L"Đăng nhập"), font, 20);
    loginText.setFillColor(sf::Color::Black);
    loginText.setPosition(555, 387);

    // --- Main Loop ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MAIN_MENU && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (tutorBox.getGlobalBounds().contains(mousePos)) {
                    currentState = LOGIN_TUTOR;
                } else if (studentBox.getGlobalBounds().contains(mousePos)) {
                    currentState = LOGIN_STUDENT;
                }
            }

            if ((currentState == LOGIN_TUTOR || currentState == LOGIN_STUDENT) &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                currentState = MAIN_MENU;
            }
        }

        window.clear(bgColor);

        if (currentState == MAIN_MENU) {
            window.draw(title1);
            window.draw(title2);
            window.draw(desc);
            window.draw(tutorBox);
            window.draw(studentBox);
            window.draw(tutorIcon);
            window.draw(studentIcon);
            window.draw(tutorTitle);
            window.draw(tutorDesc);
            window.draw(studentTitle);
            window.draw(studentDesc);
        } else {
            window.draw(loginBox);
            window.draw(loginTitle);
            window.draw(usernameLabel);
            window.draw(passwordLabel);
            window.draw(inputUser);
            window.draw(inputPass);
            window.draw(loginButton);
            window.draw(loginText);
        }

        window.display();
    }

    return 0;
}
