#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h> 
#include <fstream>
#include <sstream>
#include <cstdlib>
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define Coord pair<int, int>
#define SE second
#define FI first
using namespace std;

void SetWordColor(WORD wAttributes)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, wAttributes);
}

void gotoXY(short x, short y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GetConsoleSize(int &width, int &height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ShowFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << fileName << endl;
        return;
    }

    ostringstream oss;
    string line;
    while (getline(file, line)) {
        oss << line << '\n';
    }
    file.close();

    SetWordColor(6);
    cout << oss.str();
    SetWordColor(7);
}

int LeftMargin = 50;
int TopMargin = 2;

Coord MouseCoord()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD inputRecord;
    DWORD events;
    COORD mousePos;

    while (true)
    {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            if (mouseEvent.dwEventFlags == 0 && (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
            {
                mousePos = mouseEvent.dwMousePosition;
                return {mousePos.X, mousePos.Y};
            }
        }
    }
}

void rectangle(int x, int y, int width, int height)
{
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186;

     // màu vàng sáng

    // --- góc trên ---
    gotoXY(x, y);
    cout << LeftTop;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTop;

    // --- thân ---
    for (int i = 0; i < height - 2; i++)
    {
        gotoXY(x, y + i + 1);
        cout << UpBorder;
        for (int j = 0; j < width - 2; j++) cout << " ";
        cout << UpBorder;
    }

    // --- góc duoi ---
    gotoXY(x, y + height - 1);
    cout << LeftBottom;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightBottom;
}

void Resize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

string getPassword(int x, int y, int maxLength) {
    string password = "";
    char ch;
    gotoXY(x, y);
    while ((ch = _getch()) != 13) { // ENTER
        if (ch == 8) { // BACKSPACE
            if (!password.empty()) {
                password.pop_back();
                gotoXY(x + password.length(), y);
                cout << " ";
                gotoXY(x + password.length(), y);
            }
        }
        else if (isprint(ch) && password.length() < maxLength) {
            password += ch;
            cout << "*";
        }
    }
    return password;
}

void LoginUser() {
    system("cls");

    int x = 15;
    int y = 3;
    int width = 55;     // Tang chieu rong (goc là 30)
    int height_1 = 3;   // chieu cao cua khung
    int height_2 = 15;  

    SetWordColor(14); // Màu vàng sáng
    rectangle(x, y, width, height_1);

    rectangle(x, y + height_1 - 1, width, height_2 ); 

    std::string title = "DANG KY TAI KHOAN";
    int title_len = title.length();
    
    int title_x = x + (width - title_len) / 2;
    int title_y = y + (height_1 / 2);

    gotoXY(title_x, title_y);
    SetWordColor(6); // Màu vàng cam
    std::cout << title;

    int content_x = x + 3; 
    int content_y = (y + height_1 - 1) + 2; 

    gotoXY(content_x, content_y);
    SetWordColor(6); // Màu vàng
    cout << "Nhap ID: ";
	string ID;
    getline(cin, ID); //Nhap ID: "
    
    gotoXY(content_x, content_y+1);
    cout<<"Nhap vai tro cua ban(Gia su/ Hoc vien): ";
    string t;
    getline(cin,t);
    
    gotoXY(content_x, content_y+2);
    cout<<"Nhap ten cua ban: ";
    string name;
    getline(cin, name);
    // nhap them code vao day ...
    

    SetWordColor(7); // white
    _getch();
}

//menu dang nhap student
void LoginStudent() {
    system("cls");
    // toa do 
    int x = 20;
    int y = 5;
    int width = 73;  //Can chinh
    int height = 14;

    char Border = 205;   // -
    char LeftTee = 204;  // ¦
    char RightTee = 185; // ¦


    // ve khung 
    SetWordColor(14); // Màu xanh lá cho khung
    rectangle(x, y, width, height);

    // ve duong chia ben trong
    gotoXY(x, y + 4);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++) cout << Border; // -
    cout << RightTee; // ¦


    gotoXY(x, y + 11);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++) cout << Border; // -
    cout << RightTee; // ¦


    SetWordColor(6); 
    gotoXY(x + 27, y + 2); cout << "DANG NHAP - HOC VIEN";

    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9); cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12); cout << "(Nhan ENTER de xac nhan)";

    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;
    gotoXY(inputX, y + 6); cout << "___________________________________";
    gotoXY(inputX, y + 8); cout << "___________________________________";

    // 5.Nhap thông tin
    string id, password;
    
    SetWordColor(6); // Màu trang cho nhãn
    gotoXY(x + 4, y + 6); cout << "Nhap ID:";
    SetWordColor(15); 
    gotoXY(inputX, y + 6);
    getline(cin, id);

    SetWordColor(6);
    gotoXY(x + 4, y + 8); cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // 6. Xu lý sau khi dang nhap
    SetWordColor(6); // Màu xanh duong sáng
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
    cout << "Dang kiem tra thong tin, vui long cho..." << endl;
    
    Sleep(1000); 
    gotoXY(x, y + height + 1);
    SetWordColor(10); // Màu xanh lá
    cout << "Dang nhap tai khoan thanh cong!          " << endl;
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de vao Bang Dieu Khien." << endl;
    _getch();
}

void PrintTitle()
{
    SetWordColor(6);
    SetConsoleOutputCP(65001);// chuyen doi qua UCRT -8 
    ShowFile("MenuTutor.txt");
    SetConsoleOutputCP(437); // chuyen ve lai ASCII
    // SetConsoleOutputCP(65001);
    // ShowFile("MenuTutor.txt");
    
}

