// #include <iostream>
// #include <windows.h>
// #include <string>
// #include <conio.h>
// #include <fstream>
// #include <sstream>
// #include <cstdlib>
// #include "Program.h"
// #include "Student.h"
// #define FOR(i, a, b) for (int i = a; i <= b; i++)
// #define Coord pair<int, int>
// #define SE second
// #define FI first
// using namespace std;

// void SetWordColor(WORD wAttributes)
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(hConsole, wAttributes);
// }

// void gotoXY(short x, short y)
// {
//     COORD coord = {x, y};
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

// void GetConsoleSize(int &width, int &height)
// {
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//     width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//     height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
// }

// void ShowFile(const string &fileName)
// {
//     ifstream file(fileName);
//     if (!file.is_open())
//     {
//         cerr << "Khong the mo file: " << fileName << endl;
//         return;
//     }

//     ostringstream oss;
//     string line;
//     while (getline(file, line))
//     {
//         oss << line << '\n';
//     }
//     file.close();

//     SetWordColor(6);
//     cout << oss.str();
//     SetWordColor(7);
// }

// int LeftMargin = 50;
// int TopMargin = 2;

// Coord MouseCoord()
// {
//     HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//     SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

//     INPUT_RECORD inputRecord;
//     DWORD events;
//     COORD mousePos;

//     while (true)
//     {
//         ReadConsoleInput(hInput, &inputRecord, 1, &events);

//         if (inputRecord.EventType == MOUSE_EVENT)
//         {
//             MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

//             if (mouseEvent.dwEventFlags == 0 && (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
//             {
//                 mousePos = mouseEvent.dwMousePosition;
//                 return {mousePos.X, mousePos.Y};
//             }
//         }
//     }
// }

// void rectangle(int x, int y, int width, int height)
// {
//     char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
//     char Border = 205, UpBorder = 186;

//     // màu vàng sáng

//     // --- góc trên ---
//     gotoXY(x, y);
//     cout << LeftTop;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTop;

//     // --- thân ---
//     for (int i = 0; i < height - 2; i++)
//     {
//         gotoXY(x, y + i + 1);
//         cout << UpBorder;
//         for (int j = 0; j < width - 2; j++)
//             cout << " ";
//         cout << UpBorder;
//     }

//     // --- góc du?i ---
//     gotoXY(x, y + height - 1);
//     cout << LeftBottom;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightBottom;
// }

// void Resize(int width, int height)
// {
//     HWND console = GetConsoleWindow();
//     RECT r;
//     GetWindowRect(console, &r);
//     MoveWindow(console, r.left, r.top, width, height, TRUE);
// }

// string getPassword(int x, int y, int maxLength)
// {
//     string password = "";
//     char ch;
//     gotoXY(x, y);
//     while ((ch = _getch()) != 13)
//     { // ENTER
//         if (ch == 8)
//         { // BACKSPACE
//             if (!password.empty())
//             {
//                 password.pop_back();
//                 gotoXY(x + password.length(), y);
//                 cout << " ";
//                 gotoXY(x + password.length(), y);
//             }
//         }
//         else if (isprint(ch) && password.length() < maxLength)
//         {
//             password += ch;
//             cout << "*";
//         }
//     }
//     return password;
// }

// // menu dang nhap student
// Student* LoginStudent()
// {
//     system("cls");

//     // T?a d? và kích thu?c
//     int x = 20;
//     int y = 5;
//     int width = 73; // Can ch?nh l?i cho kh?p v?i 71 ký t? bên trong + 2 vi?n
//     int height = 14;

//     // Mã ký t? b?n dã d?nh nghia
//     char Border = 205;   // -
//     char LeftTee = 204;  // ¦
//     char RightTee = 185; // ¦

//     // 1. V? khung ngoài b?ng hàm c?a b?n
//     SetWordColor(14); // Màu xanh lá cho khung
//     rectangle(x, y, width, height);

//     // 2. V? các du?ng chia ngang bên trong
//     // Ðu?ng chia 1 (sau tiêu d?)
//     gotoXY(x, y + 4);
//     cout << LeftTee; // ¦
//     for (int i = 0; i < width - 2; i++)
//         cout << Border; // -
//     cout << RightTee;   // ¦

//     // Ðu?ng chia 2 (tru?c ph?n hu?ng d?n)
//     gotoXY(x, y + 11);
//     cout << LeftTee; // ¦
//     for (int i = 0; i < width - 2; i++)
//         cout << Border; // -
//     cout << RightTee;   // ¦

