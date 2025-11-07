#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h> 
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


int LeftMargin = 50;
int TopMargin = 2;

Coord MouseCoord()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

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

    // --- góc du?i ---
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

void PrintTitle()
{
	SetWordColor(2);
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186;
    gotoXY(LeftMargin, TopMargin);
    cout << LeftTop;
    FOR(i, 1, 58) cout << Border;
    cout << RightTop;
    gotoXY(LeftMargin, TopMargin + 1);
    cout << UpBorder;
    FOR(i, 1, 10) cout << " ";
    SetWordColor(10);
    cout << "    CHAO MUNG DEN VOI TUTORCONNECT    ";
    FOR(i, 1, 10) cout << " ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 2);
    cout << UpBorder;
    FOR(i, 1, 3) cout << " ";
    SetWordColor(10);
    cout << "       Nen tang ho tro quan ly gia su va hoc vien ";
    FOR(i, 1, 5) cout << " ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 3);
    cout << UpBorder;
    gotoXY(LeftMargin + 59, TopMargin + 3);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 4);
    cout << UpBorder;
    SetWordColor(10);
    cout << "    Giao vien huong dan:                                  ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 5);
    cout << UpBorder;
    SetWordColor(10);
    cout << "    Nguyen Van Hieu                                       ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 6);
    cout << UpBorder;
    gotoXY(LeftMargin + 59, TopMargin + 6);
    cout << UpBorder;
    TopMargin++;
    gotoXY(LeftMargin, TopMargin + 6);
    cout << UpBorder;
    SetWordColor(10);
    cout << "    Sinh vien thuc hien:                                  ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 7);
    cout << UpBorder;
    SetWordColor(10);
    cout << "    1. Nguyen Dang Phong                                  ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 8);
    cout << UpBorder;
    SetWordColor(10);
    cout << "    2. Ngo Van Dac Tri                                    ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 9);
    cout << UpBorder;
    FOR(i,1,58) cout<<" ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 10);
    cout << LeftBottom;
    FOR(i, 1, 58) cout << Border;
    cout << RightBottom;
    TopMargin = 14;
}

void PrintMenu(){
    PrintTitle();
    int LeftMargin = 50;
    int TopMargin = 14;

    SetWordColor(14);
    gotoXY(LeftMargin, TopMargin);
    FOR(i,1,15) cout<<" ";
    cout << char(201);
    FOR(i,1,25)  cout<<char(205);
    cout<<char(187);

    LeftMargin = 50 + 15;
    gotoXY(LeftMargin, TopMargin + 1);
    cout<<char(186);
    FOR(i,1,2) cout<<" ";
    SetWordColor(6);
    cout<<"Chon vai tro cua ban? ";
    cout<<" ";
    SetWordColor(14);
    cout<<char(186);

    gotoXY(LeftMargin, TopMargin + 2);
    cout<<char(200);
    FOR(i,1,25) cout<<char(205);
    cout<<char(188);

    int boxWidth = 16;      
    int spaceBetween = 8;   
    int totalWidth = 3 * boxWidth + 2 * spaceBetween;
    int screenCenter = LeftMargin + 13; 
    int firstBoxX = screenCenter - totalWidth / 2;

    int boxY = TopMargin + 5;
    string titles[3] = {"Hoc Vien", "Teacher", "Admin"};
    // hoc vien 31, 19
    // teacher 55, 19
    // admin 79 ,19

    FOR(b,0,2) {
        int x = firstBoxX + b * (boxWidth + spaceBetween);

        gotoXY(x, boxY);
        SetWordColor(14);
        cout << char(201);
        FOR(i,1,boxWidth) cout<<char(205);
        cout<<char(187);

        gotoXY(x, boxY + 1);
        cout<<char(186);
        int padding = (boxWidth - titles[b].length()) / 2;
        FOR(i,1,padding) cout<<" ";
        SetWordColor(6);
        cout<<titles[b];
        FOR(i,1,boxWidth - padding - titles[b].length()) cout<<" ";
        SetWordColor(14);
        cout<<char(186);

        gotoXY(x, boxY + 2);
        cout<<char(200);
        FOR(i,1,boxWidth) cout<<char(205);
        cout<<char(188);
    }
    LeftMargin = LeftMargin+2;
    boxY = boxY + 1;
    gotoXY(LeftMargin, boxY+3);
    rectangle(LeftMargin, boxY+3, 25,3 );
    gotoXY(LeftMargin+2, boxY+4);
    SetWordColor(6);
    cout<<"Dang ky tai khoan moi"<<endl;

    // --- Thêm hu?ng d?n click ---
    gotoXY(LeftMargin , boxY + 7);
    SetWordColor(10);
    cout << "Click vao mot vai tro de tiep tuc...";
}