//void PrintMenu(){
//    PrintTitle();
//    int LeftMargin = 50;
//    int TopMargin = 14;
//
//    SetWordColor(14);
//    gotoXY(LeftMargin, TopMargin);
//    FOR(i,1,15) cout<<" ";
//    cout << char(201);
//    FOR(i,1,25)  cout<<char(205);
//    cout<<char(187);
//
//    LeftMargin = 50 + 15;
//    gotoXY(LeftMargin, TopMargin + 1);
//    cout<<char(186);
//    FOR(i,1,2) cout<<" ";
//    SetWordColor(6);
//    cout<<"Chon vai tro cua ban? ";
//    cout<<" ";
//    SetWordColor(14);
//    cout<<char(186);
//
//    gotoXY(LeftMargin, TopMargin + 2);
//    cout<<char(200);
//    FOR(i,1,25) cout<<char(205);
//    cout<<char(188);
//
//    int boxWidth = 16;      
//    int spaceBetween = 8;   
//    int totalWidth = 3 * boxWidth + 2 * spaceBetween;
//    int screenCenter = LeftMargin + 13; 
//    int firstBoxX = screenCenter - totalWidth / 2;
//
//    int boxY = TopMargin + 5;
//    string titles[3] = {"Hoc Vien", "Teacher", "Admin"};
//    // hoc vien 31, 19
//    // teacher 55, 19
//    // admin 79 ,19
//
//    FOR(b,0,2) {
//        int x = firstBoxX + b * (boxWidth + spaceBetween);
//
//        gotoXY(x, boxY);
//        SetWordColor(14);
//        cout << char(201);
//        FOR(i,1,boxWidth) cout<<char(205);
//        cout<<char(187);
//
//        gotoXY(x, boxY + 1);
//        cout<<char(186);
//        int padding = (boxWidth - titles[b].length()) / 2;
//        FOR(i,1,padding) cout<<" ";
//        SetWordColor(6);
//        cout<<titles[b];
//        FOR(i,1,boxWidth - padding - titles[b].length()) cout<<" ";
//        SetWordColor(14);
//        cout<<char(186);
//
//        gotoXY(x, boxY + 2);
//        cout<<char(200);
//        FOR(i,1,boxWidth) cout<<char(205);
//        cout<<char(188);
//    }
//    LeftMargin = LeftMargin+2;
//    boxY = boxY + 1;
//    gotoXY(LeftMargin, boxY+3);
//    rectangle(LeftMargin, boxY+3, 25,3 );
//    gotoXY(LeftMargin+2, boxY+4);
//    SetWordColor(6);
//    cout<<"Dang ky tai khoan moi"<<endl;
//
//    // --- Thêm hu?ng d?n click ---
//    gotoXY(LeftMargin , boxY + 7);
//    SetWordColor(10);
//    cout << "Click vao mot vai tro de tiep tuc...";
//}

// thay cho Menu
void PrintMenu() {
    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight); // Lay chieu rong console
    
    int titleWidth = 60; // Chieu rong cua title box (58 ky tu + 2 vien)
    
    LeftMargin = (consoleWidth - titleWidth) / 2; 
    

    TopMargin = 3;

    PrintTitle(); 

    //  TopMargin = 14,
    int currentTopMargin = 15; 

    // --- Ve hop "Chon vai tro" (Can giua so voi Title) ---
    SetWordColor(14);
    int box1_Width = 25; // Chieu rong ben trong cua hop
    int box1_X = LeftMargin + (titleWidth - (box1_Width + 2)) / 2 + 2; // Can giua

    gotoXY(box1_X, currentTopMargin);
    cout << char(201);
    FOR(i, 1, box1_Width) cout << char(205);
    cout << char(187);

    gotoXY(box1_X, currentTopMargin + 1);
    cout << char(186);
    FOR(i, 1, 2) cout << " ";
    SetWordColor(6);
    cout << "Chon vai tro cua ban? ";
    cout << " ";
    SetWordColor(14);
    cout << char(186);

    gotoXY(box1_X, currentTopMargin + 2);
    cout << char(200);
    FOR(i, 1, box1_Width) cout << char(205);
    cout << char(188);

    //Ve 3 nut (Can giua so voi Title) 
    int boxWidth = 16;
    int spaceBetween = 8;
    int totalWidth = 3 * boxWidth + 2 * spaceBetween; // = 64
    
    // Lay trung tam cua Title Box (LeftMargin + 30)
    int titleCenter = LeftMargin + (titleWidth / 2); 
    
    int firstBoxX = titleCenter - totalWidth / 2; // Vi tri X bat dau cua nut dau tien

    int boxY = currentTopMargin + 5; // Y = 14 + 5 = 19
    string titles[3] = {"Hoc Vien", "Gia Su", "Admin"};

    FOR(b, 0, 2) {
        int x = firstBoxX + b * (boxWidth + spaceBetween);

        gotoXY(x, boxY);
        SetWordColor(14);
        cout << char(201);
        FOR(i, 1, boxWidth) cout << char(205);
        cout << char(187);

        gotoXY(x, boxY + 1);
        cout << char(186);
        int padding = (boxWidth - titles[b].length()) / 2;
        FOR(i, 1, padding) cout << " ";
        SetWordColor(6);
        cout << titles[b];
        FOR(i, 1, boxWidth - padding - titles[b].length()) cout << " ";
        SetWordColor(14);
        cout << char(186);

        gotoXY(x, boxY + 2);
        cout << char(200);
        FOR(i, 1, boxWidth) cout << char(205);
        cout << char(188);
    }
    
    // --- Ve nut "Dang ky" 
    boxY = boxY + 1; // boxY = 20
    int registerBoxWidth = 20;
    int registerBoxX = LeftMargin + (titleWidth - (registerBoxWidth + 2)) / 2;

    gotoXY(registerBoxX, boxY + 3); // Y = 23
    rectangle(registerBoxX, boxY + 3, 25, 3);
    gotoXY(registerBoxX + 2, boxY + 4); // Y = 24
    SetWordColor(6);
    cout << "Dang ky tai khoan moi" << endl;
    // ve nut thoat
    
    int exitBoxWidth = 16; 
    string exitTitle = "Thoat";
    
    int exitBoxX = firstBoxX + 2 * (boxWidth + spaceBetween);

    int exitBoxY = boxY + 3; 

    gotoXY(exitBoxX, exitBoxY);
    SetWordColor(14); // Mau vien
    cout << char(201);
    FOR(i, 1, exitBoxWidth) cout << char(205);
    cout << char(187);

    gotoXY(exitBoxX, exitBoxY + 1);
    cout << char(186);
    int padding = (exitBoxWidth - exitTitle.length()) / 2;
    FOR(i, 1, padding) cout << " ";
    SetWordColor(6); // Mau chu
    cout << exitTitle;
    // Can chinh lai cho deu
    FOR(i, 1, exitBoxWidth - padding - exitTitle.length()) cout << " ";
    SetWordColor(14); // Mau vien
    cout << char(186);

    gotoXY(exitBoxX, exitBoxY + 2);
    cout << char(200);
    FOR(i, 1, exitBoxWidth) cout << char(205);
    cout << char(188);

    // Ve text huong dan 
    string clickText = "Click vao mot vai tro de tiep tuc...";
    int textX = LeftMargin + (titleWidth - clickText.length()) / 2;
    
    gotoXY(textX, boxY + 7); // Y = 27
    SetWordColor(10);
    cout << clickText;
}