//     // 3. Vi?t n?i dung
//     // Tiêu d?
//     SetWordColor(6); // Màu vàng nh?t
//     gotoXY(x + 27, y + 2);
//     cout << "DANG NHAP - HOC VIEN";

//     // Hu?ng d?n
//     SetWordColor(8); // Màu xám
//     gotoXY(x + 50, y + 9);
//     cout << "(An mat khau bang '*')";
//     gotoXY(x + 22, y + 12);
//     cout << "(Nhan ENTER de xac nhan)";

//     // 4. V? ô nh?p li?u (Input boxes)
//     SetWordColor(8); // Màu xám cho ô
//     int inputX = x + 22;
//     int inputWidth = 35;
//     gotoXY(inputX, y + 6);
//     cout << "___________________________________";
//     gotoXY(inputX, y + 8);
//     cout << "___________________________________";

//     // 5. Nh?n thông tin
//     string id, password;

//     SetWordColor(6); // Màu tr?ng cho nhãn
//     gotoXY(x + 4, y + 6);
//     cout << "Nhap ID:";
//     gotoXY(x + 4, y + 8);
//     cout << "Mat Khau:";

//     SetWordColor(15); // Màu tr?ng sáng cho ch? nh?p
//     gotoXY(inputX, y + 6);
//     getline(cin, id);

//     // SetWordColor(6);
//     // gotoXY(x + 4, y + 8); cout << "Mat Khau:";
//     SetWordColor(15);
//     password = getPassword(inputX, y + 8, inputWidth);

//     // // 6. X? lý sau khi dang nh?p
//     SetWordColor(6);           // Màu xanh duong sáng
//     gotoXY(x, y + height + 1); // Di chuy?n xu?ng du?i khung
//     cout << "Dang kiem tra thong tin, vui long cho..." << endl;

//     Sleep(1000);
//     gotoXY(x, y + height + 2);
//     SetWordColor(10); // Màu xanh lá
//     Program p;
//     return p.LoginStudent(id, password);
//     // cout << "Dang nhap tai khoan thanh cong!          " << endl;
//     // gotoXY(x, y + height + 2);
//     // SetWordColor(6);
//     // cout << "Nhan phim bat ky de vao Bang Dieu Khien." << endl;
// }

// void PrintTitle()
// {
//     SetWordColor(6);
//     SetConsoleOutputCP(65001);
//     ShowFile("MenuTutor.txt");
//     SetConsoleOutputCP(437);
//     // SetConsoleOutputCP(65001);
//     // ShowFile("MenuTutor.txt");
// }

// void PrintMenu()
// {
//     // --- MOI: Tinh toan de can giua ---
//     int consoleWidth, consoleHeight;
//     GetConsoleSize(consoleWidth, consoleHeight); // Lay chieu rong console

//     int titleWidth = 60; // Chieu rong cua title box (58 ky tu + 2 vien)

//     // Tinh toan va SET LAI BIEN GLOBAL LeftMargin
//     LeftMargin = (consoleWidth - titleWidth) / 2;

//     // Reset lai GLOBAL TopMargin (de dam bao)
//     TopMargin = 3;
//     // --- KET THUC PHAN MOI ---

//     PrintTitle(); // Goi PrintTitle, bay gio no se tu dong can giua

//     // PrintTitle da set global TopMargin = 14,
//     // nen chung ta se dung gia tri do
//     int currentTopMargin = 14; // Bi?n local

//     // --- Ve hop "Chon vai tro" (Can giua so voi Title) ---
//     SetWordColor(14);
//     int box1_Width = 25;                                           // Chieu rong ben trong cua hop
//     int box1_X = LeftMargin + (titleWidth - (box1_Width + 2)) / 2; // Can giua

//     gotoXY(box1_X, currentTopMargin);
//     cout << char(201);
//     FOR(i, 1, box1_Width)
//         cout << char(205);
//     cout << char(187);

//     gotoXY(box1_X, currentTopMargin + 1);
//     cout << char(186);
//     FOR(i, 1, 2)
//         cout << " ";
//     SetWordColor(6);
//     cout << "Chon vai tro cua ban? ";
//     cout << " ";
//     SetWordColor(14);
//     cout << char(186);

