// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <iostream>
// #include <string>
// #include <chrono>
// #include "Admin.h"
// #include "Tutor.h"
// #include "Student.h"
// // Sử dụng enum class để an toàn hơn về kiểu dữ liệu
// enum class AppState
// {
//     MAIN_MENU,
//     LOGIN_TUTOR,
//     LOGIN_STUDENT,
//     REGISTER,
//     TUTOR_DASHBOARD,
//     STUDENT_DASHBOARD
// };

// // Biến toàn cục để lưu thông tin
// std::string currentUsername = "";
// std::string currentPassword = "";
// std::string currentFullname = "";
// std::string currentLocation = "";
// int currentGradeLevel = 1;
// std::string currentRole = "";

// // Biến cho con trỏ nhấp nháy
// bool cursorVisible = true;
// sf::Clock cursorClock;

// // Trạng thái nhập liệu
// enum class InputField
// {
//     NONE,
//     USERNAME,
//     PASSWORD,
//     FULLNAME,
//     LOCATION,
//     GRADE
// };
// InputField currentInputField = InputField::NONE;

// // Biến để lưu đối tượng đăng nhập
// User *currentUser = nullptr;
// Tutor *currentTutor = nullptr;
// Student *currentStudent = nullptr;

// // Hàm xử lý đăng nhập
// bool handleLogin(Admin &admin, const std::string &username, const std::string &password, AppState loginType)
// {
//     if (loginType == AppState::LOGIN_TUTOR)
//     {
//         currentTutor = admin.LoginTutor(username, password);
//         if (currentTutor != nullptr)
//         {
//             currentUser = static_cast<User *>(currentTutor);
//             return true;
//         }
//     }
//     else if (loginType == AppState::LOGIN_STUDENT)
//     {
//         currentStudent = admin.LoginStudent(username, password);
//         if (currentStudent != nullptr)
//         {
//             currentUser = static_cast<User *>(currentStudent);
//             return true;
//         }
//     }
//     return false;
// }

// // Hàm đăng xuất
// void handleLogout()
// {
//     currentUser = nullptr;
//     currentTutor = nullptr;
//     currentStudent = nullptr;
//     currentUsername = "";
//     currentPassword = "";
//     currentFullname = "";
//     currentLocation = "";
//     currentGradeLevel = 1;
//     currentRole = "";
//     currentInputField = InputField::NONE;
// }

// // Hàm xử lý đăng ký
// bool handleRegister(Admin &admin)
// {
//     admin.RegisterNewUser();
//     return true;
// }

// // Hàm cập nhật con trỏ nhấp nháy
// void updateCursor()
// {
//     if (cursorClock.getElapsedTime().asMilliseconds() > 500)
//     {
//         cursorVisible = !cursorVisible;
//         cursorClock.restart();
//     }
// }

// // Hàm xử lý sự kiện nhập văn bản
// void handleTextInput(char32_t unicode)
// {
//     if (currentInputField == InputField::USERNAME)
//     {
//         if (unicode == 8)
//         { // Backspace
//             if (!currentUsername.empty())
//             {
//                 currentUsername.pop_back();
//             }
//         }
//         else if (unicode >= 32 && unicode < 127)
//         {
//             currentUsername += static_cast<char>(unicode);
//         }
//     }
//     else if (currentInputField == InputField::PASSWORD)
//     {
//         if (unicode == 8)
//         { // Backspace
//             if (!currentPassword.empty())
//             {
//                 currentPassword.pop_back();
//             }
//         }
//         else if (unicode >= 32 && unicode < 127)
//         {
//             currentPassword += static_cast<char>(unicode);
//         }
//     }
//     else if (currentInputField == InputField::FULLNAME)
//     {
//         if (unicode == 8)
//         { // Backspace
//             if (!currentFullname.empty())
//             {
//                 currentFullname.pop_back();
//             }
//         }
//         else if (unicode >= 32 && unicode < 127)
//         {
//             currentFullname += static_cast<char>(unicode);
//         }
//     }
//     else if (currentInputField == InputField::LOCATION)
//     {
//         if (unicode == 8)
//         { // Backspace
//             if (!currentLocation.empty())
//             {
//                 currentLocation.pop_back();
//             }
//         }
//         else if (unicode >= 32 && unicode < 127)
//         {
//             currentLocation += static_cast<char>(unicode);
//         }
//     }
// }