// dang nhap cho gia su 
void LoginTutor() {
    system("cls");

    // Toa do 
    int x = 20;
    int y = 5;
    int width = 73;  // can chinh 
    int height = 14;

    char Border = 205;   // -
    char LeftTee = 204;  // ¦
    char RightTee = 185; // ¦

    SetWordColor(14); // Màu vang cho khung
    rectangle(x, y, width, height);

    gotoXY(x, y + 4);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++) cout << Border; // -
    cout << RightTee; // ¦

    gotoXY(x, y + 11);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++) cout << Border; // -
    cout << RightTee; // ¦

    // 3. Noi dung
    // Tiêu d?
    SetWordColor(6); // Màu vàng 
    gotoXY(x + 27, y + 2); cout << "DANG NHAP - GIA SU";

    // Huong dan
    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9); cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12); cout << "(Nhan ENTER de xac nhan)";

    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;
    gotoXY(inputX, y + 6); cout << "___________________________________";
    gotoXY(inputX, y + 8); cout << "___________________________________";

    // 5. nhap thông tin
    string id, password;
    
    SetWordColor(6); 
    gotoXY(x + 4, y + 6); cout << "Nhap ID:";
    SetWordColor(15); 
    gotoXY(inputX, y + 6);
    getline(cin, id);

    SetWordColor(6);
    gotoXY(x + 4, y + 8); cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // Xuy ly sau dang nhap
    SetWordColor(6); // Màu xanh duong sáng
    gotoXY(x, y + height + 1); 
    cout << "Dang kiem tra thong tin, vui long cho..." << endl;
    
    Sleep(1000); 
    gotoXY(x, y + height + 1);
    SetWordColor(10); // Màu xanh lá
    cout << "Dang nhap tai khoan thanh cong!          " << endl;
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de vao Bang Dieu Khien." << endl;
    _getch();
}
// dang nhap hoc vien
//void LoginStudent() {
//	system("cls");
//    int width = 25, height = 4;
//    int x = 50 - 2; 
//    int y = 2 ;
//
//    // V? khung dang nh?p
//    rectangle(x, y, width, height);
//
//    // Hai dòng ch?
//    string title = "DANG NHAP";
//    string subtitle = "voi vai tro hoc vien";
//
//    // Can gi?a ch? trong khung
//    int titleX = x + (width - title.length()) / 2;
//    int subtitleX = x + (width - subtitle.length()) / 2;
//
//    SetWordColor(14); // màu vàng sáng
//    gotoXY(titleX, y + 1);
//    SetWordColor(6);
//    cout << title;
//    gotoXY(subtitleX, y + 2);
//    cout << subtitle;
//
//    // Nh?p thông tin
//    string id, password;
//    gotoXY(LeftMargin - 5, y + height + 2);
//    SetWordColor(6);
//    cout << "Nhap ID: ";
//    SetWordColor(7);
//    getline(cin, id);
//
//    gotoXY(LeftMargin - 5, y + height + 3);
//    SetWordColor(6);
//    cout << "Nhap Password: ";
//    SetWordColor(7);
//    getline(cin, password);
//    gotoXY(LeftMargin - 5, y + height + 4);
//    cout << "Dang nhap tai khoan thanh cong\n";
//    gotoXY(LeftMargin - 5, y + height + 5);
//    cout << "Chon tiep chuc nang ";
//}

void LoginAdmin() {
	system("cls");
    int width = 25, height = 4;
    int x = 50 - 2; 
    int y = 2 ;

    // Ve Khung dang nhap
    rectangle(x, y, width, height);

    string title = "DANG NHAP";
    string subtitle = "voi vai tro Admin";

    // Can giua
    int titleX = x + (width - title.length()) / 2;
    int subtitleX = x + (width - subtitle.length()) / 2;

    SetWordColor(14); // màu vàng sáng
    gotoXY(titleX, y + 1);
    SetWordColor(6);
    cout << title;
    gotoXY(subtitleX, y + 2);
    cout << subtitle;

    // Nhap thông tin
    string id, password;
    gotoXY(LeftMargin - 5, y + height + 2);
    SetWordColor(6);
    cout << "Nhap ID: ";
    SetWordColor(7);
    getline(cin, id);

    gotoXY(LeftMargin - 5, y + height + 3);
    SetWordColor(6);
    cout << "Nhap Password: ";
    SetWordColor(7);
    getline(cin, password);
    gotoXY(LeftMargin - 5, y + height + 4);
    cout << "Dang nhap tai khoan thanh cong\n";
    gotoXY(LeftMargin - 5, y + height + 5);
    cout << "Chon tiep chuc nang ";
}

void ShowTutorMenu() {
	system("cls");
    // Ký t? khung
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // N?i dung hi?n th?
    std::string title = "MENU GIA SU";
    std::string welcome = "Chao mung: Nguyen Van A (ID: GS123)";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    SetWordColor(14);

    // --- Dòng trên cùng ---
    std::cout << std::string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6);
    std::cout << std::string(padTitle, ' ') << title;
    SetWordColor(14);
    std::cout << std::string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    std::cout << std::string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << CrossRight << "\n";

    // --- Dòng chào mung ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    std::cout << std::string(padWelcome, ' ') << welcome;
    SetWordColor(14);
    std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    std::cout << std::string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightBottom << "\n";

    // Các ô chuc nang 
    int menuWidth = 34; // tang chieu rong cac ô
    int spaceBetween = 10; // khoảng cách giữa 2 cột
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2; // canh giua theo khung trên
    int leftX = startMenuX;
    int rightX = leftX + menuWidth + spaceBetween;

    int startY = 9; // dòng bat dau phía duoi khung
    int gapY = 3;   // khoang cach giua các hàng

    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "1. Hien thi thong tin ca nhan";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "2. Cap nhat thong tin ca nhan";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "4. Hien thi danh sach mon hoc";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "5. Hien thi danh sach hoc sinh";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "6. Them mon hoc moi";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "7. Cap nhat thong tin mon hoc";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "8. Xem danh gia";
    
    gotoXY(50,23);
    SetWordColor(4);
    rectangle(50,23,20, 3);
    SetWordColor(6);
    gotoXY(55,23+1);
    cout<<"Dang Xuat"<<endl;
    SetWordColor(7);
}