//     gotoXY(box1_X, currentTopMargin + 2);
//     cout << char(200);
//     FOR(i, 1, box1_Width)
//         cout << char(205);
//     cout << char(188);

//     // --- Ve 3 nut (Can giua so voi Title) ---
//     int boxWidth = 16;
//     int spaceBetween = 8;
//     int totalWidth = 3 * boxWidth + 2 * spaceBetween; // = 64

//     // Lay trung tam cua Title Box (LeftMargin + 30)
//     int titleCenter = LeftMargin + (titleWidth / 2);

//     int firstBoxX = titleCenter - totalWidth / 2; // Vi tri X bat dau cua nut dau tien

//     int boxY = currentTopMargin + 5; // Y = 14 + 5 = 19
//     string titles[3] = {"Hoc Vien", "Gia Su", "Admin"};

//     FOR(b, 0, 2)
//     {
//         int x = firstBoxX + b * (boxWidth + spaceBetween);

//         gotoXY(x, boxY);
//         SetWordColor(14);
//         cout << char(201);
//         FOR(i, 1, boxWidth)
//             cout << char(205);
//         cout << char(187);

//         gotoXY(x, boxY + 1);
//         cout << char(186);
//         int padding = (boxWidth - titles[b].length()) / 2;
//         FOR(i, 1, padding)
//             cout << " ";
//         SetWordColor(6);
//         cout << titles[b];
//         FOR(i, 1, boxWidth - padding - titles[b].length())
//             cout << " ";
//         SetWordColor(14);
//         cout << char(186);

//         gotoXY(x, boxY + 2);
//         cout << char(200);
//         FOR(i, 1, boxWidth)
//             cout << char(205);
//         cout << char(188);
//     }

//     // --- Ve nut "Dang ky" (Can giua so voi Title) ---
//     boxY = boxY + 1; // boxY = 20
//     int registerBoxWidth = 25;
//     int registerBoxX = LeftMargin + (titleWidth - (registerBoxWidth + 2)) / 2;

//     gotoXY(registerBoxX, boxY + 3); // Y = 23
//     rectangle(registerBoxX, boxY + 3, 25, 3);
//     gotoXY(registerBoxX + 2, boxY + 4); // Y = 24
//     SetWordColor(6);
//     cout << "Dang ky tai khoan moi" << endl;

//     // --- Ve text huong dan (Can giua so voi Title) ---
//     string clickText = "Click vao mot vai tro de tiep tuc...";
//     int textX = LeftMargin + (titleWidth - clickText.length()) / 2;

//     gotoXY(textX, boxY + 7); // Y = 27
//     SetWordColor(10);
//     cout << clickText;
// }

// // dang nhap cho gia su
// void LoginTutor()
// {
//     system("cls");

//     // T?a d? và kích thu?c
//     int x = 20;
//     int y = 5;
//     int width = 73; // Can ch?nh l?i cho kh?p v?i 71 ký t? bên trong + 2 vi?n
//     int height = 14;

//     char Border = 205;   // -
//     char LeftTee = 204;  // ¦
//     char RightTee = 185; // ¦

//     SetWordColor(14); // Màu vang cho khung
//     rectangle(x, y, width, height);

//     gotoXY(x, y + 4);
//     cout << LeftTee; // ¦
//     for (int i = 0; i < width - 2; i++)
//         cout << Border; // -
//     cout << RightTee;   // ¦

//     gotoXY(x, y + 11);
//     cout << LeftTee; // ¦
//     for (int i = 0; i < width - 2; i++)
//         cout << Border; // -
//     cout << RightTee;   // ¦

//     // 3. Vi?t n?i dung
//     // Tiêu d?
//     SetWordColor(6); // Màu vàng nh?t
//     gotoXY(x + 27, y + 2);
//     cout << "DANG NHAP - GIA SU";

//     // Hu?ng d?n
//     SetWordColor(8); // Màu xám
//     gotoXY(x + 50, y + 9);
//     cout << "(An mat khau bang '*')";
//     gotoXY(x + 22, y + 12);
//     cout << "(Nhan ENTER de xac nhan)";

//     // 4. V? ô nh?p li?u (Input boxes)
//     SetWordColor(8); // Màu xám cho ô
//     int inputX = x + 22;
//     int inputWidth = 35;
//     gotoXY(inputX, y + 6);
//     cout << "___________________________________";
//     gotoXY(inputX, y + 8);
//     cout << "___________________________________";