// // Hàm reset outline cho tất cả input fields
// void resetOutline(sf::RectangleShape &inputUser, sf::RectangleShape &inputPass,
//                   sf::RectangleShape &inputFullname, sf::RectangleShape &inputRegUsername,
//                   sf::RectangleShape &inputRegPassword, sf::RectangleShape &inputLocation)
// {
//     inputUser.setOutlineThickness(0);
//     inputPass.setOutlineThickness(0);
//     inputFullname.setOutlineThickness(0);
//     inputRegUsername.setOutlineThickness(0);
//     inputRegPassword.setOutlineThickness(0);
//     inputLocation.setOutlineThickness(0);
// }

// int main()
// {
//     // Khởi tạo Admin và load data
//     Admin admin;

//     // SFML 3.0.2.1 Window
//     sf::RenderWindow window(sf::VideoMode({1150, 650}), "TutorConnectLL",
//                             sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
//     window.setFramerateLimit(60);

//     sf::Font font;
//     if (!font.openFromFile("arial.ttf"))
//     {
//         std::cout << "Lỗi: Không tìm thấy hoặc không thể đọc file font\n";
//         return -1;
//     }

//     AppState currentState = AppState::MAIN_MENU;

//     // --- Màu chủ đạo ---
//     sf::Color bgColor(10, 17, 40);
//     sf::Color boxColor(22, 36, 71);
//     sf::Color borderColor(40, 55, 95);
//     sf::Color accentColor(255, 195, 0);
//     sf::Color textLight(230, 230, 230);
//     sf::Color textGray(180, 180, 180);
//     sf::Color errorColor(255, 100, 100);

//     // --- MAIN MENU ---
//     sf::Text title1(font, "Chào mừng đến với ", 48);
//     title1.setFillColor(textLight);
//     title1.setStyle(sf::Text::Bold);
//     title1.setPosition({220.f, 60.f});

//     sf::Text title2(font, "TutorConnect", 48);
//     title2.setFillColor(accentColor);
//     title2.setStyle(sf::Text::Bold);
//     title2.setPosition({title1.getPosition().x + title1.getLocalBounds().size.x + 5.f, 60.f});

//     sf::Text desc(font, "Vui lòng chọn vai trò của bạn để bắt đầu hành trình dạy và học.", 22);
//     desc.setFillColor(textGray);
//     desc.setPosition({250.f, 130.f});

//     // --- Hai hộp chọn ---
//     sf::RectangleShape tutorBox({400.f, 200.f});
//     tutorBox.setPosition({180.f, 280.f});
//     tutorBox.setFillColor(boxColor);
//     tutorBox.setOutlineThickness(2);
//     tutorBox.setOutlineColor(borderColor);

//     sf::RectangleShape studentBox({400.f, 200.f});
//     studentBox.setPosition({630.f, 280.f});
//     studentBox.setFillColor(boxColor);
//     studentBox.setOutlineThickness(2);
//     studentBox.setOutlineColor(borderColor);

//     // --- Nút Đăng ký ---
//     sf::RectangleShape registerButton({200.f, 50.f});
//     registerButton.setPosition({475.f, 520.f});
//     registerButton.setFillColor(sf::Color(50, 100, 150));

//     sf::Text registerText(font, "Đăng ký tài khoản mới", 22);
//     registerText.setFillColor(textLight);
//     registerText.setPosition({485.f, 530.f});

//     // --- Biểu tượng ---
//     sf::CircleShape tutorIcon(25.f);
//     tutorIcon.setFillColor(accentColor);
//     tutorIcon.setPosition({180.f + 400.f / 2.f - 25.f, 300.f});

//     sf::RectangleShape studentIcon({50.f, 30.f});
//     studentIcon.setFillColor(accentColor);
//     studentIcon.setPosition({630.f + 400.f / 2.f - 25.f, 305.f});