void ShowStudentMenu() {
	system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // Noi dung hien thi
    std::string title = "MENU HOC VIEN";
    std::string welcome = "Chao mung ban Nguyen Van A (ID: GS123)";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    // Màu khung
    SetWordColor(9); // xanh duong sáng

    // --- Dòng trên cùng ---
    std::cout << std::string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6); // vang
    std::cout << std::string(padTitle, ' ') << title;
    SetWordColor(9);
    std::cout << std::string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    std::cout << std::string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << CrossRight << "\n";

    // --- Dòng chào mung ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    std::cout << std::string(padWelcome, ' ') << welcome;
    SetWordColor(9);
    std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    std::cout << std::string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightBottom << "\n";

    // ======= Các ô chuc nang =======
    int menuWidth = 34;
    int spaceBetween = 10;
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2;
    int leftX = startMenuX; // 21 khung trai
    int rightX = leftX + menuWidth + spaceBetween;//65 khung bên phai 

    int startY = 9;
    int gapY = 3;
    // moi khung co toa do x (21,55)
    // moi khung co toa do y (9,12)

    // --- Ct 1 & 2 ---
    SetWordColor(9); // màu khung xanh duong sáng
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6); // vang
    gotoXY(leftX + 1, startY + 1);
    std::cout << "1. Hien thi thong tin ca nhan";  
    gotoXY(rightX + 1, startY + 1);
    std::cout << "2. Cap nhat thong tin ca nhan";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "4. Nap tien";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "5. Hien thi danh sach mon hoc";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "6. Hien thi danh sach gia su";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "7. Tim kiem va them gia su";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "8. Danh gia gia su";

    // --- Ô Ðang Xuat ---
    int logoutX = 50;
    int logoutY = 23;
    SetWordColor(9);
    rectangle(logoutX, logoutY, 20, 3);
    SetWordColor(6);
    gotoXY(logoutX + 5, logoutY + 1);
    std::cout << "Dang Xuat" << std::endl;

    SetWordColor(14); // quay ve mau vang
}

void Screen_Student_one()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 21;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Ma so hoc vien:";
    gotoXY(valueX, contentY);     cout << "GS123";
    
    gotoXY(labelX, contentY + 1); cout << "Ho va ten     :";
    gotoXY(valueX, contentY + 1); cout << "Nguyen Van A";
    
    gotoXY(labelX, contentY + 2); cout << "Lop         :";
    gotoXY(valueX, contentY + 2); cout << "10";
    
    gotoXY(labelX, contentY + 3); cout << "Gioi tinh     :";
    gotoXY(valueX, contentY + 3); cout << "Nam";
    
    gotoXY(labelX, contentY + 4); cout << "Dia chi       :";
    gotoXY(valueX, contentY + 4); cout << "123 Duong ABC, Q. Hai Chau,";
    gotoXY(valueX, contentY + 5); cout << "Da Nang"; // Tách dòng 
    
    gotoXY(labelX, contentY + 6); cout << "Email         :";
    gotoXY(valueX, contentY + 6); cout << "nguyenvana@email.com";
    
    gotoXY(labelX, contentY + 7); cout << "So tien trong tai khoan :";
    gotoXY(valueX + 5, contentY + 7); cout << "500K";

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}
void Screen_Student_2(){
     system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT THONG TIN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 27;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Nhap ma so hoc vien moi:";
    gotoXY(valueX, contentY);     
    string id;
    getline(cin,id);

    
    gotoXY(labelX, contentY + 1); cout << "Nhap Ho va ten moi     :";
    gotoXY(valueX, contentY + 1); 
    string name;
    getline(cin, name);
    
    gotoXY(labelX, contentY + 2); cout << "Nhap Lop moi           :";
    gotoXY(valueX, contentY + 2); 
    string lop;
    getline(cin,lop);
    
    gotoXY(labelX, contentY + 3); cout << "Gioi tinh              :";
    gotoXY(valueX, contentY + 3); cout << "Nam";
    
    gotoXY(labelX, contentY + 4); cout << "Dia chi moi            :";
    gotoXY(valueX, contentY + 5); 
    string location;
    getline(cin,location);
    
    
    gotoXY(labelX, contentY + 6); cout << "ten dang nhap moi      :";
    gotoXY(valueX, contentY + 6); 
    string ten;
    getline(cin,ten);

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}

void Screen_Student_3() {
    system("cls");

    int x = 20;
    int y = 5;
    int width = 73;  // 71 ky tu ben trong + 2 vien
    int height = 10; 

    char Border = 205;   // ═ (Ban da cung cap)
    char LeftTee = 204;  // ╠ (Ky tu noi)
    char RightTee = 185; // ╣ (Ky tu noi)


    SetWordColor(11); // Mau xanh duong nhat
    rectangle(x, y, width, height);

    // 4. Ve cac duong chia ngang ben trong
    SetWordColor(11);
    
    // Duong chia 1 (duoi tieu de)
    gotoXY(x, y + 2);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // Duong chia 2 (truoc footer)
    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // 5. In noi dung
    // Tieu de
    SetWordColor(15); // Trang sang
    gotoXY(x + 28, y + 1); cout << "[ 3. KIEM TRA SO DU ]";

    // Nhan
    SetWordColor(7); // Trang xam
    gotoXY(x + 4, y + 4); cout << "So du hien tai cua ban:";

    SetWordColor(10); // Set mau XANH LA (Bright Green)
    string balance = "500,000 VND";
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 6); cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Nap Tien, hoac phim bat ky de quay lai)";
    int footerX = x + (width - footer.length()) / 2; // Can giua
    gotoXY(footerX, y + 8); cout << footer;
    
    // Reset mau
    SetWordColor(7); 
    _getch();
}