//     // 5. Nh?n thông tin
//     string id, password;

//     SetWordColor(6); // Màu tr?ng cho nhãn
//     gotoXY(x + 4, y + 6);
//     cout << "Nhap ID:";
//     SetWordColor(15); // Màu tr?ng sáng cho ch? nh?p
//     gotoXY(inputX, y + 6);
//     getline(cin, id);

//     SetWordColor(6);
//     gotoXY(x + 4, y + 8);
//     cout << "Mat Khau:";
//     SetWordColor(15);
//     password = getPassword(inputX, y + 8, inputWidth);

//     // 6. X? lý sau khi dang nh?p
//     SetWordColor(6);           // Màu xanh duong sáng
//     gotoXY(x, y + height + 1); // Di chuy?n xu?ng du?i khung
//     cout << "Dang kiem tra thong tin, vui long cho..." << endl;

//     Sleep(1000);
//     gotoXY(x, y + height + 1);
//     SetWordColor(10); // Màu xanh lá
//     cout << "Dang nhap tai khoan thanh cong!          " << endl;
//     gotoXY(x, y + height + 2);
//     SetWordColor(6);
//     cout << "Nhan phim bat ky de vao Bang Dieu Khien." << endl;
//     _getch();
// }

// void LoginAdmin()
// {
//     system("cls");
//     int width = 25, height = 4;
//     int x = 50 - 2;
//     int y = 2;

//     // V? khung dang nh?p
//     rectangle(x, y, width, height);

//     // Hai dòng ch?
//     string title = "DANG NHAP";
//     string subtitle = "voi vai tro Admin";

//     // Can gi?a ch? trong khung
//     int titleX = x + (width - title.length()) / 2;
//     int subtitleX = x + (width - subtitle.length()) / 2;

//     SetWordColor(14); // màu vàng sáng
//     gotoXY(titleX, y + 1);
//     SetWordColor(6);
//     cout << title;
//     gotoXY(subtitleX, y + 2);
//     cout << subtitle;

//     // Nh?p thông tin
//     string id, password;
//     gotoXY(LeftMargin - 5, y + height + 2);
//     SetWordColor(6);
//     cout << "Nhap ID: ";
//     SetWordColor(7);
//     getline(cin, id);

//     gotoXY(LeftMargin - 5, y + height + 3);
//     SetWordColor(6);
//     cout << "Nhap Password: ";
//     SetWordColor(7);
//     getline(cin, password);
//     gotoXY(LeftMargin - 5, y + height + 4);
//     cout << "Dang nhap tai khoan thanh cong\n";
//     gotoXY(LeftMargin - 5, y + height + 5);
//     cout << "Chon tiep chuc nang ";
// }

// void ShowTutorMenu()
// {
//     system("cls");
//     // Ký t? khung
//     system("cls");
//     char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
//     char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

//     int consoleWidth, consoleHeight;
//     GetConsoleSize(consoleWidth, consoleHeight);

//     // N?i dung hi?n th?
//     std::string title = "MENU GIA SU";
//     std::string welcome = "Chao mung: Nguyen Van A (ID: GS123)";

//     int boxWidth = 60;
//     int startX = (consoleWidth - boxWidth) / 2;

//     SetWordColor(14);

//     // --- Dòng trên cùng ---
//     std::cout << std::string(startX, ' ') << LeftTop;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << RightTop << "\n";

//     // --- Dòng tiêu d? ---
//     std::cout << std::string(startX, ' ') << UpBorder;
//     int padTitle = (boxWidth - 2 - title.size()) / 2;
//     SetWordColor(6);
//     std::cout << std::string(padTitle, ' ') << title;
//     SetWordColor(14);
//     std::cout << std::string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

//     // --- Dòng ngan cách ---
//     std::cout << std::string(startX, ' ') << CrossLeft;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << CrossRight << "\n";

//     // --- Dòng chào m?ng ---
//     std::cout << std::string(startX, ' ') << UpBorder;
//     int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
//     SetWordColor(6);
//     std::cout << std::string(padWelcome, ' ') << welcome;
//     SetWordColor(14);
//     std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

//     // --- Dòng cu?i ---
//     std::cout << std::string(startX, ' ') << LeftBottom;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << RightBottom << "\n";

