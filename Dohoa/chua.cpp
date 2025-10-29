#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
// #include <sstream> // không cần dùng nữa

class SinhVien {
public:
    std::string ten;
    int tuoi;
};

int main() {
    // Sử dụng C++11 uniform initialization cho VideoMode
    sf::RenderWindow window(sf::VideoMode({600, 400}), "Nhap thong tin sinh vien");
    window.setFramerateLimit(60); // Giới hạn FPS để giảm tải CPU

    sf::Font font;
    // Đảm bảo file font "arial.ttf" có trong thư mục dự án của bạn
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text labelTen("Ten:", font, 25);
    labelTen.setPosition(50, 80);

    sf::Text labelTuoi("Tuoi:", font, 25);
    labelTuoi.setPosition(50, 150);

    sf::Text textTen("", font, 25);
    textTen.setPosition(150, 80);

    sf::Text textTuoi("", font, 25);
    textTuoi.setPosition(150, 150);

    sf::Text thongbao("", font, 25);
    thongbao.setPosition(50, 300);

    // Sử dụng std::string cho tiện lợi
    std::string nhapTen = "", nhapTuoi = "";
    bool nhapDangTen = true; // true = đang nhập tên, false = đang nhập tuổi

    SinhVien sv;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            // Nhập chữ - THAY ĐỔI LỚN Ở ĐÂY
            if (e.type == sf::Event::TextEntered) {
                // Sử dụng e.text.utf32 thay cho e.text.unicode
                sf::Uint32 unicode = e.text.utf32;

                if (unicode == 8) { // backspace
                    if (nhapDangTen && !nhapTen.empty()) nhapTen.pop_back();
                    else if (!nhapDangTen && !nhapTuoi.empty()) nhapTuoi.pop_back();
                }
                else if (unicode == '\r' || unicode == '\n') { // Enter
                    if (nhapDangTen) {
                        nhapDangTen = false;
                    } else {
                        try {
                            sv.ten = nhapTen;
                            sv.tuoi = std::stoi(nhapTuoi);
                            thongbao.setString("Da luu sinh vien: " + sv.ten + " - " + std::to_string(sv.tuoi) + " tuoi");
                        } catch (const std::invalid_argument& ia) {
                            thongbao.setString("Loi: Tuoi phai la so!");
                        } catch (const std::out_of_range& oor) {
                            thongbao.setString("Loi: So tuoi qua lon!");
                        }
                    }
                }
                // Chỉ nhận các ký tự ASCII in được
                else if (unicode >= 32 && unicode < 128) {
                    if (nhapDangTen) {
                        nhapTen += static_cast<char>(unicode);
                    } else if (std::isdigit(static_cast<char>(unicode))) { // Chỉ cho phép nhập số vào tuổi
                        nhapTuoi += static_cast<char>(unicode);
                    }
                }
            }
        }

        textTen.setString(nhapTen);
        textTuoi.setString(nhapTuoi);

        window.clear(sf::Color(30, 30, 50));
        window.draw(labelTen);
        window.draw(textTen);
        window.draw(labelTuoi);
        window.draw(textTuoi);
        window.draw(thongbao);
        window.display();
    }
}