void FindTutorScreen() {
    system("cls");

    int x = 5;       // Toa do X
    int y = 3;       // Toa do Y
    int width = 73;  
    int height = 18; // 18 dòng

    char Border = 205;   // -
    char LeftTee = 204;  // ¦
    char RightTee = 185; // ¦


    SetWordColor(11); // Màu xanh duong cho khung
    rectangle(x, y, width, height);

    SetWordColor(11); 

    gotoXY(x, y + 2);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;


    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // Ðuong chia 3: Duoi ket qua
    gotoXY(x, y + 15);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // 4. Viet noi dung tinh
    // Tiêu de
    SetWordColor(15); // Trang sáng
    gotoXY(x + 28, y + 1); cout << "[ 7. TIM KIEM GIA SU ]";
    
    // Tiêu de các muc
    SetWordColor(14); // Vàng
    gotoXY(x + 19, y + 3); cout << "[ BO LOC (Nhan ENTER de bo qua) ]";
    gotoXY(x + 32, y + 8); cout << "[ KET QUA ]";
    gotoXY(x + 27, y + 16); cout << "[ Trang 1 / 5 ]"; // ...

    // Nhãn 
    SetWordColor(7); // Trang xám
    gotoXY(x + 3, y + 5); cout << "Tim theo Ma Mon hoc: [            ]";
    gotoXY(x + 34, y + 5); cout << "(Xem ID o muc 5)";
    gotoXY(x + 3, y + 6); cout << "Tim theo Khu vuc:    [            ]";

    // Bang ket qua
    SetWordColor(10); // Xanh lá cho header
    gotoXY(x + 3, y + 10); cout << "ID   | HO TEN                | MON DAY             | RATING";
    gotoXY(x + 3, y + 11); cout << "-------------------------------------------------------------------";
    
    // Du lieu doc tu file
    // them code ....
    SetWordColor(15); // Trang sáng
    gotoXY(x + 3, y + 12); cout << "GS003| Tran Van B            | Toan 12, Ly 11      | 4.5/5";
    gotoXY(x + 3, y + 13); cout << "GS008| Nguyen Thi A          | Hoa 10              | 4.8/5";
    gotoXY(x + 3, y + 14); cout << "..."; // them vong for chay duyet vo cho ni 

    SetWordColor(7);
    gotoXY(x + 3, y + 17); cout << "(Nhap ID, 'N' next, 'P' prev, 'Q' quit)";


    string filterMon, filterKhuVuc;
    
    SetWordColor(15); // Màu nhap
    gotoXY(x + 23, y + 5); //  ô "Ma Mon hoc"
    getline(cin, filterMon);
    
    gotoXY(x + 23, y + 6); // Toa do ô "Khu vuc"
    getline(cin, filterKhuVuc);

    // chon tiep theo
    SetWordColor(15);
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
    cout << "Da tim voi Ma Mon: '" << filterMon << "', Khu Vuc: '" << filterKhuVuc << "'" << endl;
    gotoXY(x, y + height + 2);
    cout << "Nhan phim bat ky de quay lai menu... ";
    _getch();
}