//     // ======= Các ô ch?c nang =======
//     int menuWidth = 34;    // tang chi?u r?ng ô d? ch?a d? ch?
//     int spaceBetween = 10; // kho?ng cách gi?a 2 c?t
//     int totalMenuWidth = menuWidth * 2 + spaceBetween;

//     int startMenuX = (consoleWidth - totalMenuWidth) / 2; // canh gi?a theo khung trên
//     int leftX = startMenuX;
//     int rightX = leftX + menuWidth + spaceBetween;

//     int startY = 9; // dòng b?t d?u phía du?i khung
//     int gapY = 3;   // kho?ng cách gi?a các hàng

//     // --- C?t 1 & 2 ---
//     SetWordColor(14);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "1. Hien thi thong tin ca nhan";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "2. Cap nhat thong tin ca nhan";

//     startY += gapY;
//     SetWordColor(14);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "3. Kiem tra so du";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "4. Hien thi danh sach mon hoc";

//     startY += gapY;
//     SetWordColor(14);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "5. Hien thi danh sach hoc sinh";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "6. Them mon hoc moi";

//     startY += gapY;
//     SetWordColor(14);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "7. Cap nhat thong tin mon hoc";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "8. Xem danh gia";

//     gotoXY(50, 23);
//     SetWordColor(4);
//     rectangle(50, 23, 20, 3);
//     SetWordColor(6);
//     gotoXY(55, 23 + 1);
//     cout << "Dang Xuat" << endl;
//     SetWordColor(7);
// }

// void ShowStudentMenu()
// {
//     system("cls");
//     // Ký t? khung
//     char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
//     char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

//     int consoleWidth, consoleHeight;
//     GetConsoleSize(consoleWidth, consoleHeight);

//     // N?i dung hi?n th?
//     std::string title = "MENU HOC VIEN";
//     std::string welcome = "Chao mung ban Nguyen Van A (ID: GS123)";

//     int boxWidth = 60;
//     int startX = (consoleWidth - boxWidth) / 2;

//     // Màu khung
//     SetWordColor(9); // xanh duong sáng

//     // --- Dòng trên cùng ---
//     std::cout << std::string(startX, ' ') << LeftTop;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << RightTop << "\n";

//     // --- Dòng tiêu d? ---
//     std::cout << std::string(startX, ' ') << UpBorder;
//     int padTitle = (boxWidth - 2 - title.size()) / 2;
//     SetWordColor(6); // ch? xanh duong d?m
//     std::cout << std::string(padTitle, ' ') << title;
//     SetWordColor(9);
//     std::cout << std::string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

//     // --- Dòng ngan cách ---
//     std::cout << std::string(startX, ' ') << CrossLeft;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << CrossRight << "\n";

//     // --- Dòng chào m?ng ---
//     std::cout << std::string(startX, ' ') << UpBorder;
//     int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
//     SetWordColor(6);
//     std::cout << std::string(padWelcome, ' ') << welcome;
//     SetWordColor(9);
//     std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

//     // --- Dòng cu?i ---
//     std::cout << std::string(startX, ' ') << LeftBottom;
//     for (int i = 0; i < boxWidth - 2; i++)
//         std::cout << Border;
//     std::cout << RightBottom << "\n";

//     // ======= Các ô ch?c nang =======
//     int menuWidth = 34;
//     int spaceBetween = 10;
//     int totalMenuWidth = menuWidth * 2 + spaceBetween;

//     int startMenuX = (consoleWidth - totalMenuWidth) / 2;
//     int leftX = startMenuX;                        // 21 khung trai
//     int rightX = leftX + menuWidth + spaceBetween; // 65 khung bên phai

//     int startY = 9;
//     int gapY = 3;
//     // moi khung co toa do x (21,55)
//     // moi khung co toa do y (9,12)

//     // --- C?t 1 & 2 ---
//     SetWordColor(9); // màu khung xanh duong sáng
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6); // ch? xanh duong d?m
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "1. Hien thi thong tin ca nhan";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "2. Cap nhat thong tin ca nhan";

//     startY += gapY;
//     SetWordColor(9);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "3. Kiem tra so du";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "4. Nap tien";

//     startY += gapY;
//     SetWordColor(9);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "5. Hien thi danh sach mon hoc";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "6. Hien thi danh sach gia su";

//     startY += gapY;
//     SetWordColor(9);
//     rectangle(leftX, startY, menuWidth, 3);
//     rectangle(rightX, startY, menuWidth, 3);

