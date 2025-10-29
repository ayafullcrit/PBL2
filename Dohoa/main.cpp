#include <SFML/Graphics.hpp>
#include <iostream>

// Sử dụng enum class để an toàn hơn về kiểu dữ liệu
enum class AppState { MAIN_MENU, LOGIN_TUTOR, LOGIN_STUDENT, LOGIN_ADMIN };

int main() {
    // SFML 3.x: sf::VideoMode bây giờ nhận một sf::Vector2u
    sf::RenderWindow window(sf::VideoMode({1150, 650}), L"TutorConnectLL",
                            sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("Arial.ttf")) {
        std::cout << L"Lỗi: Không tìm thấy hoặc không thể đọc file font Arial.ttf\n";
        return -1;
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
    sf::Text title1(font, L"Chào mừng đến với ", 48);
    title1.setFillColor(textLight);
    title1.setStyle(sf::Text::Bold);
    title1.setPosition({220.f, 60.f});

    sf::Text title2(font, L"TutorConnect", 48);
    title2.setFillColor(accentColor);
    title2.setStyle(sf::Text::Bold);
    title2.setPosition({title1.getPosition().x + title1.getLocalBounds().size.x + 5.f, 60.f});

    sf::Text desc(font, L"Vui lòng chọn vai trò của bạn để bắt đầu hành trình dạy và học.", 22);
    desc.setFillColor(textGray);
    desc.setPosition({250.f, 130.f});

    // --- Tính toán vị trí 3 hộp cân đối ---
    float boxWidth = 300.f;
    float boxHeight = 200.f;
    float totalWidth = 1150.f;
    float gap = (totalWidth - (boxWidth * 3)) / 4; // Khoảng cách đều giữa các hộp
    
    // --- Ba hộp chọn ---
    sf::RectangleShape tutorBox({boxWidth, boxHeight});
    tutorBox.setPosition({gap, 280.f});
    tutorBox.setFillColor(boxColor);
    tutorBox.setOutlineThickness(2);
    tutorBox.setOutlineColor(borderColor);

    sf::RectangleShape studentBox({boxWidth, boxHeight});
    studentBox.setPosition({gap * 2 + boxWidth, 280.f});
    studentBox.setFillColor(boxColor);
    studentBox.setOutlineThickness(2);
    studentBox.setOutlineColor(borderColor);

    sf::RectangleShape adminBox({boxWidth, boxHeight});
    adminBox.setPosition({gap * 3 + boxWidth * 2, 280.f});
    adminBox.setFillColor(boxColor);
    adminBox.setOutlineThickness(2);
    adminBox.setOutlineColor(borderColor);

    // --- Biểu tượng ---
    sf::CircleShape tutorIcon(25.f);
    tutorIcon.setFillColor(accentColor);
    tutorIcon.setPosition({gap + boxWidth / 2.f - 25.f, 300.f});

    sf::RectangleShape studentIcon({50.f, 30.f});
    studentIcon.setFillColor(accentColor);
    studentIcon.setPosition({gap * 2 + boxWidth + boxWidth / 2.f - 25.f, 305.f});

    // Thêm biểu tượng cho admin (hình lục giác)
    sf::CircleShape adminIcon(25.f, 6);
    adminIcon.setFillColor(accentColor);
    adminIcon.setPosition({gap * 3 + boxWidth * 2 + boxWidth / 2.f - 25.f, 300.f});

    // --- Văn bản hộp 1 (Gia sư) ---
    sf::Text tutorTitle(font, L"Tôi là Gia sư", 26);
    tutorTitle.setFillColor(textLight);
    tutorTitle.setStyle(sf::Text::Bold);
    float tutorTitleX = gap + boxWidth / 2.f - tutorTitle.getLocalBounds().size.x / 2.f;
    tutorTitle.setPosition({tutorTitleX, 360.f});

    sf::Text tutorDesc(font, L"Quản lý lớp học\nDuyệt học viên\nTheo dõi tiến độ học tập", 18);
    tutorDesc.setFillColor(textGray);
    float tutorDescX = gap + boxWidth / 2.f - tutorDesc.getLocalBounds().size.x / 2.f;
    tutorDesc.setPosition({tutorDescX, 400.f});

    // --- Văn bản hộp 2 (Học viên) ---
    sf::Text studentTitle(font, L"Tôi là Học viên", 26);
    studentTitle.setFillColor(textLight);
    studentTitle.setStyle(sf::Text::Bold);
    float studentTitleX = gap * 2 + boxWidth + boxWidth / 2.f - studentTitle.getLocalBounds().size.x / 2.f;
    studentTitle.setPosition({studentTitleX, 360.f});

    sf::Text studentDesc(font, L"Tìm kiếm gia sư phù hợp\nĐăng ký môn học theo mong muốn", 18);
    studentDesc.setFillColor(textGray);
    float studentDescX = gap * 2 + boxWidth + boxWidth / 2.f - studentDesc.getLocalBounds().size.x / 2.f;
    studentDesc.setPosition({studentDescX, 400.f});

    // --- Văn bản hộp 3 (Admin) ---
    sf::Text adminTitle(font, L"Tôi là Admin", 26);
    adminTitle.setFillColor(textLight);
    adminTitle.setStyle(sf::Text::Bold);
    float adminTitleX = gap * 3 + boxWidth * 2 + boxWidth / 2.f - adminTitle.getLocalBounds().size.x / 2.f;
    adminTitle.setPosition({adminTitleX, 360.f});

    sf::Text adminDesc(font, L"Quản lý hệ thống\nGiám sát người dùng\nPhân quyền truy cập", 18);
    adminDesc.setFillColor(textGray);
    float adminDescX = gap * 3 + boxWidth * 2 + boxWidth / 2.f - adminDesc.getLocalBounds().size.x / 2.f;
    adminDesc.setPosition({adminDescX, 400.f});

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
        // SFML 3.x: Vòng lặp sự kiện
        while (std::optional <sf::Event> event = window.pollEvent()) {
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
                    } else if (adminBox.getGlobalBounds().contains(mousePos)) {
                        currentState = AppState::LOGIN_ADMIN; // Thêm xử lý cho admin
                    }
                }
            }

            // Xử lý logic cho màn hình đăng nhập (chung cho cả ba)
            if ((currentState == AppState::LOGIN_TUTOR || 
                 currentState == AppState::LOGIN_STUDENT || 
                 currentState == AppState::LOGIN_ADMIN)) {
                if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
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
            window.draw(adminBox);
            window.draw(tutorIcon);
            window.draw(studentIcon);
            window.draw(adminIcon);
            window.draw(tutorTitle);
            window.draw(tutorDesc);
            window.draw(studentTitle);
            window.draw(studentDesc);
            window.draw(adminTitle);
            window.draw(adminDesc);

        } else { // Màn hình đăng nhập (chung cho cả ba)
            window.draw(loginBox);
            window.draw(loginTitle);
            window.draw(usernameLabel);
            window.draw(passwordLabel);
            window.draw(inputUser);
            window.draw(inputPass);
            window.draw(loginButton);
            window.draw(loginText);
            
            // Hiển thị thêm thông tin về loại đăng nhập
            sf::Text loginType(font, L"", 24);
            loginType.setFillColor(accentColor);
            loginType.setPosition({400.f, 150.f});
            
            if (currentState == AppState::LOGIN_TUTOR) {
                loginType.setString(L"Đăng nhập với tư cách Gia sư");
            } else if (currentState == AppState::LOGIN_STUDENT) {
                loginType.setString(L"Đăng nhập với tư cách Học viên");
            } else if (currentState == AppState::LOGIN_ADMIN) {
                loginType.setString(L"Đăng nhập với tư cách Admin");
            }
            window.draw(loginType);
        }

        window.display();
    }

    return 0;
}