//     // --- Văn bản hộp 1 ---
//     sf::Text tutorTitle(font, "Tôi là Gia sư", 26);
//     tutorTitle.setFillColor(textLight);
//     tutorTitle.setStyle(sf::Text::Bold);
//     tutorTitle.setPosition({180.f + 400.f / 2.f - tutorTitle.getLocalBounds().size.x / 2.f, 360.f});

//     sf::Text tutorDesc(font, "Quản lý lớp học\nDuyệt học viên\nTheo dõi tiến độ học tập", 18);
//     tutorDesc.setFillColor(textGray);
//     tutorDesc.setPosition({180.f + 400.f / 2.f - tutorDesc.getLocalBounds().size.x / 2.f, 400.f});

//     // // --- Văn bản hộp 2 ---
//     sf::Text studentTitle(font, "Tôi là Học viên", 26);
//     studentTitle.setFillColor(textLight);
//     studentTitle.setStyle(sf::Text::Bold);
//     studentTitle.setPosition({630.f + 400.f / 2.f - studentTitle.getLocalBounds().size.x / 2.f, 360.f});

//     sf::Text studentDesc(font, "Tìm kiếm gia sư phù hợp\nĐăng ký môn học theo mong muốn", 18);
//     studentDesc.setFillColor(textGray);
//     studentDesc.setPosition({630.f + 400.f / 2.f - studentDesc.getLocalBounds().size.x / 2.f, 400.f});

//     // --- FORM ĐĂNG NHẬP ---
//     sf::RectangleShape loginBox({500.f, 300.f});
//     loginBox.setFillColor(boxColor);
//     loginBox.setOutlineColor(accentColor);
//     loginBox.setOutlineThickness(2);
//     loginBox.setPosition({325.f, 175.f});

//     sf::Text loginTitle(font, "Đăng nhập tài khoản", 32);
//     loginTitle.setFillColor(accentColor);
//     loginTitle.setStyle(sf::Text::Bold);
//     loginTitle.setPosition({400.f, 200.f});

//     sf::Text usernameLabel(font, "Tên đăng nhập:", 20);
//     usernameLabel.setFillColor(textLight);
//     usernameLabel.setPosition({370.f, 270.f});

//     sf::Text passwordLabel(font, "Mật khẩu:", 20);
//     passwordLabel.setFillColor(textLight);
//     passwordLabel.setPosition({370.f, 320.f});

//     sf::RectangleShape inputUser({300.f, 30.f});
//     inputUser.setPosition({500.f, 270.f});
//     inputUser.setFillColor(sf::Color(25, 35, 70));

//     sf::RectangleShape inputPass({300.f, 30.f});
//     inputPass.setPosition({500.f, 320.f});
//     inputPass.setFillColor(sf::Color(25, 35, 70));

//     sf::RectangleShape loginButton({120.f, 40.f});
//     loginButton.setPosition({540.f, 380.f});
//     loginButton.setFillColor(accentColor);

//     sf::Text loginText(font, "Đăng nhập", 20);
//     loginText.setFillColor(sf::Color::Black);
//     loginText.setPosition({555.f, 387.f});

//     // --- Text hiển thị nhập liệu ---
//     sf::Text usernameText(font, currentUsername, 18);
//     usernameText.setFillColor(textLight);
//     usernameText.setPosition({505.f, 273.f});

//     sf::Text passwordText(font, std::string(currentPassword.size(), '*'), 18);
//     passwordText.setFillColor(textLight);
//     passwordText.setPosition({505.f, 323.f});

//     // --- Con trỏ nhấp nháy ---
//     sf::RectangleShape cursor({2.f, 20.f});
//     cursor.setFillColor(accentColor);

//     // --- Thông báo lỗi ---
//     sf::Text errorText(font, "", 16);
//     errorText.setFillColor(errorColor);
//     errorText.setPosition({400.f, 430.f});

//     // --- FORM ĐĂNG KÝ ---
//     sf::RectangleShape registerBox({600.f, 450.f});
//     registerBox.setFillColor(boxColor);
//     registerBox.setOutlineColor(accentColor);
//     registerBox.setOutlineThickness(2);
//     registerBox.setPosition({275.f, 100.f});