void ShowNapTienScreen_4()
{
    system("cls");
    int x = 10, y = 5;
    int width = 55; // Chiều rộng của khung
    
    // Tính toán chiều cao các phần
    int header_height = 3;  // 1 dòng viền trên, 1 dòng chữ, 1 dòng viền dưới
    int body_height = 12;   // 1 viền, 10 dòng nội dung/padding, 1 viền
    int footer_height = 3;  // 1 viền, 1 dòng chữ, 1 dòng viền dưới
    
    // Tổng chiều cao (trừ đi 2 vì các viền chia bị trùng)
    int total_height = header_height + body_height + footer_height - 2; // = 16

    char Border = 205;   
    char LeftTee = 204;  
    char RightTee = 185; 

    // 2. Vẽ khung ngoài 
    SetWordColor(14); 
    rectangle(x, y, width, total_height);

    // 3. Vẽ các đường chia ngang

    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;
    
    // Đường chia Body / Footer
    int footer_divider_y = y + header_height + body_height - 2;
    gotoXY(x, footer_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // 4. In nội dung (Màu Vàng Cam)
    SetWordColor(6); // 6 = Vàng Cam

    // In Tiêu đề (Header)
    string title = "NAP TIEN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8
    
    gotoXY(contentX, contentY_start + 1); cout << "Nhap so tien can nap (VND):";
    gotoXY(contentX, contentY_start + 3); cout << "Chon phuong thuc thanh toan:";
    gotoXY(contentX + 3, contentY_start + 4); cout << "1. Chuyen khoan ngan hang";
    gotoXY(contentX + 3, contentY_start + 5); cout << "2. Vi dien tu (Momo, ZaloPay)";
    gotoXY(contentX + 3, contentY_start + 6); cout << "3. The tin dung (Visa/Mastercard)";
    gotoXY(contentX + 3, contentY_start + 8); cout << "0. Huy bo giao dich";

    // In Chân trang (Footer)
    gotoXY(contentX, footer_divider_y + 1); cout << "Nhap lua chon cua ban (0-3):";

    long soTien;
    int luaChon;
    
    SetWordColor(15); // Trắng sáng để nhập liệu
    
    // Nhập số tiền
    gotoXY(contentX + 30, contentY_start + 1);
    cin >> soTien;
    
    // Nhập lựa chọn
    gotoXY(contentX + 30, footer_divider_y + 1);
    cin >> luaChon;
    
    // 6. Xử lý (Ví dụ)
    system("cls"); // Xóa màn hình
    SetWordColor(10); // Màu xanh lá
    gotoXY(10, 10);
    cout << "Giao dich nap " << soTien << " VND dang duoc xu ly...";
    gotoXY(10, 11);
    cout << "Ban da chon phuong thuc: " << luaChon;
    SetWordColor(7); // Reset màu
    _getch();
}
void ShowDanhSachDanhGia_6()
{
    system("cls");
    // 1. Định nghĩa layout
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    
    // Tính toán chiều cao các phần
    int header_height = 3;  
    int body_height = 12;   // Chiều cao phần thân cho các đánh giá
    int footer_height = 3;  
    
    int total_height = header_height + body_height + footer_height - 2; // = 16

    char Border = 205;   
    char LeftTee = 204;  
    char RightTee = 185; 

    // 2. Vẽ khung ngoài 
    SetWordColor(14); 
    rectangle(x, y, width, total_height);

    // 3. Vẽ các đường chia ngang
    // Đường chia Header / Body
    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;
    
    // Đường chia Body / Footer
    int footer_divider_y = y + header_height + body_height - 2;
    gotoXY(x, footer_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // 4. In nội dung (Màu Vàng Cam)
    SetWordColor(6); // 6 = Vàng Cam

    // In Tiêu đề (Header)
    string title = "DANH SACH DA DANH GIA";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8
    
    gotoXY(contentX, contentY_start + 1); cout << "+ Gia su: Tran Van B (GS002) - Mon: Lap trinh C++";
    gotoXY(contentX, contentY_start + 2); cout << "  So sao: [*****] (5/5)";
    gotoXY(contentX, contentY_start + 3); cout << "  Binh luan: \"Gia su day rat tan tinh va de hieu.\"";
    
    // Dòng kẻ ngang (dùng ký tự 196)
    gotoXY(contentX, contentY_start + 4); 
    for(int i = 0; i < width - 6; i++) { cout << char(196); }

    gotoXY(contentX, contentY_start + 5); cout << "+ Gia su: Le Thi C (GS007) - Mon: Tieng Anh";
    gotoXY(contentX, contentY_start + 6); cout << "  So sao: [**** ] (4/5)";
    gotoXY(contentX, contentY_start + 7); cout << "  Binh luan: \"Phat am chuan, nhung thinh thoang";
    gotoXY(contentX, contentY_start + 8); cout << "  den lop muon.\"";


    // In Chân trang (Footer)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footer_divider_y + 1);
    cout << footer;

    // 5. Chờ người dùng xem
    gotoXY(0, y + total_height + 2);
    SetWordColor(7);
    _getch(); // Reset màu về mặc định
}

void ShowDanhSachMonHoc_5()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    
    // Tính toán chiều cao các phần
    int header_height = 3;  
    int body_height = 11;   // 1 viền, 1 dòng tiêu đề, 1 cách, 6 môn, 1 cách, 1 viền
    int footer_height = 3;  
    
    int total_height = header_height + body_height + footer_height - 2; // = 15

    
    char Border = 205;   
    char LeftTee = 204;  
    char RightTee = 185; 

    //  Vẽ khung ngoài (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, total_height);

    //  Vẽ các đường chia ngang
    // Đường chia Header / Body
    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;
    
    // Đường chia Body / Footer
    int footer_divider_y = y + header_height + body_height - 2;
    gotoXY(x, footer_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    //  (Màu Vàng Cam)
    SetWordColor(6); // 6 = Vàng Cam

    // Tiêu đề (Header)
    string title = "DANH SACH MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8
    
    gotoXY(contentX, contentY_start + 1); cout << "Cac mon hoc hien co:";
    gotoXY(contentX + 3, contentY_start + 3); cout << "1. Toan Cao Cap A1";
    gotoXY(contentX + 3, contentY_start + 4); cout << "2. Lap trinh Co ban C/C++";
    gotoXY(contentX + 3, contentY_start + 5); cout << "3. Lap trinh Huong doi tuong";
    gotoXY(contentX + 3, contentY_start + 6); cout << "4. Cau truc Du lieu & Giai thuat";
    gotoXY(contentX + 3, contentY_start + 7); cout << "5. Tieng Anh Giao tiep";
    gotoXY(contentX + 3, contentY_start + 8); cout << "6. Vat Ly Dai cuong";

    // In Chân trang (Footer)
    string footer = "Nhan 0 de quay lai. Nhan so de xem chi tiet...";
    gotoXY(x + (width - footer.length()) / 2, footer_divider_y + 1);
    cout << footer;

    // Di chuyển con trỏ ra khỏi khung để không bị đè lên
    gotoXY(0, y + total_height + 2);
    // merge cho ni 
    SetWordColor(7);
    _getch(); // Reset màu về mặc định
}


void ScreenDanhGiaTuTor_8(){
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "Danh Gia Gia Su";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 27;  // Lề trái cho dữ liệu



    // Hien ra danh sach gia su ban theo hoc ... merge them vào đây
    gotoXY(labelX, contentY);     cout << "Nhap stt gia su do     :";
    gotoXY(valueX, contentY);     
    string id;
    getline(cin,id);

    
    gotoXY(labelX, contentY + 1); cout << "Nhap so sao (***/5)    :";
    gotoXY(valueX, contentY + 1); 
    string sao;
    getline(cin, sao);
    
    gotoXY(labelX, contentY + 2); cout << "Gia su duoc danh gia   :";
    gotoXY(valueX, contentY + 2); 
    for (int i =1; i<=sao.length();i++){
        cout<<"*";
    }
    cout<<"/5 sao";
    string lop;
    getline(cin,lop);
    
    gotoXY(labelX, contentY + 3); cout << "Binh luan ve gia su    :";
    string cmt;
    getline(cin,cmt);
    gotoXY(labelX, contentY + 4);
    cout<< cmt;
    gotoXY(labelX, contentY + 7);
    cout<<"Nhap phim bat ky de thoat";
    SetWordColor(7);
    _getch();
}



void Screen_Tutor_one()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(5); 

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 21;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Ma so gia su:";
    gotoXY(valueX, contentY);     cout << "GS123";
    
    gotoXY(labelX, contentY + 1); cout << "Ho va ten     :";
    gotoXY(valueX, contentY + 1); cout << "Nguyen Dinh Minh";
    
    gotoXY(labelX, contentY + 2); cout << "Mon day         :";
    gotoXY(valueX, contentY + 2); cout << "Toan";
    
    gotoXY(labelX, contentY + 3); cout << "Gioi tinh     :";
    gotoXY(valueX, contentY + 3); cout << "Nam";
    
    gotoXY(labelX, contentY + 4); cout << "Dia chi       :";
    gotoXY(valueX, contentY + 4); cout << "123 Duong ABC, Q. Hai Chau,";
    gotoXY(valueX, contentY + 5); cout << "Da Nang"; // Tách dòng 
    
    gotoXY(labelX, contentY + 6); cout << "Email         :";
    gotoXY(valueX, contentY + 6); cout << "nguyenvana@email.com";
    
    gotoXY(labelX, contentY + 7); cout << "So tien trong tai khoan :";
    gotoXY(valueX + 5, contentY + 7); cout << "500K";

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}

void Screen_Tutor_2(){
     system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT THONG TIN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 30;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Nhap ma so gia su moi  :";
    gotoXY(valueX, contentY);     
    string id;
    getline(cin,id);

    
    gotoXY(labelX, contentY + 1); cout << "Nhap Ho va ten moi     :";
    gotoXY(valueX, contentY + 1); 
    string name;
    getline(cin, name);
    
    gotoXY(labelX, contentY + 2); cout << "Nhap mon hoc moi       :";
    gotoXY(valueX, contentY + 2); 
    string lop;
    getline(cin,lop);
    
    gotoXY(labelX, contentY + 3); cout << "Gioi tinh              :";
    gotoXY(valueX, contentY + 3); cout << "Nam";
    
    gotoXY(labelX, contentY + 4); cout << "Dia chi moi            :";
    gotoXY(valueX, contentY + 4); 
    string location;
    getline(cin,location);
    
    
    gotoXY(labelX, contentY + 6); cout << "ten dang nhap moi      :";
    gotoXY(valueX, contentY + 6); 
    string ten;
    getline(cin,ten);

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}


void Screen_Tutor_3() {
    system("cls");

    int x = 20;
    int y = 5;
    int width = 73;  // 71 ky tu ben trong + 2 vien
    int height = 10; // Tong cong 10 dong (tu y den y+9)

    char Border = 205;   
    char LeftTee = 204; 
    char RightTee = 185; 

    // 3. Ve khung ngoai
    SetWordColor(11); // Mau xanh duong nhat
    rectangle(x, y, width, height);

    // 4. Ve cac duong chia ngang ben trong
    SetWordColor(11);
    
    // Duong chia 1 (duoi tieu de)
    gotoXY(x, y + 2);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // Duong chia 2 (truoc footer)
    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    // 5. In noi dung
    // Tieu de
    SetWordColor(15); // Trang sang
    gotoXY(x + 28, y + 1); cout << "[ 3. KIEM TRA SO DU ]";

    // Nhan
    SetWordColor(7); // Trang xam
    gotoXY(x + 4, y + 4); cout << "So du hien tai cua ban:";

    // SO DU (Mau Xanh La)
    SetWordColor(10); // Set mau XANH LA (Bright Green)
    string balance = "500,000 VND";
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 6); cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Nap Tien, hoac phim bat ky de quay lai)";
    int footerX = x + (width - footer.length()) / 2; // Can giua
    gotoXY(footerX, y + 8); cout << footer;
    
    // Reset mau
    SetWordColor(7); 
    _getch();
}