//     SetWordColor(6);
//     gotoXY(leftX + 1, startY + 1);
//     std::cout << "7. Tim kiem va them gia su";
//     gotoXY(rightX + 1, startY + 1);
//     std::cout << "8. Danh gia gia su";

//     // --- Ô Ðang Xu?t ---
//     int logoutX = 50;
//     int logoutY = 23;
//     SetWordColor(9);
//     rectangle(logoutX, logoutY, 20, 3);
//     SetWordColor(6);
//     gotoXY(logoutX + 5, logoutY + 1);
//     std::cout << "Dang Xuat" << std::endl;

//     SetWordColor(14); // reset v? m?c d?nh
// }

// void FindTutorScreen()
// {
//     system("cls");

//     // 1. T?a d? và Kích thu?c
//     int x = 5;       // T?a d? X
//     int y = 3;       // T?a d? Y
//     int width = 73;  // 71 ký t? bên trong + 2 vi?n
//     int height = 18; // 18 dòng

//     // Mã ký t? CP437 cho du?ng chia
//     char Border = 205;   // -
//     char LeftTee = 204;  // ¦
//     char RightTee = 185; // ¦

//     // 2. V? khung ngoài
//     SetWordColor(11); // Màu xanh duong cho khung
//     rectangle(x, y, width, height);

//     // 3. V? các du?ng chia ngang
//     SetWordColor(11); // Ð?m b?o màu cho du?ng chia
//     // Ðu?ng chia 1: Du?i tiêu d?
//     gotoXY(x, y + 2);
//     cout << LeftTee;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTee;

//     // Ðu?ng chia 2: Du?i b? l?c
//     gotoXY(x, y + 7);
//     cout << LeftTee;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTee;

//     // Ðu?ng chia 3: Du?i k?t qu?
//     gotoXY(x, y + 15);
//     cout << LeftTee;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTee;

//     // 4. Vi?t n?i dung tinh
//     // Tiêu d?
//     SetWordColor(15); // Tr?ng sáng
//     gotoXY(x + 28, y + 1);
//     cout << "[ 7. TIM KIEM GIA SU ]";

//     // Tiêu d? các m?c
//     SetWordColor(14); // Vàng
//     gotoXY(x + 19, y + 3);
//     cout << "[ BO LOC (Nhan ENTER de bo qua) ]";
//     gotoXY(x + 32, y + 8);
//     cout << "[ KET QUA ]";
//     gotoXY(x + 27, y + 16);
//     cout << "[ Trang 1 / 5 ]"; // Gi? l?p

//     // Nhãn b? l?c
//     SetWordColor(7); // Tr?ng xám
//     gotoXY(x + 3, y + 5);
//     cout << "Tim theo Ma Mon hoc: [            ]";
//     gotoXY(x + 34, y + 5);
//     cout << "(Xem ID o muc 5)";
//     gotoXY(x + 3, y + 6);
//     cout << "Tim theo Khu vuc:    [            ]";

//     // B?ng k?t qu?
//     SetWordColor(10); // Xanh lá cho header
//     gotoXY(x + 3, y + 10);
//     cout << "ID   | HO TEN                | MON DAY             | RATING";
//     gotoXY(x + 3, y + 11);
//     cout << "-------------------------------------------------------------------";

//     // D? li?u gi? l?p (Mock data)
//     SetWordColor(15); // Tr?ng sáng
//     gotoXY(x + 3, y + 12);
//     cout << "GS003| Tran Van B            | Toan 12, Ly 11      | 4.5/5";
//     gotoXY(x + 3, y + 13);
//     cout << "GS008| Nguyen Thi A          | Hoa 10              | 4.8/5";
//     gotoXY(x + 3, y + 14);
//     cout << "...";

//     // Hu?ng d?n
//     SetWordColor(7);
//     gotoXY(x + 3, y + 17);
//     cout << "(Nhap ID, 'N' next, 'P' prev, 'Q' quit)";

//     // 5. Nh?n Input cho b? l?c
//     string filterMon, filterKhuVuc;

//     SetWordColor(15);      // Màu nh?p li?u
//     gotoXY(x + 23, y + 5); // T?a d? ô "Ma Mon hoc"
//     getline(cin, filterMon);

//     gotoXY(x + 23, y + 6); // T?a d? ô "Khu vuc"
//     getline(cin, filterKhuVuc);

