#include <SFML/Graphics.hpp>
#include <iostream>

// Sử dụng enum class để an toàn hơn về kiểu dữ liệu
enum class AppState { MAIN_MENU, LOGIN_TUTOR, LOGIN_STUDENT };

int main() {
    // SFML 3.x: sf::VideoMode bây giờ nhận một sf::Vector2u
    sf::RenderWindow window(sf::VideoMode({1150, 650}), L"TutorConnectLL",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    sf::Font font;
    // BẬT LẠI ĐOẠN CODE NÀY ĐỂ TẢI FONT
    if (!font.openFromFile("NotoSans_Condensed-Black.ttf")) {
        // Tôi đã sửa lỗi cú pháp nhỏ ở đây (từ :std: thành std::)
        std::cout << L"Lỗi: Không tìm thấy hoặc không thể đọc file font NotoSans_Condensed-Black.ttf\n";
        return -1; // Thoát nếu không tải được font
    }

    AppState currentState = AppState::MAIN_MENU;

    // --- Màu chủ đạo ---
    sf::Color bgColor(10, 17, 40);
    sf::Color boxColor(22, 36, 71);
    sf::Color borderColor(40, 55, 95);
    sf::Color accentColor(255, 195, 0);
    sf::Color textLight(230, 230, 230);
    sf::Color textGray(180, 180, 180);

    // --- Tiêu đề ---
    // Giờ đây các đối tượng Text sẽ được tạo với font đã nạp
    sf::Text title1(font, L"Chào mừng đến với ", 48);
    title1.setFillColor(textLight);
    title1.setStyle(sf::Text::Bold);
    title1.setPosition({220.f, 60.f});

    sf::Text title2(font, L"TutorConnect", 48);
    title2.setFillColor(accentColor);
    title2.setStyle(sf::Text::Bold);
    title2.setPosition({title1.getPosition().x + title1.getGlobalBounds().size.x + 5.f, 60.f});

    sf::Text desc(font, L"Vui lòng chọn vai trò của bạn để bắt đầu hành trình dạy và học.", 22);
    desc.setFillColor(textGray);
    desc.setPosition({250.f, 130.f});

    // --- Hai hộp chọn ---
    sf::RectangleShape tutorBox({400.f, 200.f});
    tutorBox.setPosition({180.f, 280.f});
    tutorBox.setFillColor(boxColor);
    tutorBox.setOutlineThickness(2);
    tutorBox.setOutlineColor(borderColor);

    sf::RectangleShape studentBox({400.f, 200.f});
    studentBox.setPosition({630.f, 280.f});
    studentBox.setFillColor(boxColor);
    studentBox.setOutlineThickness(2);
    studentBox.setOutlineColor(borderColor);

    // --- Biểu tượng ---
    sf::CircleShape tutorIcon(25.f);
    tutorIcon.setFillColor(accentColor);
    tutorIcon.setPosition({180.f + 400.f / 2.f - 25.f, 300.f});

    sf::RectangleShape studentIcon({50.f, 30.f});
    studentIcon.setFillColor(accentColor);
    studentIcon.setPosition({630.f + 400.f / 2.f - 25.f, 305.f});

    // --- Văn bản hộp 1 ---
    sf::Text tutorTitle(font, L"Tôi là Gia sư", 26);
    tutorTitle.setFillColor(textLight);
    tutorTitle.setStyle(sf::Text::Bold);
    tutorTitle.setPosition({180.f + 400.f / 2.f - tutorTitle.getGlobalBounds().size.x / 2.f, 360.f});

    sf::Text tutorDesc(font, L"Quản lý lớp học\nDuyệt học viên\nTheo dõi tiến độ học tập", 18);
    tutorDesc.setFillColor(textGray);
    tutorDesc.setPosition({180.f + 400.f / 2.f - tutorDesc.getGlobalBounds().size.x / 2.f, 400.f});

    // --- Văn bản hộp 2 ---
    sf::Text studentTitle(font, L"Tôi là Học viên", 26);
    studentTitle.setFillColor(textLight);
    studentTitle.setStyle(sf::Text::Bold);
    studentTitle.setPosition({630.f + 400.f / 2.f - studentTitle.getGlobalBounds().size.x / 2.f, 360.f});

    sf::Text studentDesc(font, L"Tìm kiếm gia sư phù hợp\nĐăng ký môn học theo mong muốn", 18);
    studentDesc.setFillColor(textGray);
    studentDesc.setPosition({630.f + 400.f / 2.f - studentDesc.getGlobalBounds().size.x / 2.f, 400.f});

    // --- FORM ĐĂNG NHẬP ---
    sf::RectangleShape loginBox({500.f, 300.f});
    loginBox.setFillColor(boxColor);
    loginBox.setOutlineColor(accentColor);
    loginBox.setOutlineThickness(2);
    loginBox.setPosition({325.f, 175.f});

    sf::Text loginTitle(font, L"Đăng nhập tài khoản", 32);
    loginTitle.setFillColor(accentColor);
    loginTitle.setStyle(sf::Text::Bold);
    loginTitle.setPosition({400.f, 200.f});

    sf::Text usernameLabel(font, L"Tên đăng nhập:", 20);
    usernameLabel.setFillColor(textLight);
    usernameLabel.setPosition({370.f, 270.f});

    sf::Text passwordLabel(font, L"Mật khẩu:", 20);
    passwordLabel.setFillColor(textLight);
    passwordLabel.setPosition({370.f, 320.f});

    sf::RectangleShape inputUser({300.f, 30.f});
    inputUser.setPosition({500.f, 270.f});
    inputUser.setFillColor(sf::Color(25, 35, 70));
    
    sf::RectangleShape inputPass({300.f, 30.f});
    inputPass.setPosition({500.f, 320.f});
    inputPass.setFillColor(sf::Color(25, 35, 70));

    sf::RectangleShape loginButton({120.f, 40.f});
    loginButton.setPosition({540.f, 380.f});
    loginButton.setFillColor(accentColor);

    sf::Text loginText(font, L"Đăng nhập", 20);
    loginText.setFillColor(sf::Color::Black);
    loginText.setPosition({555.f, 387.f});

    // --- Main Loop ---
    while (window.isOpen()) {
        // SFML 3.x: Vòng lặp sự kiện đã thay đổi hoàn toàn
        while (const auto event = window.pollEvent()) {
            // Kiểm tra sự kiện đóng cửa sổ
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Xử lý logic cho màn hình chính
            if (currentState == AppState::MAIN_MENU) {
                // Lấy sự kiện nhấn chuột
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);
                    if (tutorBox.getGlobalBounds().contains(mousePos)) {
                        currentState = AppState::LOGIN_TUTOR;
                    } else if (studentBox.getGlobalBounds().contains(mousePos)) {
                        currentState = AppState::LOGIN_STUDENT;
                    }
                }
            }

            // Xử lý logic cho màn hình đăng nhập (chung cho cả hai)
            if ((currentState == AppState::LOGIN_TUTOR || currentState == AppState::LOGIN_STUDENT)) {
                 // Lấy sự kiện nhấn phím
                if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                    // SFML 3.x: sf::Keyboard::Escape đổi thành sf::Keyboard::Key::Escape
                    if (keyEvent->code == sf::Keyboard::Key::Escape) {
                        currentState = AppState::MAIN_MENU;
                    }
                }
            }
        }

        window.clear(bgColor);

        if (currentState == AppState::MAIN_MENU) {
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
        } else { // Màn hình đăng nhập
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