void Screen_Tutor_4()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    
    // Tính toán chiều cao 
    int header_height = 3;  
    int body_height = 11;   // 1 viền, 1 dòng tiêu đề, 1 cách, 6 môn, 1 cách, 1 viền
    int footer_height = 3;  
    
    int total_height = header_height + body_height + footer_height - 2; // = 15

    char Border = 205;   
    char LeftTee = 204;  
    char RightTee = 185; 

    SetWordColor(14); //  Vàng Sáng
    rectangle(x, y, width, total_height);

    // Đường chia Header / Body
    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;
    
    // Đường chia Body / Footer
    int footer_divider_y = y + header_height + body_height - 2;
    gotoXY(x, footer_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    //  (Màu Vàng Cam)
    SetWordColor(6); 

    // Tiêu đề (Header)
    string title = "DANH SACH MON DAY";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8
    
    gotoXY(contentX, contentY_start + 1); cout << "Cac mon hoc hien co:";
    gotoXY(contentX + 3, contentY_start + 3); cout << "1. Toan Cao Cap A1";
    gotoXY(contentX + 3, contentY_start + 4); cout << "2. Lap trinh Co ban C/C++";

    // In Chân trang (Footer)
    string footer = "Nhan 0 de quay lai. Nhan so de xem chi tiet...";
    gotoXY(x + (width - footer.length()) / 2, footer_divider_y + 1);
    cout << footer;

    // Di chuyển con trỏ ra khỏi khung để không bị đè lên
    gotoXY(0, y + total_height + 2);
    // merge thêm cho cai ni 
    SetWordColor(7);
    _getch(); // Reset màu về mặc định
}

void Screen_Tutor_5()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    
    // Tính toán chiều cao 
    int header_height = 3;  
    int body_height = 11;   // 1 viền, 1 dòng tiêu đề, 1 cách, 6 môn, 1 cách, 1 viền
    int footer_height = 3;  
    
    int total_height = header_height + body_height + footer_height - 2; // = 15

    char Border = 205;   // Ngang ═
    char LeftTee = 204;  // Ngã 3 trái ╠
    char RightTee = 185; // Ngã 3 phải ╣

    SetWordColor(14); //  Vàng Sáng
    rectangle(x, y, width, total_height);

    // Đường chia Header / Body
    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;
    
    // Đường chia Body / Footer
    int footer_divider_y = y + header_height + body_height - 2;
    gotoXY(x, footer_divider_y);
    cout << LeftTee;
    for(int i = 0; i < width - 2; i++) cout << Border;
    cout << RightTee;

    //  (Màu Vàng Cam)
    SetWordColor(6); 

    // Tiêu đề (Header)
    string title = "DANH SACH HOC SINH";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8
    
    gotoXY(contentX, contentY_start + 1); cout << " mon hoc hien dang day:";
    gotoXY(contentX + 3, contentY_start + 3); cout << "Mon Toan";
    gotoXY(contentX + 3, contentY_start + 4); cout << "1.Nguyen Van A";
    gotoXY(contentX + 3, contentY_start + 5); cout << "2. Dang Van Teo";
    gotoXY(contentX + 3, contentY_start + 6); cout << "___________________";
    gotoXY(contentX + 3, contentY_start + 7); cout << "Mon Hoa ";
    gotoXY(contentX + 3, contentY_start + 8); cout << "Pham Nhu Thao";

    // In Chân trang (Footer)
    string footer = "Nhan 0 de quay lai. Nhan so de xem chi tiet...";
    gotoXY(x + (width - footer.length()) / 2, footer_divider_y + 1);
    cout << footer;

    // Di chuyển con trỏ ra khỏi khung để không bị đè lên
    gotoXY(0, y + total_height + 2);
    // merge thêm cho cai ni 
    SetWordColor(7);
    _getch(); // Reset màu về mặc định
}

void Screen_Tutor_6(){
     system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "THEM MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 32;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Nhap ten mon hoc moi    :";
    gotoXY(valueX, contentY);     
    string mon;
    getline(cin,mon);

    
    gotoXY(labelX, contentY + 1); cout << "Nhap Hoc Phi cho mon hoc:";
    gotoXY(valueX, contentY + 1); 
    string hp;
    getline(cin, hp);
    
    gotoXY(labelX, contentY + 6); cout << "Da them mon hoc         :"<<mon;
    gotoXY(labelX, contentY +7);
    cout<<"va Hoc phi la"<<hp;

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}

void Screen_Tutor_7(){
     system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); 
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 33;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Nhap Mon hoc can chinh sua  :";
    gotoXY(valueX, contentY); 
    string subject;
    getline(cin, subject);    

    
    gotoXY(labelX, contentY + 1); cout << "Nhap hoc phi moi            :";
    gotoXY(valueX, contentY + 1); 
    string hp;
    getline(cin,hp);

    

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}