//     // (Sau khi nh?p, b?n s? x? lý logic tìm ki?m và hi?n th? k?t qu? ? dây)

//     // 6. Ch? l?nh ti?p theo
//     SetWordColor(15);
//     gotoXY(x, y + height + 1); // Di chuy?n xu?ng du?i khung
//     cout << "Da tim voi Ma Mon: '" << filterMon << "', Khu Vuc: '" << filterKhuVuc << "'" << endl;
//     gotoXY(x, y + height + 2);
//     cout << "Nhan phim bat ky de quay lai menu... ";
//     _getch();
// }

// void HandleStudentMenu(Student* student)
// {
//     ShowStudentMenu(); // 1. Ve menu sinh vien lan dau tien.

//     while (true)
//     {                               // 2. Bat dau vong lap su kien cho menu sinh vien.
//         Coord click = MouseCoord(); // 3. Cho mot CLICK MOI tu nguoi dung.

//         // Kiem tra nut [7. Tim kiem va them gia su]
//         // Toa do X: (leftX) 21 -> (leftX + menuWidth - 1) 54
//         // Toa do Y: (startY row 4) 18 -> (startY + 3 - 1) 20
//         if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
//         {
//             FindTutorScreen(); // Chay chuc nang tim kiem

//             // QUAN TRONG: Sau khi chuc nang ket thuc, ve lai menu
//             ShowStudentMenu();
//         }

//         // Kiem tra nut [Dang Xuat]
//         // Toa do X: (logoutX) 50 -> (logoutX + 20 - 1) 69
//         // Toa do Y: (logoutY) 23 -> (logoutY + 3 - 1) 25
//         else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
//         {
//             break; // 4. Thoat khoi vong lap while(true) nay
//         }

//         // ... Them cac else if cho cac nut khac (1-6, 8) o day ...
//         // else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 21 && click.FI <= 54) {
//         //     ShowStudentInfo(); // Vi du cho nut 1
//         //     ShowStudentMenu(); // Luon ve lai menu sau khi xong
//         // }
//     }
//     // 5. Sau khi 'break', ham nay ket thuc va quay tro lai ham main
// }

// void HandleTutorMenu()
// {
//     ShowTutorMenu();
//     while (true)
//     {
//         Coord click = MouseCoord();
//         if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
//         {
//             //.....
//         }
//         else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
//         {
//             break;
//         }
//     }
// }
// /**
//  *@brief
//  **/
// int main() noexcept
// {
//     Program prog;
//     PrintMenu(); // 1. Ve menu chinh (Login, Tutor, Admin)

//     while (1)
//     {
//         Coord click = MouseCoord(); // 2. Cho click tren menu chinh

//         // Kiem tra nut [Hoc Vien]
//         // Y: 19 -> 21, X: 46 -> 62
//         if (click.SE >= 19 && click.SE <= 21 && click.FI >= 28 && click.FI <= 45)
//         {
//             Student *student = LoginStudent(); // Chay man hinh dang nhap
//             // Neu dang nhap thanh cong (code cua ban auto thanh cong)
//             // GOI HAM XU LY MENU CUA HOC VIEN
//             if(student == nullptr) continue;
//             getch();
//             HandleStudentMenu(student);

//             // 3. Sau khi HandleStudentMenu() ket thuc (do an Dang Xuat),
//             // chung ta can VE LAI menu chinh
//             system("cls");
//             PrintMenu();
//         }

//         // Kiem tra nut [Teacher]
//         // Y: 19 -> 21, X: 70 -> 86
//         else if (click.SE >= 19 && click.SE <= 21 && click.FI >= 52 && click.FI <= 69)
//         {
//             Student *student = LoginStudent();
//             HandleTutorMenu(); // Ban se can tao mot ham "HandleTutorMenu()"
//                                // tuong tu nhu HandleStudentMenu()

//             // Tam thoi _getch() de xem menu truoc khi ve lai menu chinh
//             // _getch();
//             system("cls");
//             PrintMenu();
//         }

//         // Kiem tra nut [Admin]
//         // Y: 19 -> 21, X: 94 -> 110
//         else if (click.SE >= 19 && click.SE <= 21 && click.FI >= 76 && click.FI <= 93)
//         {
//             LoginAdmin();
//             // ... (Tuong tu, ban se can mot HandleAdminMenu())

//             _getch();
//             system("cls");
//             PrintMenu();
//         }
//     }
// }