//     sf::Text registerTitle(font, "Đăng ký tài khoản mới", 32);
//     registerTitle.setFillColor(accentColor);
//     registerTitle.setStyle(sf::Text::Bold);
//     registerTitle.setPosition({350.f, 120.f});

//     // Các trường đăng ký
//     sf::Text fullnameLabel(font, "Họ và tên:", 20);
//     fullnameLabel.setFillColor(textLight);
//     fullnameLabel.setPosition({320.f, 180.f});

//     sf::Text regUsernameLabel(font, "Tên đăng nhập:", 20);
//     regUsernameLabel.setFillColor(textLight);
//     regUsernameLabel.setPosition({320.f, 230.f});

//     sf::Text regPasswordLabel(font, "Mật khẩu:", 20);
//     regPasswordLabel.setFillColor(textLight);
//     regPasswordLabel.setPosition({320.f, 280.f});

//     sf::Text locationLabel(font, "Địa chỉ:", 20);
//     locationLabel.setFillColor(textLight);
//     locationLabel.setPosition({320.f, 330.f});

//     sf::Text roleLabel(font, "Vai trò:", 20);
//     roleLabel.setFillColor(textLight);
//     roleLabel.setPosition({320.f, 380.f});

//     // Input fields cho đăng ký
//     sf::RectangleShape inputFullname({300.f, 30.f});
//     inputFullname.setPosition({500.f, 180.f});
//     inputFullname.setFillColor(sf::Color(25, 35, 70));

//     sf::RectangleShape inputRegUsername({300.f, 30.f});
//     inputRegUsername.setPosition({500.f, 230.f});
//     inputRegUsername.setFillColor(sf::Color(25, 35, 70));

//     sf::RectangleShape inputRegPassword({300.f, 30.f});
//     inputRegPassword.setPosition({500.f, 280.f});
//     inputRegPassword.setFillColor(sf::Color(25, 35, 70));

//     sf::RectangleShape inputLocation({300.f, 30.f});
//     inputLocation.setPosition({500.f, 330.f});
//     inputLocation.setFillColor(sf::Color(25, 35, 70));

//     // Nút chọn vai trò
//     sf::RectangleShape tutorRoleButton({120.f, 30.f});
//     tutorRoleButton.setPosition({500.f, 380.f});
//     tutorRoleButton.setFillColor(boxColor);
//     tutorRoleButton.setOutlineThickness(1);
//     tutorRoleButton.setOutlineColor(borderColor);

//     sf::RectangleShape studentRoleButton({120.f, 30.f});
//     studentRoleButton.setPosition({630.f, 380.f});
//     studentRoleButton.setFillColor(boxColor);
//     studentRoleButton.setOutlineThickness(1);
//     studentRoleButton.setOutlineColor(borderColor);

//     sf::Text tutorRoleText(font, "Gia sư", 18);
//     tutorRoleText.setFillColor(textLight);
//     tutorRoleText.setPosition({530.f, 383.f});

//     sf::Text studentRoleText(font, "Học sinh", 18);
//     studentRoleText.setFillColor(textLight);
//     studentRoleText.setPosition({650.f, 383.f});

//     // Nút đăng ký
//     sf::RectangleShape registerConfirmButton({120.f, 40.f});
//     registerConfirmButton.setPosition({540.f, 450.f});
//     registerConfirmButton.setFillColor(accentColor);

//     sf::Text registerConfirmText(font, "Đăng ký", 20);
//     registerConfirmText.setFillColor(sf::Color::Black);
//     registerConfirmText.setPosition({555.f, 457.f});

//     // Text hiển thị cho đăng ký
//     sf::Text fullnameText(font, currentFullname, 18);
//     fullnameText.setFillColor(textLight);
//     fullnameText.setPosition({505.f, 183.f});

//     sf::Text regUsernameText(font, currentUsername, 18);
//     regUsernameText.setFillColor(textLight);
//     regUsernameText.setPosition({505.f, 233.f});