// dang nhap cho gia su 
void LoginTutor() {
	system("cls");
    int width = 25, height = 4;
    int x = LeftMargin - 2; 
    int y = TopMargin;

    // V? khung dang nh?p
    rectangle(x, y, width, height);

    // Hai dòng ch?
    string title = "DANG NHAP";
    string subtitle = "voi vai tro gia su";

    // Can gi?a ch? trong khung
    int titleX = x + (width - title.length()) / 2;
    int subtitleX = x + (width - subtitle.length()) / 2;

    SetWordColor(14); // màu vàng sáng
    gotoXY(titleX, y + 1);
    SetWordColor(6);
    cout << title;
    gotoXY(subtitleX, y + 2);
    cout << subtitle;

    // Nh?p thông tin
    string id, password;
    gotoXY(LeftMargin - 5, TopMargin + height + 2);
    SetWordColor(6);
    cout << "Nhap ID: ";
    SetWordColor(7);
    getline(cin, id);

    gotoXY(LeftMargin - 5, TopMargin + height + 3);
    SetWordColor(6);
    cout << "Nhap Password: ";
    SetWordColor(7);
    getline(cin, password);
    gotoXY(LeftMargin - 5, TopMargin + height + 4);
    cout << "Dang nhap tai khoan thanh cong\n";
    gotoXY(LeftMargin - 5, TopMargin + height + 5);
    cout << "Chon tiep chuc nang ";
}
// dang nhap hoc vien
void LoginStudent() {
	system("cls");
    int width = 25, height = 4;
    int x = LeftMargin - 2; 
    int y = TopMargin;

    // V? khung dang nh?p
    rectangle(x, y, width, height);

    // Hai dòng ch?
    string title = "DANG NHAP";
    string subtitle = "voi vai tro hoc vien";

    // Can gi?a ch? trong khung
    int titleX = x + (width - title.length()) / 2;
    int subtitleX = x + (width - subtitle.length()) / 2;

    SetWordColor(14); // màu vàng sáng
    gotoXY(titleX, y + 1);
    SetWordColor(6);
    cout << title;
    gotoXY(subtitleX, y + 2);
    cout << subtitle;

    // Nh?p thông tin
    string id, password;
    gotoXY(LeftMargin - 5, TopMargin + height + 2);
    SetWordColor(6);
    cout << "Nhap ID: ";
    SetWordColor(7);
    getline(cin, id);

    gotoXY(LeftMargin - 5, TopMargin + height + 3);
    SetWordColor(6);
    cout << "Nhap Password: ";
    SetWordColor(7);
    getline(cin, password);
    gotoXY(LeftMargin - 5, TopMargin + height + 4);
    cout << "Dang nhap tai khoan thanh cong\n";
    gotoXY(LeftMargin - 5, TopMargin + height + 5);
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

    // --- Dòng tiêu d? ---
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

    // --- Dòng chào m?ng ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    std::cout << std::string(padWelcome, ' ') << welcome;
    SetWordColor(14);
    std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cu?i ---
    std::cout << std::string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightBottom << "\n";

    // ======= Các ô ch?c nang =======
    int menuWidth = 34; // tang chi?u r?ng ô d? ch?a d? ch?
    int spaceBetween = 10; // kho?ng cách gi?a 2 c?t
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2; // canh gi?a theo khung trên
    int leftX = startMenuX;
    int rightX = leftX + menuWidth + spaceBetween;

    int startY = 9; // dòng b?t d?u phía du?i khung
    int gapY = 3;   // kho?ng cách gi?a các hàng

    // --- C?t 1 & 2 ---
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
    SetWordColor(4);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    std::cout << "7. Cap nhat thong tin mon hoc";
    gotoXY(rightX + 1, startY + 1);
    std::cout << "8. Xem danh gia";
    
    gotoXY(50,23);
    SetWordColor(14);
    rectangle(50,23,20, 3);
    SetWordColor(6);
    gotoXY(55,23+1);
    cout<<"Dang Xuat"<<endl;
    SetWordColor(7);
}

void ShowStudentMenu() {
	system("cls");
    // Ký t? khung
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // N?i dung hi?n th?
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

    // --- Dòng tiêu d? ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6); // ch? xanh duong d?m
    std::cout << std::string(padTitle, ' ') << title;
    SetWordColor(9);
    std::cout << std::string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    std::cout << std::string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << CrossRight << "\n";

    // --- Dòng chào m?ng ---
    std::cout << std::string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    std::cout << std::string(padWelcome, ' ') << welcome;
    SetWordColor(9);
    std::cout << std::string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cu?i ---
    std::cout << std::string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++) std::cout << Border;
    std::cout << RightBottom << "\n";

    // ======= Các ô ch?c nang =======
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

    // --- C?t 1 & 2 ---
    SetWordColor(9); // màu khung xanh duong sáng
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6); // ch? xanh duong d?m
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

    // --- Ô Ðang Xu?t ---
    int logoutX = 50;
    int logoutY = 23;
    SetWordColor(9);
    rectangle(logoutX, logoutY, 20, 3);
    SetWordColor(6);
    gotoXY(logoutX + 5, logoutY + 1);
    std::cout << "Dang Xuat" << std::endl;

    SetWordColor(14); // reset v? m?c d?nh
}




int main() { // Th? d?t kích thu?c console c? d?nh
    while (1) {
        system("cls"); // Xóa màn hình d? v? menu m?i
        PrintMenu();
        SetWordColor(14);
        while (1) {
            Coord click = MouseCoord();
            // In t?a d? d? debug (có th? b? sau khi ki?m tra)
            cout << "Mouse clicked at: " << click.FI << ", " << click.SE << "   ";

            // Ki?m tra các khung
            if (click.SE >= 19 && click.SE <= 21 && click.FI >= 46 && click.FI <= 62) {
                // ... x? lý
            }
            // ... các di?u ki?n khác
        }
    }
}