void Screen_Tutor_8(){
     system("cls");
    int x = 10, y = 5;
    int width = 60; // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣
    
    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, y + 2); cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY); cout << ML;
    for(int i = 0; i < width - 2; i++) cout << HL;
    gotoXY(x + width - 1, footerSeparatorY); cout << MR;
    
    // In nội dung (Màu Vàng Cam)
    SetWordColor(6); 

    // In tiêu đề (căn giữa)
    string title = "Xem Danh Gia cua Hoc vien";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 27;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);     cout << "Duoc danh gia 5 sao   :";
    gotoXY(valueX, contentY);     

    
    gotoXY(labelX, contentY + 1); cout << "Thay tuyet voi qua";
    gotoXY(valueX, contentY + 1); 

    

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7); 
    _getch();
}
//    while (1) {
//        system("cls"); // Xóa màn hình dua vao menu m?i
//        PrintMenu();
//        SetWordColor(14);
//        while (1) {
//            Coord click = MouseCoord();
//            cout << "Mouse clicked at: " << click.FI << ", " << click.SE << "   ";
//
//            // Kiem tra các khung
//            if (click.SE >= 19 && click.SE <= 21 && click.FI >= 46 && click.FI <= 62) {
//                // ... xu lý
//            }
//            // ... các dieu kien khác
//        }
//    }


void HandleStudentMenu() {
    ShowStudentMenu(); // 1. Ve menu sinh vien lan dau tien.

    while (true) { // 2. Bat dau vong lap su kien cho menu sinh vien.
        Coord click = MouseCoord(); // 3. Cho mot CLICK MOI tu nguoi dung.

        // Kiem tra nut [7. Tim kiem va them gia su]
        // Toa do X: (leftX) 21 -> (leftX + menuWidth - 1) 54
        // Toa do Y: (startY row 4) 18 -> (startY + 3 - 1) 20
        if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54) {
            FindTutorScreen(); // Chay chuc nang tim kiem

            // QUAN TRONG: Sau khi chuc nang ket thuc, ve lai menu
            ShowStudentMenu(); 
        }
        else if (click.FI >=21 && click.FI <=54 && click.SE >=9 && click.SE <=11 ){
            Screen_Student_one();
            // man hinh hien thi thong tin ca nhan
            ShowStudentMenu();
            // quay ve menu

        }
        else if(click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98  ){
            Screen_Student_2();
            ShowStudentMenu();

        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54){
            Screen_Student_3();
            ShowStudentMenu();
        }

        else if (click.SE >= 12 && click.SE <=14 && click.FI >=65 && click.FI <=98){
            ShowNapTienScreen_4();
            ShowStudentMenu();
        }

        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 21 && click.FI <= 54){
            ShowDanhSachMonHoc_5();
            ShowStudentMenu();

        }
        else if (click.SE >= 15 && click.SE <=17 && click.FI >=65 && click.FI <=98){
            ShowDanhSachDanhGia_6();
            ShowStudentMenu();
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >=65 && click.FI <=98){
            ScreenDanhGiaTuTor_8();
            ShowStudentMenu();
        }
        
        // nut dang xuat
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69) {
            break; // 4. Thoat khoi vong lap while(true) nay
        }

    }
    // 5. Sau khi 'break', ham nay ket thuc va quay tro lai ham main
}
void HandleTutorMenu(){
    ShowTutorMenu();
    while (true){
        Coord click = MouseCoord();
        if (click.SE >= 9 && click.SE<=11 && click.FI >=21 && click.FI <=54){
            Screen_Tutor_one();
            ShowTutorMenu();
            
        }
        else if (click.SE >= 9 && click.SE<=11 && click.FI >=65 && click.FI <=98){
            Screen_Tutor_2();
            ShowTutorMenu();

        }
        else if (click.SE >= 12 && click.SE<=14 && click.FI >=21 && click.FI <=54){
            Screen_Tutor_3();
            ShowTutorMenu();
        }
        else if (click.SE >= 12 && click.SE<=14 && click.FI >=65 && click.FI <=98){
            Screen_Tutor_4();
            ShowTutorMenu();

        }
        else if (click.SE >=15 && click.SE <=17 && click.FI >=21 && click.FI <=54){
            Screen_Tutor_5();
            ShowTutorMenu();
        }
        else if (click.SE >=15 && click.SE <=17 && click.FI >=65 && click.FI <=98){
            Screen_Tutor_6();
            ShowTutorMenu();
        }
        else if (click.SE >=18 && click.SE <=20 && click.FI >=21 && click.FI <=54){
            Screen_Tutor_7();
            ShowTutorMenu();

        }
        else if (click.SE >= 18 && click.SE <=20 && click.FI >=65 && click.FI <=98){
            Screen_Tutor_8();
            ShowTutorMenu();
        }
        else if (click.SE >=23 && click.SE <=25 && click.FI >=50 && click.FI <=69){
            break;
        }
    }

}
//	PrintMenu();
//	while(1){
//		Coord click = MouseCoord();
//		if (click.SE >= 19 && click.SE <=21 && click.FI >= 46 && click.FI <=62){
//			LoginStudent();
//			ShowStudentMenu();
//			if(click.SE >= 18 && click.SE <=20 && click.FI >= 21 && click.FI <=54){
//				FindTutorScreen();
//			}
////			if (click.SE >=)
//		}
//		else if (click.SE >= 19 && click.SE <=21 && click.FI >=70 && click.FI <=86){
//			LoginTutor();
//			ShowTutorMenu();
//		}
//		else if (click.SE >=19 && click.SE <=21 && click.FI >=94 && click.FI <=110){
//			LoginAdmin();
//		}
//	}

/**
 * @brief Hàm main 
 */
int main() {
    PrintMenu(); 

    while (1) {
        Coord click = MouseCoord(); 

        if (click.SE >= 19 && click.SE <= 21 && click.FI >= 28 && click.FI <= 45) {
            LoginStudent(); // Chay man hinh dang nhap
    
            HandleStudentMenu(); 

            system("cls");
            PrintMenu();
        }

        // Kiem tra nut [Teacher]
        // Y: 19 -> 21, X: 70 -> 86
        else if (click.SE >= 19 && click.SE <= 21 && click.FI >= 52 && click.FI <= 69) {
            LoginTutor();
            HandleTutorMenu(); 
            system("cls");
            PrintMenu(); 
        }

        // Y: 19 -> 21, X: 94 -> 110
        else if (click.SE >= 19 && click.SE <= 21 && click.FI >= 76 && click.FI <= 93) {
            LoginAdmin();
            _getch();
            system("cls");
            PrintMenu();
        }
        else if (click.SE >= 23 && click.SE <=25 && click.FI >=46 && click.FI <=70){
        	LoginUser();
            system("cls");
            PrintMenu();
		}
        else if (click.SE >=23 && click.SE <= 25 && click.FI >=76 && click.FI <=93){
            break;
        }
    }
	return 0;
}