//     sf::Text regPasswordText(font, std::string(currentPassword.size(), '*'), 18);
//     regPasswordText.setFillColor(textLight);
//     regPasswordText.setPosition({505.f, 283.f});

//     sf::Text locationText(font, currentLocation, 18);
//     locationText.setFillColor(textLight);
//     locationText.setPosition({505.f, 333.f});

//     // --- DASHBOARD GIA SƯ ---
//     sf::RectangleShape tutorDashboardBox({800.f, 500.f});
//     tutorDashboardBox.setFillColor(boxColor);
//     tutorDashboardBox.setOutlineColor(accentColor);
//     tutorDashboardBox.setOutlineThickness(2);
//     tutorDashboardBox.setPosition({175.f, 75.f});

//     sf::Text tutorWelcomeText(font, "Chào mừng Gia sư!", 36);
//     tutorWelcomeText.setFillColor(accentColor);
//     tutorWelcomeText.setStyle(sf::Text::Bold);
//     tutorWelcomeText.setPosition({350.f, 100.f});

//     sf::Text tutorInfoText(font, "Thông tin cá nhân sẽ hiển thị ở đây", 20);
//     tutorInfoText.setFillColor(textLight);
//     tutorInfoText.setPosition({250.f, 180.f});

//     sf::RectangleShape tutorLogoutButton({120.f, 40.f});
//     tutorLogoutButton.setPosition({500.f, 500.f});
//     tutorLogoutButton.setFillColor(errorColor);

//     sf::Text tutorLogoutText(font, "Đăng xuất", 20);
//     tutorLogoutText.setFillColor(sf::Color::White);
//     tutorLogoutText.setPosition({515.f, 507.f});

//     // --- DASHBOARD HỌC SINH ---
//     sf::RectangleShape studentDashboardBox({800.f, 500.f});
//     studentDashboardBox.setFillColor(boxColor);
//     studentDashboardBox.setOutlineColor(accentColor);
//     studentDashboardBox.setOutlineThickness(2);
//     studentDashboardBox.setPosition({175.f, 75.f});

//     sf::Text studentWelcomeText(font, "Chào mừng Học sinh!", 36);
//     studentWelcomeText.setFillColor(accentColor);
//     studentWelcomeText.setStyle(sf::Text::Bold);
//     studentWelcomeText.setPosition({330.f, 100.f});

//     sf::Text studentInfoText(font, "Thông tin cá nhân sẽ hiển thị ở đây", 20);
//     studentInfoText.setFillColor(textLight);
//     studentInfoText.setPosition({250.f, 180.f});

//     sf::RectangleShape studentLogoutButton({120.f, 40.f});
//     studentLogoutButton.setPosition({500.f, 500.f});
//     studentLogoutButton.setFillColor(errorColor);

//     sf::Text studentLogoutText(font, "Đăng xuất", 20);
//     studentLogoutText.setFillColor(sf::Color::White);
//     studentLogoutText.setPosition({515.f, 507.f});

//     // --- Main Loop ---
//     while (window.isOpen())
//     {
//         // SFML 3.0.2.1: Sử dụng pollEvent thay vì while (const auto event = window.pollEvent())
//         //sf::Event event;
//         // while (window.pollEvent())
//         while (std::optional<sf::Event> event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//             {
//                 window.close();
//             }

//             // Xử lý sự kiện nhập văn bản
//             if (event->is<sf::Event::TextEntered>())
//             {
//                 const auto* textEvent = event->getIf<sf::Event::TextEntered>();
//                 handleTextInput(textEvent->unicode);
//             }

//             // Xử lý sự kiện chuột
//             if (event->is<sf::Event::MouseButtonPressed>())
//             {
//                 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

//                 // Màn hình chính
//                 if (currentState == AppState::MAIN_MENU)
//                 {
//                     if (tutorBox.getGlobalBounds().contains(mousePos))
//                     {
//                         currentState = AppState::LOGIN_TUTOR;
//                         errorText.setString("");
//                         currentInputField = InputField::USERNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputUser.setOutlineColor(accentColor);
//                         inputUser.setOutlineThickness(2);
//                     }
//                     else if (studentBox.getGlobalBounds().contains(mousePos))
//                     {
//                         currentState = AppState::LOGIN_STUDENT;
//                         errorText.setString("");
//                         currentInputField = InputField::USERNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputUser.setOutlineColor(accentColor);
//                         inputUser.setOutlineThickness(2);
//                     }
//                     else if (registerButton.getGlobalBounds().contains(mousePos))
//                     {
//                         currentState = AppState::REGISTER;
//                         errorText.setString("");
//                         currentInputField = InputField::FULLNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputFullname.setOutlineColor(accentColor);
//                         inputFullname.setOutlineThickness(2);
//                         currentFullname = "";
//                         currentUsername = "";
//                         currentPassword = "";
//                         currentLocation = "";
//                         currentRole = "";
//                     }
//                 }
//                 // Màn hình đăng nhập
//                 else if (currentState == AppState::LOGIN_TUTOR || currentState == AppState::LOGIN_STUDENT)
//                 {
//                     // Chọn ô nhập username
//                     if (inputUser.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::USERNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputUser.setOutlineColor(accentColor);
//                         inputUser.setOutlineThickness(2);
//                     }
//                     // Chọn ô nhập password
//                     else if (inputPass.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::PASSWORD;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputPass.setOutlineColor(accentColor);
//                         inputPass.setOutlineThickness(2);
//                     }
//                     // Nút đăng nhập
//                     else if (loginButton.getGlobalBounds().contains(mousePos))
//                     {
//                         if (currentUsername.empty() || currentPassword.empty())
//                         {
//                             errorText.setString("Vui lòng nhập đầy đủ thông tin!");
//                         }
//                         else
//                         {
//                             bool loginSuccess = handleLogin(admin, currentUsername, currentPassword, currentState);
//                             if (loginSuccess)
//                             {
//                                 if (currentState == AppState::LOGIN_TUTOR)
//                                 {
//                                     currentState = AppState::TUTOR_DASHBOARD;
//                                     tutorWelcomeText.setString("Chào mừng " + currentTutor->GetName());
//                                     tutorInfoText.setString(
//                                         "ID: " + currentTutor->GetID() + "\n" +
//                                         "Địa chỉ: " + currentTutor->GetLocation() + "\n" +
//                                         "Số dư: " + std::to_string(currentTutor->GetBalance()) + " VND\n" +
//                                         "Đánh giá: " + std::to_string(currentTutor->GetRating()) + "/5");
//                                 }
//                                 else
//                                 {
//                                     currentState = AppState::STUDENT_DASHBOARD;
//                                     studentWelcomeText.setString("Chào mừng " + currentStudent->GetName());
//                                     studentInfoText.setString(
//                                         "ID: " + currentStudent->GetID() + "\n" +
//                                         "Địa chỉ: " + currentStudent->GetLocation() + "\n" +
//                                         "Số dư: " + std::to_string(currentStudent->GetBalance()) + " VND\n" +
//                                         "Lớp: " + std::to_string(currentStudent->GetGradeLevel()));
//                                 }
//                                 errorText.setString("");
//                             }
//                             else
//                             {
//                                 errorText.setString("Đăng nhập thất bại! Kiểm tra lại ID và mật khẩu.");
//                             }
//                         }
//                     }
//                 }
//                 // Màn hình đăng ký
//                 else if (currentState == AppState::REGISTER)
//                 {
//                     // Chọn các ô nhập liệu
//                     if (inputFullname.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::FULLNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputFullname.setOutlineColor(accentColor);
//                         inputFullname.setOutlineThickness(2);
//                     }
//                     else if (inputRegUsername.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::USERNAME;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputRegUsername.setOutlineColor(accentColor);
//                         inputRegUsername.setOutlineThickness(2);
//                     }
//                     else if (inputRegPassword.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::PASSWORD;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputRegPassword.setOutlineColor(accentColor);
//                         inputRegPassword.setOutlineThickness(2);
//                     }
//                     else if (inputLocation.getGlobalBounds().contains(mousePos))
//                     {
//                         currentInputField = InputField::LOCATION;
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                         inputLocation.setOutlineColor(accentColor);
//                         inputLocation.setOutlineThickness(2);
//                     }
//                     // Chọn vai trò
//                     else if (tutorRoleButton.getGlobalBounds().contains(mousePos))
//                     {
//                         currentRole = "Tutor";
//                         tutorRoleButton.setFillColor(accentColor);
//                         studentRoleButton.setFillColor(boxColor);
//                     }
//                     else if (studentRoleButton.getGlobalBounds().contains(mousePos))
//                     {
//                         currentRole = "Student";
//                         tutorRoleButton.setFillColor(boxColor);
//                         studentRoleButton.setFillColor(accentColor);
//                     }
//                     // Nút đăng ký
//                     else if (registerConfirmButton.getGlobalBounds().contains(mousePos))
//                     {
//                         if (currentFullname.empty() || currentUsername.empty() || currentPassword.empty() || currentLocation.empty() || currentRole.empty())
//                         {
//                             errorText.setString("Vui lòng điền đầy đủ thông tin!");
//                         }
//                         else
//                         {
//                             // Gọi hàm đăng ký
//                             handleRegister(admin);
//                             errorText.setString("Đăng ký thành công! Quay về trang chủ.");
//                             // Reset form
//                             currentFullname = "";
//                             currentUsername = "";
//                             currentPassword = "";
//                             currentLocation = "";
//                             currentRole = "";
//                             currentState = AppState::MAIN_MENU;
//                         }
//                     }
//                 }
//                 // Dashboard gia sư
//                 else if (currentState == AppState::TUTOR_DASHBOARD)
//                 {
//                     if (tutorLogoutButton.getGlobalBounds().contains(mousePos))
//                     {
//                         handleLogout();
//                         currentState = AppState::MAIN_MENU;
//                     }
//                 }
//                 // Dashboard học sinh
//                 else if (currentState == AppState::STUDENT_DASHBOARD)
//                 {
//                     if (studentLogoutButton.getGlobalBounds().contains(mousePos))
//                     {
//                         handleLogout();
//                         currentState = AppState::MAIN_MENU;
//                     }
//                 }
//             }

//             // Xử lý phím ESC để quay lại
//             if (event->is<sf::Event::KeyPressed>())
//             {
//                 const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
//                 if (keyEvent->code == sf::Keyboard::Key::Escape)
//                 {
//                     if (currentState == AppState::LOGIN_TUTOR || currentState == AppState::LOGIN_STUDENT || currentState == AppState::REGISTER)
//                     {
//                         currentState = AppState::MAIN_MENU;
//                         currentUsername = "";
//                         currentPassword = "";
//                         currentFullname = "";
//                         currentLocation = "";
//                         currentRole = "";
//                         errorText.setString("");
//                         resetOutline(inputUser, inputPass, inputFullname, inputRegUsername, inputRegPassword, inputLocation);
//                     }
//                 }

//                 // Xử lý phím Backspace
//                 if (keyEvent->code == sf::Keyboard::Key::Backspace)
//                 {
//                     handleTextInput(8); // 8 là mã unicode cho backspace
//                 }
//             }
//         }

//         // Cập nhật con trỏ nhấp nháy
//         updateCursor();

//         // Cập nhật text hiển thị
//         usernameText.setString(currentUsername);
//         passwordText.setString(std::string(currentPassword.size(), '*'));
//         fullnameText.setString(currentFullname);
//         regUsernameText.setString(currentUsername);
//         regPasswordText.setString(std::string(currentPassword.size(), '*'));
//         locationText.setString(currentLocation);

//         window.clear(bgColor);

//         // Vẽ theo trạng thái hiện tại
//         switch (currentState)
//         {
//         case AppState::MAIN_MENU:
//             window.draw(title1);
//             window.draw(title2);
//             window.draw(desc);
//             window.draw(tutorBox);
//             window.draw(studentBox);
//             window.draw(registerButton);
//             window.draw(registerText);
//             window.draw(tutorIcon);
//             window.draw(studentIcon);
//             window.draw(tutorTitle);
//             window.draw(tutorDesc);
//             window.draw(studentTitle);
//             window.draw(studentDesc);
//             break;

//         case AppState::LOGIN_TUTOR:
//         case AppState::LOGIN_STUDENT:
//             window.draw(loginBox);
//             window.draw(loginTitle);
//             window.draw(usernameLabel);
//             window.draw(passwordLabel);
//             window.draw(inputUser);
//             window.draw(inputPass);
//             window.draw(loginButton);
//             window.draw(loginText);
//             window.draw(usernameText);
//             window.draw(passwordText);
//             window.draw(errorText);

//             // Vẽ con trỏ nhấp nháy
//             if (cursorVisible && currentInputField != InputField::NONE)
//             {
//                 if (currentInputField == InputField::USERNAME)
//                 {
//                     cursor.setPosition({usernameText.getPosition().x + usernameText.getLocalBounds().size.x + 2, usernameText.getPosition().y});
//                     window.draw(cursor);
//                 }
//                 else if (currentInputField == InputField::PASSWORD)
//                 {
//                     cursor.setPosition({passwordText.getPosition().x + passwordText.getLocalBounds().size.x + 2, passwordText.getPosition().y});
//                     window.draw(cursor);
//                 }
//             }
//             break;

//         case AppState::REGISTER:
//             window.draw(registerBox);
//             window.draw(registerTitle);
//             window.draw(fullnameLabel);
//             window.draw(regUsernameLabel);
//             window.draw(regPasswordLabel);
//             window.draw(locationLabel);
//             window.draw(roleLabel);
//             window.draw(inputFullname);
//             window.draw(inputRegUsername);
//             window.draw(inputRegPassword);
//             window.draw(inputLocation);
//             window.draw(tutorRoleButton);
//             window.draw(studentRoleButton);
//             window.draw(tutorRoleText);
//             window.draw(studentRoleText);
//             window.draw(registerConfirmButton);
//             window.draw(registerConfirmText);
//             window.draw(fullnameText);
//             window.draw(regUsernameText);
//             window.draw(regPasswordText);
//             window.draw(locationText);
//             window.draw(errorText);

//             // Vẽ con trỏ nhấp nháy
//             if (cursorVisible && currentInputField != InputField::NONE)
//             {
//                 if (currentInputField == InputField::FULLNAME)
//                 {
//                     cursor.setPosition({fullnameText.getPosition().x + fullnameText.getLocalBounds().size.x + 2, fullnameText.getPosition().y});
//                     window.draw(cursor);
//                 }
//                 else if (currentInputField == InputField::USERNAME)
//                 {
//                     cursor.setPosition({regUsernameText.getPosition().x + regUsernameText.getLocalBounds().size.x + 2, regUsernameText.getPosition().y});
//                     window.draw(cursor);
//                 }
//                 else if (currentInputField == InputField::PASSWORD)
//                 {
//                     cursor.setPosition({regPasswordText.getPosition().x + regPasswordText.getLocalBounds().size.x + 2, regPasswordText.getPosition().y});
//                     window.draw(cursor);
//                 }
//                 else if (currentInputField == InputField::LOCATION)
//                 {
//                     cursor.setPosition({locationText.getPosition().x + locationText.getLocalBounds().size.x + 2, locationText.getPosition().y});
//                     window.draw(cursor);
//                 }
//             }
//             break;

//         case AppState::TUTOR_DASHBOARD:
//             window.draw(tutorDashboardBox);
//             window.draw(tutorWelcomeText);
//             window.draw(tutorInfoText);
//             window.draw(tutorLogoutButton);
//             window.draw(tutorLogoutText);
//             break;

//         case AppState::STUDENT_DASHBOARD:
//             window.draw(studentDashboardBox);
//             window.draw(studentWelcomeText);
//             window.draw(studentInfoText);
//             window.draw(studentLogoutButton);
//             window.draw(studentLogoutText);
//             break;
//         }

//         window.display();
//     }

//     // Dọn dẹp bộ nhớ
//     if (currentUser != nullptr)
//     {
//         delete currentUser;
//     }

//     return 0;
// }