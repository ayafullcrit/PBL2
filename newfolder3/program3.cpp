#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <limits>
#include "Screen.h"
#include "FileHandler.h"
#include "Program.h"
#include "Student.h"
#define FOR(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

int LeftMargin = 50;
int TopMargin = 2;
bool compareSchedulesByTime(Schedule *a, Schedule *b)
{
    // So sánh theo ngày trước
    if (a->GetDate() != b->GetDate())
    {
        return a->GetDate() < b->GetDate();
    }
    // Nếu cùng ngày thì so sánh theo giờ bắt đầu
    return a->GetStartTime() < b->GetStartTime();
}
void SortSchedulesByTime(MyVector<Schedule*> &schedules)
{
    int n = schedules.getSize();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (!compareSchedulesByTime(schedules[j], schedules[j + 1]))
            {
                // Hoán đổi hai phần tử
                Schedule* temp = schedules[j];
                schedules[j] = schedules[j + 1];
                schedules[j + 1] = temp;
            }
        }
    }
}
string getPassword(int x, int y, int maxLength)
{
    string password = "";
    char ch;
    gotoXY(x, y);
    while ((ch = _getch()) != 13)
    { // ENTER
        if (ch == 8)
        { // BACKSPACE
            if (!password.empty())
            {
                password.pop_back();
                gotoXY(x + password.length(), y);
                cout << " ";
                gotoXY(x + password.length(), y);
            }
        }
        else if (isprint(ch) && password.length() < maxLength)
        {
            password += ch;
            cout << "*";
        }
    }
    return password;
}

// menu dang nhap student
Student *LoginStudent()
{
    Program prg;
    system("cls");
    // toa do
    int x = 20;
    int y = 5;
    int width = 73; // Can chinh
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
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    gotoXY(x, y + 11);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    SetWordColor(6);
    gotoXY(x + 27, y + 2);
    cout << "DANG NHAP - HOC VIEN";

    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9);
    cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12);
    cout << "(Nhan ENTER de xac nhan)";

    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;
    // gotoXY(inputX, y + 6);
    // cout << "___________________________________";
    // gotoXY(inputX, y + 8);
    // cout << "___________________________________";

    // 5.Nhap thông tin
    string id, password;

    SetWordColor(6); // Màu trang cho nhãn
    gotoXY(x + 4, y + 6);
    cout << "Nhap ID:";
    gotoXY(x + 4, y + 8);
    cout << "Mat Khau:";
    SetWordColor(15);
    gotoXY(inputX, y + 6);
    getline(cin, id);
    // SetWordColor(6);
    // gotoXY(x + 4, y + 8);
    // cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // 6. Xu lý sau khi dang nhap
    SetWordColor(6);           // Màu xanh duong sáng
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
    Student *student = prg.LoginStudent(id, password);
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    return student;
}

void PrintTitle()
{
    SetWordColor(6);
    SetConsoleOutputCP(65001); // chuyen doi qua UCRT -8
    ShowFile("MenuTutor.txt");
    SetConsoleOutputCP(437); // chuyen ve lai ASCII
    // SetConsoleOutputCP(65001);
    // ShowFile("MenuTutor.txt");
}

// thay cho Menu
void PrintMenu()
{
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
    int box1_Width = 25;                                               // Chieu rong ben trong cua hop
    int box1_X = LeftMargin + (titleWidth - (box1_Width + 2)) / 2 + 2; // Can giua

    gotoXY(box1_X, currentTopMargin);
    cout << char(201);
    FOR(i, 1, box1_Width)
    cout << char(205);
    cout << char(187);

    gotoXY(box1_X, currentTopMargin + 1);
    cout << char(186);
    FOR(i, 1, 2)
    cout << " ";
    SetWordColor(6);
    cout << "Chon vai tro cua ban? ";
    cout << " ";
    SetWordColor(14);
    cout << char(186);

    gotoXY(box1_X, currentTopMargin + 2);
    cout << char(200);
    FOR(i, 1, box1_Width)
    cout << char(205);
    cout << char(188);

    // Ve 3 nut (Can giua so voi Title)
    int boxWidth = 16;
    int spaceBetween = 8;
    int totalWidth = 3 * boxWidth + 2 * spaceBetween; // = 64

    // Lay trung tam cua Title Box (LeftMargin + 30)
    int titleCenter = LeftMargin + (titleWidth / 2);

    int firstBoxX = titleCenter - totalWidth / 2; // Vi tri X bat dau cua nut dau tien

    int boxY = currentTopMargin + 5; // Y = 14 + 5 = 19
    string titles[3] = {"Hoc Vien", "Gia Su", "Admin"};

    FOR(b, 0, 2)
    {
        // if (b == 1)
        //     continue;
        int x = firstBoxX + b * (boxWidth + spaceBetween);

        gotoXY(x, boxY);
        SetWordColor(14);
        cout << char(201);
        FOR(i, 1, boxWidth)
        cout << char(205);
        cout << char(187);

        gotoXY(x, boxY + 1);
        cout << char(186);
        int padding = (boxWidth - titles[b].length()) / 2;
        FOR(i, 1, padding)
        cout << " ";
        SetWordColor(6);
        cout << titles[b];
        FOR(i, 1, boxWidth - padding - titles[b].length())
        cout << " ";
        SetWordColor(14);
        cout << char(186);

        gotoXY(x, boxY + 2);
        cout << char(200);
        FOR(i, 1, boxWidth)
        cout << char(205);
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
    FOR(i, 1, exitBoxWidth)
    cout << char(205);
    cout << char(187);

    gotoXY(exitBoxX, exitBoxY + 1);
    cout << char(186);
    int padding = (exitBoxWidth - exitTitle.length()) / 2;
    FOR(i, 1, padding)
    cout << " ";
    SetWordColor(6); // Mau chu
    cout << exitTitle;
    // Can chinh lai cho deu
    FOR(i, 1, exitBoxWidth - padding - exitTitle.length())
    cout << " ";
    SetWordColor(14); // Mau vien
    cout << char(186);

    gotoXY(exitBoxX, exitBoxY + 2);
    cout << char(200);
    FOR(i, 1, exitBoxWidth)
    cout << char(205);
    cout << char(188);

    // Ve text huong dan
    string clickText = "Click vao mot vai tro de tiep tuc...";
    int textX = LeftMargin + (titleWidth - clickText.length()) / 2;

    gotoXY(textX, boxY + 7); // Y = 27
    SetWordColor(10);
    cout << clickText;
}

// dang nhap cho gia su
Tutor *LoginTutor()
{
    Program prg;
    system("cls");
    // toa do
    int x = 20;
    int y = 5;
    int width = 73; // Can chinh
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
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    gotoXY(x, y + 11);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    SetWordColor(6);
    gotoXY(x + 27, y + 2);
    cout << "DANG NHAP - GIA SU";

    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9);
    cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12);
    cout << "(Nhan ENTER de xac nhan)";

    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;

    // 5.Nhap thông tin
    string id, password;

    SetWordColor(6); // Màu trang cho nhãn
    gotoXY(x + 4, y + 6);
    cout << "Nhap ID:";
    gotoXY(x + 4, y + 8);
    cout << "Mat Khau:";
    SetWordColor(15);
    gotoXY(inputX, y + 6);
    getline(cin, id);
    // SetWordColor(6);
    // gotoXY(x + 4, y + 8);
    // cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // 6. Xu lý sau khi dang nhap
    SetWordColor(6);           // Màu xanh duong sáng
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
    Tutor *tutor = prg.LoginTutor(id, password);
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    return tutor;
}

void ShowTutorMenu(Tutor *tutor)
{
    system("cls");
    // Ký t? khung
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // N?i dung hi?n th?
    string title = "MENU GIA SU";
    string welcome = "Chao mung gia su " + tutor->GetName() + " (ID: " + tutor->GetID() + ")";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    SetWordColor(14);

    // --- Dòng trên cùng ---
    cout << string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    cout << string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6);
    cout << string(padTitle, ' ') << title;
    SetWordColor(14);
    cout << string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    cout << string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << CrossRight << "\n";

    // --- Dòng chào mung ---
    cout << string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    cout << string(padWelcome, ' ') << welcome;
    SetWordColor(14);
    cout << string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    cout << string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightBottom << "\n";

    // Các ô chuc nang
    int menuWidth = 34;    // tang chieu rong cac ô
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
    cout << "1. Hien thi thong tin ca nhan";
    gotoXY(rightX + 1, startY + 1);
    cout << "2. Cap nhat thong tin ca nhan";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    cout << "4. Hien thi danh sach mon hoc";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "5. Them mon hoc moi";
    gotoXY(rightX + 1, startY + 1);
    cout << "6. Cap nhat thong tin mon hoc";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "7. Xac nhan lich day";
    gotoXY(rightX + 1, startY + 1);
    cout << "8. Xem lich day";

    gotoXY(50, 23);
    SetWordColor(4);
    rectangle(50, 23, 20, 3);
    SetWordColor(6);
    gotoXY(55, 23 + 1);
    cout << "Dang Xuat" << endl;
    SetWordColor(7);
}

void ShowStudentMenu(Student *student)
{
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // Noi dung hien thi
    string title = "MENU HOC VIEN";
    string welcome = "Chao mung ban " + student->GetName() + " (ID: " + student->GetID() + ")";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    // Màu khung
    SetWordColor(9); // xanh duong sáng

    // --- Dòng trên cùng ---
    cout << string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    cout << string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6); // vang
    cout << string(padTitle, ' ') << title;
    SetWordColor(9);
    cout << string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    cout << string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << CrossRight << "\n";

    // --- Dòng chào mung ---
    cout << string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    cout << string(padWelcome, ' ') << welcome;
    SetWordColor(9);
    cout << string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    cout << string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightBottom << "\n";

    // ======= Các ô chuc nang =======
    int menuWidth = 34;
    int spaceBetween = 10;
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2;
    int leftX = startMenuX;                        // 21 khung trai
    int rightX = leftX + menuWidth + spaceBetween; // 65 khung bên phai

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
    cout << "1. Hien thi thong tin ca nhan";
    gotoXY(rightX + 1, startY + 1);
    cout << "2. Dang ky buoi hoc moi";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    cout << "4. Nap tien";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "5. Hien thi danh sach gia su";
    gotoXY(rightX + 1, startY + 1);
    cout << "6. Xem lich hoc";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "7. Tim kiem va them gia su";
    gotoXY(rightX + 1, startY + 1);
    cout << "8. Danh gia gia su";

    // --- Ô Ðang Xuat ---
    int logoutX = 50;
    int logoutY = 23;
    SetWordColor(9);
    rectangle(logoutX, logoutY, 20, 3);
    SetWordColor(6);
    gotoXY(logoutX + 5, logoutY + 1);
    cout << "Dang Xuat" << endl;

    SetWordColor(14); // quay ve mau vang
}
void Screen_Student_2(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT THONG TIN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 5; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 28;  // Lề trái cho dữ liệu
    gotoXY(labelX, contentY - 1);
    cout << "(Nhap N/n o vi tri ban muon bo qua)";
    gotoXY(labelX, contentY);
    cout << "Nhap ma so hoc vien moi: ";
    gotoXY(valueX, contentY);
    string id;
    getline(cin, id);
    if (id != "N" && id != "n" && !id.empty())
        student->SetID(id);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap Ho va ten moi     : ";
    gotoXY(valueX, contentY + 1);
    string name;
    getline(cin, name);
    if (name != "N" && name != "n" && !name.empty())
        student->SetUserName(name);

    gotoXY(labelX, contentY + 2);
    cout << "Nhap Lop moi           : ";
    gotoXY(valueX, contentY + 2);
    string lop;
    getline(cin, lop);
    bool isvalid = 1;
    if (lop != "N" && lop != "n")
    {
        for (int i = 0; i < lop.size(); i++)
            if (!isdigit(lop[i]))
            {
                isvalid = 0;
                break;
            }
        int IntGrd = -1;
        if (!lop.empty())
            IntGrd = stoi(lop);

        if (IntGrd < 1 or IntGrd > 12)
            isvalid = 0;

        if (!isvalid)
        {
            SetWordColor(4);
            gotoXY(labelX, contentY + 3);
            cout << "Lop khong hop le!";
            gotoXY(labelX, contentY + 4);
            cout << "An phim bat ki de tiep tuc!";
            _getch();
            return;
        }
        student->SetGradeLevel(IntGrd);
    }

    gotoXY(labelX, contentY + 3);
    cout << "Dia chi moi            : ";
    gotoXY(valueX, contentY + 3);
    string location;
    getline(cin, location);
    if (location != "N" && location != "n")
        student->SetLocation(location);

    gotoXY(labelX, contentY + 4);
    cout << "Nhap mat khau moi      : ";
    gotoXY(valueX, contentY + 4);
    string password;
    getline(cin, password);
    if (password != "N" && password != "n" && !password.empty())
        student->SetPassword(password);
    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    FileHandler::SaveStudents();
    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void Screen_Student_one(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;       // Chiều rộng của khung
    int bodyHeight = 10;  // Chiều cao của phần thân
    int footerHeight = 4; // Chiều cao của phần chân trang
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = footerHeight + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    student->DisplayInfo();
    // In footer (căn giữa)
    string footer = "Nhan U de cap nhat thong tin... ";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 2);
    cout << "Nhan phim bat ky de quay lai...";

    char ch = getch();
    if (ch == 'U' || ch == 'u')
    {
        Screen_Student_2(student);
    }

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void ShowRutTienScreen(Tutor *tutor)
{
    system("cls");
    int x = 10, y = 5;
    int width = 55; // Chiều rộng của khung

    // Tính toán chiều cao các phần
    int header_height = 3; // 1 dòng viền trên, 1 dòng chữ, 1 dòng viền dưới
    int body_height = 22;  // 1 viền, 10 dòng nội dung/padding, 1 viền
                           // int footer_height = 3; // 1 viền, 1 dòng chữ, 1 dòng viền dưới

    // Tổng chiều cao (trừ đi 2 vì các viền chia bị trùng)
    int total_height = header_height + body_height - 1; //+ footer_height - 2; // = 16

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
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 4. In nội dung (Màu Vàng Cam)
    SetWordColor(6); // 6 = Vàng Cam

    // In Tiêu đề (Header)
    string title = "RUT TIEN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8

    gotoXY(contentX, contentY_start + 1);
    cout << "Nhap so tien can rut (VND):";

    gotoXY(contentX, contentY_start + 3);
    cout << "Chon phuong thuc thanh toan:";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 4, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 5);
    cout << "1. Chuyen khoan ngan hang         ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 7, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 8);
    cout << "2. Vi dien tu (Momo, ZaloPay)     ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 10, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 11);
    cout << "3. The tin dung (Visa/Mastercard) ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 13, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 14);
    cout << "0. Huy bo giao dich               ";

    int soTien;
    int luaChon;

    SetWordColor(15); // Trắng sáng để nhập liệu

    // Nhập số tiền
    gotoXY(contentX + 30, contentY_start + 1);
    if (!IntInput(soTien))
    {
        gotoXY(contentX, contentY_start + 17);
        SetWordColor(4);
        cout << "So tien da nhap khong hop le!";
        gotoXY(contentX, contentY_start + 18);
        SetWordColor(6);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    string PhuongThuc[] = {"tai khoan ngan hang", "vi dien tu", "the tin dung"};
    string final;
    gotoXY(0, 0);
    while (1)
    {
        Coord d = MouseCoord();
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 12 && d.SE <= 14)
        {
            final = PhuongThuc[0];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 15 && d.SE <= 17)
        {
            final = PhuongThuc[1];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 18 && d.SE <= 20)
        {
            final = PhuongThuc[2];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 21 && d.SE <= 23)
        {
            return;
        }
    }
    if (soTien > tutor->GetBalance())
    {
        gotoXY(contentX, contentY_start + 17);
        SetWordColor(4);
        cout << "So tien trong tai khoan khong du de rut!";
    }
    else
    {
        SetWordColor(10);
        gotoXY(contentX, contentY_start + 17);
        cout << "Da rut thanh cong ";
        SetWordColor(15);
        cout << soTien;
        SetWordColor(10);
        cout << " bang " << final << "!";
        gotoXY(contentX, contentY_start + 18);
        cout << "So du moi: ";
        SetWordColor(15);
        cout << tutor->GetBalance() - soTien;
        tutor->Withdraw(soTien);
    }
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 19);
    cout << "An phim bat ki de tiep tuc!";
    SetWordColor(15);
    _getch();
}
void ShowNapTienScreen_4(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 55; // Chiều rộng của khung

    // Tính toán chiều cao các phần
    int header_height = 3; // 1 dòng viền trên, 1 dòng chữ, 1 dòng viền dưới
    int body_height = 22;  // 1 viền, 10 dòng nội dung/padding, 1 viền
                           // int footer_height = 3; // 1 viền, 1 dòng chữ, 1 dòng viền dưới

    // Tổng chiều cao (trừ đi 2 vì các viền chia bị trùng)
    int total_height = header_height + body_height - 1; //+ footer_height - 2; // = 16

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
    for (int i = 0; i < width - 2; i++)
        cout << Border;
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

    gotoXY(contentX, contentY_start + 1);
    cout << "Nhap so tien can nap (VND):";

    gotoXY(contentX, contentY_start + 3);
    cout << "Chon phuong thuc thanh toan:";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 4, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 5);
    cout << "1. Chuyen khoan ngan hang         ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 7, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 8);
    cout << "2. Vi dien tu (Momo, ZaloPay)     ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 10, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 11);
    cout << "3. The tin dung (Visa/Mastercard) ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 13, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 14);
    cout << "0. Huy bo giao dich               ";

    int soTien;
    int luaChon;

    SetWordColor(15); // Trắng sáng để nhập liệu

    // Nhập số tiền
    gotoXY(contentX + 30, contentY_start + 1);
    if (!IntInput(soTien))
    {
        gotoXY(contentX, contentY_start + 17);
        SetWordColor(4);
        cout << "So tien da nhap khong hop le!";
        gotoXY(contentX, contentY_start + 18);
        SetWordColor(6);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    string PhuongThuc[] = {"tai khoan ngan hang", "vi dien tu", "the tin dung"};
    string final;
    gotoXY(0, 0);
    while (1)
    {
        Coord d = MouseCoord();
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 12 && d.SE <= 14)
        {
            final = PhuongThuc[0];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 15 && d.SE <= 17)
        {
            final = PhuongThuc[1];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 18 && d.SE <= 20)
        {
            final = PhuongThuc[2];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 21 && d.SE <= 23)
        {
            return;
        }
    }
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 17);
    cout << "Da nap thanh cong ";
    SetWordColor(15);
    cout << soTien;
    SetWordColor(10);
    cout << " bang " << final << "!";
    gotoXY(contentX, contentY_start + 18);
    cout << "So du moi: ";
    SetWordColor(15);
    cout << student->GetBalance() + soTien;
    student->Deposit(soTien);
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 19);
    cout << "An phim bat ki de tiep tuc!";
    SetWordColor(15);
    _getch();
}
void Screen_Student_3(Student *student)
{
    system("cls");

    int x = 20;
    int y = 5;
    int width = 73; // 71 ky tu ben trong + 2 vien
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
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // Duong chia 2 (truoc footer)
    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 5. In noi dung
    // Tieu de
    SetWordColor(15); // Trang sang
    gotoXY(x + 28, y + 1);
    cout << "[ 3. KIEM TRA SO DU ]";

    // Nhan
    SetWordColor(7); // Trang xam
    gotoXY(x + 4, y + 4);
    cout << "So du hien tai cua ban:";

    SetWordColor(10); // Set mau XANH LA (Bright Green)
    string balance = to_string(student->GetBalance());
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 5);
    cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Nap Tien, hoac phim bat ky de quay lai)";
    int footerX = x + (width - footer.length()) / 2; // Can giua
    gotoXY(footerX, y + 8);
    cout << footer;

    // Reset mau
    SetWordColor(7);
    while (true)
    {
        char key = getch();
        if (key == 'N' || key == 'n')
        {
            ShowNapTienScreen_4(student);
            break;
        }
        else
            break;
    }
}

void FindTutorScreen()
{
    system("cls");

    int x = 5; // Toa do X
    int y = 3; // Toa do Y
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
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // Ðuong chia 3: Duoi ket qua
    gotoXY(x, y + 15);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 4. Viet noi dung tinh
    // Tiêu de
    SetWordColor(15); // Trang sáng
    gotoXY(x + 28, y + 1);
    cout << "[ 7. TIM KIEM GIA SU ]";

    // Tiêu de các muc
    SetWordColor(14); // Vàng
    gotoXY(x + 19, y + 3);
    cout << "[ BO LOC (Nhan ENTER de bo qua) ]";
    gotoXY(x + 32, y + 8);
    cout << "[ KET QUA ]";
    gotoXY(x + 27, y + 16);
    cout << "[ Trang 1 / 5 ]"; // ...

    // Nhãn
    SetWordColor(7); // Trang xám
    gotoXY(x + 3, y + 5);
    cout << "Tim theo Ma Mon hoc: [            ]";
    gotoXY(x + 34, y + 5);
    cout << "(Xem ID o muc 5)";
    gotoXY(x + 3, y + 6);
    cout << "Tim theo Khu vuc:    [            ]";

    // Bang ket qua
    SetWordColor(10); // Xanh lá cho header
    gotoXY(x + 3, y + 10);
    cout << "ID   | HO TEN                | MON DAY             | RATING";
    gotoXY(x + 3, y + 11);
    cout << "-------------------------------------------------------------------";

    // Du lieu doc tu file
    // them code ....
    SetWordColor(15); // Trang sáng
    gotoXY(x + 3, y + 12);
    cout << "GS003| Tran Van B            | Toan 12, Ly 11      | 4.5/5";
    gotoXY(x + 3, y + 13);
    cout << "GS008| Nguyen Thi A          | Hoa 10              | 4.8/5";
    gotoXY(x + 3, y + 14);
    cout << "..."; // them vong for chay duyet vo cho ni

    SetWordColor(7);
    gotoXY(x + 3, y + 17);
    cout << "(Nhap ID, 'N' next, 'P' prev, 'Q' quit)";

    string filterMon, filterKhuVuc;

    SetWordColor(15);      // Màu nhap
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
void DisplayScheduleCard(Schedule *schedule, int x, int y, int width)
{
    // Vẽ khung card
    SetWordColor(7);
    rectangle(x, y, width, 5);

    // Màu theo trạng thái
    int color;
    if (schedule->GetStatus() == "completed")
        color = 14; // Vàng
    else if (schedule->GetStatus() == "cancelled")
        color = 12; // Đỏ
    else
        color = 10; // Xanh lá

    // Thông tin chính
    SetWordColor(color);
    gotoXY(x + 2, y + 1);
    cout << schedule->GetDate() << " | " << schedule->GetStartTime() << " - " << schedule->GetEndTime();

    // Môn học và gia sư
    gotoXY(x + 2, y + 2);
    if (schedule->GetSubjectRecord() && schedule->GetSubjectRecord()->GetSubject())
    {
        cout << "Mon: " << schedule->GetSubjectRecord()->GetSubject()->GetName();
    }

    gotoXY(x + width - 25, y + 2);
    if (schedule->GetTutor())
    {
        cout << "Gia su: " << schedule->GetTutor()->GetName();
    }

    // Địa điểm và trạng thái
    gotoXY(x + 2, y + 3);
    cout << "Dia diem: " << schedule->GetLocation();

    gotoXY(x + width - 20, y + 3);
    cout << schedule->GetStatus();

    // Điểm danh và thời lượng
    SetWordColor(7);
    gotoXY(x + 2, y + 4);
    cout << "Diem danh: " << (schedule->GetAttendance() ? " Da diem danh" : " Chua diem danh");

    gotoXY(x + width - 20, y + 4);
    cout << schedule->GetDuration() << " phut";
}

void ShowLichHoc_6(Student *student)
{
    system("cls");

    int x = 5, y = 3;
    int width = 110;
    int total_height = 25;

    // Vẽ khung chính
    SetWordColor(11); // Màu xanh dương
    rectangle(x, y, width, total_height);

    // Tiêu đề chính
    SetWordColor(14); // Màu vàng
    string title = "LICH HOC TUAN CUA " + student->GetName();
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // Kiểm tra nếu không có lịch học
    if (student->GetSchedules().getSize() == 0)
    {
        SetWordColor(12); // Màu đỏ
        gotoXY(x + (width - 20) / 2, y + 5);
        cout << "Chua co lich hoc nao!";
        gotoXY(x + (width - 30) / 2, y + 7);
        cout << "Nhan phim bat ky de quay lai...";
        SetWordColor(7);
        _getch();
        return;
    }

    // Phân loại lịch học
    MyVector<Schedule *> upcomingSchedules;
    MyVector<Schedule *> completedSchedules;
    MyVector<Schedule *> cancelledSchedules;
    SortSchedulesByTime(upcomingSchedules);
    SortSchedulesByTime(completedSchedules);
    SortSchedulesByTime(cancelledSchedules);
    for (int i = 0; i < student->GetSchedules().getSize(); ++i)
    {
        Schedule *schedule = student->GetSchedules()[i];
        if (schedule->GetStatus() == "completed")
        {
            completedSchedules.push_back(schedule);
        }
        else if (schedule->GetStatus() == "cancelled")
        {
            cancelledSchedules.push_back(schedule);
        }
        else
        {
            upcomingSchedules.push_back(schedule);
        }
    }

    int currentY = y + 3;

    // Hiển thị lịch sắp tới
    if (upcomingSchedules.getSize() > 0)
    {
        SetWordColor(10); // Màu xanh lá
        gotoXY(x + 3, currentY);
        cout << "=== LICH HOC SAP TOI ===";
        currentY++;

        for (int i = 0; i < upcomingSchedules.getSize(); ++i)
        {
            DisplayScheduleCard(upcomingSchedules[i], x + 3, currentY, width - 6);
            currentY += 6; // Mỗi card cao 6 dòng
            if (currentY > y + total_height - 3)
                break;
        }
        currentY += 2;
    }

    // Hiển thị lịch đã hoàn thành
    if (completedSchedules.getSize() > 0)
    {
        SetWordColor(14); // Màu vàng
        gotoXY(x + 3, currentY);
        cout << "=== LICH HOC DA HOAN THANH ===";
        currentY++;

        for (int i = 0; i < completedSchedules.getSize(); ++i)
        {
            DisplayScheduleCard(completedSchedules[i], x + 3, currentY, width - 6);
            currentY += 6;
            if (currentY > y + total_height - 3)
                break;
        }
        currentY += 2;
    }

    // Hiển thị lịch đã hủy
    if (cancelledSchedules.getSize() > 0)
    {
        SetWordColor(12); // Màu đỏ
        gotoXY(x + 3, currentY);
        cout << "=== LICH HOC DA HUY ===";
        currentY++;

        for (int i = 0; i < cancelledSchedules.getSize(); ++i)
        {
            DisplayScheduleCard(cancelledSchedules[i], x + 3, currentY, width - 6);
            currentY += 6;
            if (currentY > y + total_height - 3)
                break;
        }
    }

    // Thống kê
    SetWordColor(15); // Màu trắng sáng
    gotoXY(x + 3, y + total_height - 2);
    cout << "Tong so: " << student->GetSchedules().getSize() << " lich hoc";
    gotoXY(x + width - 25, y + total_height - 2);
    cout << "Sap toi: " << upcomingSchedules.getSize();

    gotoXY(x + 3, y + total_height - 1);
    cout << "Hoan thanh: " << completedSchedules.getSize();
    gotoXY(x + width - 25, y + total_height - 1);
    cout << "Da huy: " << cancelledSchedules.getSize();

    // Hướng dẫn
    SetWordColor(8); // Màu xám
    gotoXY(x + (width - 40) / 2, y + total_height + 1);
    cout << "Nhan phim bat ky de quay lai...";

    SetWordColor(7);
    _getch();
}

void ShowDanhSachMonHoc_5(Student *student)
{
    MyVector<Subject *> sbjlist = student->GetSubjectList();
    MyVector<Tutor *> ttlist = student->GetTutorList();
    // FOR(i, 1, 9)
    // sbjlist.push_back(new Subject("Van" + to_string(i)));
    // FOR(i, 1, 9)
    // ttlist.push_back(new Tutor("0001", "Gia su " + to_string(i)));
    int currentPage = 0;
    int itemsPerPage = 10; // Số môn học mỗi trang
    int totalItems = sbjlist.getSize();
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
    while (1)
    {
        system("cls");
        int x = 10, y = 5;
        int width = 70; // Tăng chiều rộng để chứa 2 cột

        // Tính toán chiều cao các phần
        int header_height = 3;
        int body_height = 18;
        int footer_height = 3;

        int total_height = header_height + body_height + footer_height - 2;

        char Border = 205;
        char LeftTee = 204;
        char RightTee = 185;

        // Vẽ khung ngoài
        SetWordColor(14);
        rectangle(x, y, width, total_height);

        // Vẽ các đường chia ngang
        int header_divider_y = y + header_height - 1;
        gotoXY(x, header_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        int footer_divider_y = y + header_height + body_height - 2;
        gotoXY(x, footer_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        // Tiêu đề
        SetWordColor(6);
        string title = "DANH SACH MON HOC - Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Nội dung - 2 cột
        int contentX = x + 3;
        int contentY_start = y + header_height;

        // Tiêu đề các cột
        gotoXY(contentX + 2, contentY_start + 1);
        cout << "TEN MON HOC";
        gotoXY(contentX + 35, contentY_start + 1);
        cout << "GIANG VIEN";

        // Đường kẻ ngang dưới tiêu đề
        gotoXY(contentX, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";
        gotoXY(contentX + 35, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";

        // Hiển thị danh sách môn học
        int startIndex = currentPage * itemsPerPage;
        int endIndex = min(startIndex + itemsPerPage, totalItems);
        int currentY = contentY_start + 4;

        for (int i = startIndex; i < endIndex; i++)
        {
            // Cột tên môn học
            gotoXY(contentX + 2, currentY);
            cout << (i + 1) << ". " << sbjlist[i]->GetName();

            // Cột tên giảng viên
            gotoXY(contentX + 35, currentY);
            cout << ttlist[i]->GetName();

            currentY++;
        }

        // Thông tin phân trang
        string pageInfo = "Hien thi " + to_string(startIndex + 1) + "-" + to_string(endIndex) +
                          " tren tong " + to_string(totalItems) + " mon hoc";
        gotoXY(x + (width - pageInfo.length()) / 2, currentY + 1);
        cout << pageInfo;

        // Hướng dẫn điều hướng
        SetWordColor(6);
        string footer;
        if (totalPages > 1)
        {
            footer = "Quay lai        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "                            Quay lai";
        }
        gotoXY(x + 1, footer_divider_y + 1);
        cout << footer;

        // Di chuyển con trỏ ra khỏi khung
        gotoXY(0, y + total_height + 2);

        SetWordColor(7);
        Coord d = MouseCoord();
        if (totalPages > 1)
        {
            if (d.SE != 25)
                continue;
            if (d.FI >= 27 && d.SE <= 40)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 47 && d.FI <= 58)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
            }
            if (d.FI >= 11 && d.FI <= 18)
                break;
        }
        else
        {
            if (d.SE != 25)
                continue;
            if (d.FI <= 48 && d.FI >= 40)
            {
                break;
            }
        }
    }
}
bool ShowTutorAndSubjectSelection(Student *student, Tutor *&selectedTutor, Subject *&selectedSubject)
{
    system("cls");

    int x = 10, y = 3;
    int width = 80;
    int height = 20;

    // Vẽ khung chính
    SetWordColor(14);
    rectangle(x, y, width, height);

    // Tiêu đề
    SetWordColor(14);
    string title = "CHON GIA SU VA MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    int currentY = y + 3;

    // Hiển thị danh sách gia sư
    SetWordColor(11);
    gotoXY(x + 3, currentY);
    cout << "DANH SACH GIA SU:                   MON HOC:";
    currentY++;

    MyVector<Tutor *> &tutorList = student->GetTutorList();
    MyVector<Subject *> &sbjList = student->GetSubjectList();
    if (tutorList.getSize() == 0)
    {
        SetWordColor(12);
        gotoXY(x + 5, currentY);
        cout << "Ban chua co gia su nao! Vui long them gia su truoc.";
        currentY += 2;

        SetWordColor(8);
        gotoXY(x + (width - 30) / 2, y + height - 1);
        cout << "Nhan phim bat ky de quay lai...";

        SetWordColor(7);
        return false;
    }

    // Hiển thị danh sách gia sư
    for (int i = 0; i < tutorList.getSize(); i++)
    {
        SetWordColor(7);
        gotoXY(x + 5, currentY);
        cout << i + 1 << ". " << tutorList[i]->GetName();
        FOR(j, 0, 30 - tutorList[i]->GetName().length())
        cout << " ";
        cout << sbjList[i]->GetName();
        currentY++;
    }

    // Chọn gia sư
    currentY++;
    SetWordColor(10);
    gotoXY(x + 3, currentY);
    cout << "Chon gia su (nhap so thu tu 1-" << tutorList.getSize() << "): ";

    SetWordColor(15);
    int tutorIndex;
    if (!IntInput(tutorIndex))
        return false;

    if (tutorIndex < 1 || tutorIndex > tutorList.getSize())
    {
        cout << "So thu tu khong hop le!";
        return false;
    }

    selectedTutor = tutorList[tutorIndex - 1];
    selectedSubject = sbjList[tutorIndex - 1];
    return true;
}
void ShowSuccessMessage(Schedule *schedule)
{
    system("cls");

    int x = 15, y = 8;
    int width = 50;
    int height = 8;

    SetWordColor(10);
    rectangle(x, y, width, height);

    SetWordColor(10);
    gotoXY(x + (width - 20) / 2, y + 1);
    cout << "✅ TAO LICH THANH CONG";

    SetWordColor(7);
    gotoXY(x + 3, y + 3);
    cout << "Ma lich: " << schedule->GetID();

    gotoXY(x + 3, y + 4);
    cout << "Ngay: " << schedule->GetDate();

    gotoXY(x + 3, y + 5);
    cout << "Gio: " << schedule->GetStartTime() << " - " << schedule->GetEndTime();

    SetWordColor(12);
    gotoXY(x + (width - 40) / 2, y + 6);
    cout << "⚠  Lich hoc dang cho gia su xac nhan";

    SetWordColor(8);
    gotoXY(x + (width - 30) / 2, y + height - 1);
    cout << "Nhan phim bat ky de quay lai...";

    SetWordColor(7);
    _getch();
}
bool IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool DateValidate(string date)
{
    // Kiểm tra độ dài chuỗi
    if (date.length() != 10)
        return false;

    // Kiểm tra định dạng dd-mm-yyyy
    if (date[2] != '-' || date[5] != '-')
        return false;

    // Tách và chuyển đổi các phần
    for (int i = 0; i < date.length(); i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Kiểm tra phạm vi năm
    if (year < 1 || year > 9999)
        return false;

    // Kiểm tra phạm vi tháng
    if (month < 1 || month > 12)
        return false;

    // Kiểm tra số ngày trong tháng
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Điều chỉnh ngày tháng 2 cho năm nhuận
    if (month == 2 && IsLeapYear(year))
        daysInMonth[1] = 29;

    // Kiểm tra ngày hợp lệ
    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    return true;
}

bool TimeValidate(string time)
{
    regex time_pattern("^([01][0-9]|2[0-3]):([0-5][0-9])$");
    return regex_match(time, time_pattern);
}
void ShowScheduleCreationForm(Student *student, Tutor *tutor, Subject *subjectRecord)
{
    system("cls");

    int x = 10, y = 3;
    int width = 70;
    int height = 22;

    // Vẽ khung chính
    SetWordColor(14);
    rectangle(x, y, width, height);

    // Tiêu đề
    SetWordColor(14);
    string title = "TAO LICH HOC MOI";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // Thông tin đã chọn
    SetWordColor(11);
    gotoXY(x + 3, y + 3);
    cout << "Thong tin da chon:";

    SetWordColor(7);
    gotoXY(x + 5, y + 4);
    cout << "Gia su: " << tutor->GetName();

    gotoXY(x + 5, y + 5);
    cout << "Mon hoc: " << subjectRecord->GetName();

    // Form nhập liệu
    int currentY = y + 7;
    string date, startTime, endTime, location, notes;
    SetWordColor(10);
    gotoXY(x + 3, currentY);
    cout << "Nhap ngay hoc (DD-MM-YYYY): ";
    SetWordColor(15);
    cin >> date;
    if (!DateValidate(date))
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Ngay khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }

    SetWordColor(10);
    gotoXY(x + 3, currentY + 1);
    cout << "Nhap gio bat dau (HH:MM): ";
    SetWordColor(15);
    cin >> startTime;
    if (!TimeValidate(startTime))
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Gio bat dau khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }
    SetWordColor(10);
    gotoXY(x + 3, currentY + 2);
    cout << "Nhap gio ket thuc (HH:MM): ";
    SetWordColor(15);
    cin >> endTime;
    bool validEndTime = TimeValidate(endTime) && (endTime > startTime);
    if (!validEndTime)
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Gio ket thuc khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }

    cin.ignore();
    SetWordColor(10);
    gotoXY(x + 3, currentY + 3);
    cout << "Nhap dia diem hoc: ";
    SetWordColor(15);
    getline(cin, location);

    SetWordColor(10);
    gotoXY(x + 3, currentY + 4);
    cout << "Nhap ghi chu (neu co): ";
    SetWordColor(15);
    getline(cin, notes);

    Program prg;
    bool isExist = false;
    string scheduleID = "";
    srand(time(NULL));
    do
    {
        // Tạo lịch học
        isExist = false;
        scheduleID = "";
        FOR(i, 1, 6)
        scheduleID += to_string(rand() % 10);
        FOR(i, 0, prg.getScheduleList().getSize() - 1)
        {
            if (prg.getScheduleList()[i]->GetID() == scheduleID)
            {
                isExist = true;
                break;
            }
        }
    } while (isExist);
    SubjectRecord *sr = new SubjectRecord(subjectRecord);
    Schedule *newSchedule = new Schedule(scheduleID, date, startTime, endTime, "pending", sr, student, tutor, location, notes);
    // // Kiểm tra trùng lịch
    if (prg.CheckScheduleConflict(*newSchedule))
    {
        delete newSchedule;
        gotoXY(x + 3, currentY + 10);
        cout << "Lich hoc bi trung! Vui long chon thoi gian khac.";
        _getch();
        return;
    }
    // // Lưu lịch học
    prg.getScheduleList().push_back(newSchedule);
    student->AddSchedule(newSchedule);
    tutor->AddSchedule(newSchedule);
    FileHandler::AppendScheduleToFile(newSchedule);
    cout << "Them lich hoc thanh cong! Nhan phim bat ky de tiep tuc...";
    _getch();
}

void CreateSchedule(Student *student)
{
    Tutor *tutor = nullptr;
    Subject *subject = nullptr;
    ShowTutorAndSubjectSelection(student, tutor, subject);
    if (!student || !tutor || !subject)
    {
        // Hiển thị thông báo lỗi
        system("cls");
        int x = 20, y = 10;
        int width = 40, height = 5;

        SetWordColor(12);
        rectangle(x, y, width, height);

        gotoXY(x + (width - 20) / 2, y + 2);
        cout << "THONG TIN KHONG HOP LE!";

        gotoXY(x + (width - 30) / 2, y + 3);
        cout << "Nhan phim bat ky de quay lai...";

        SetWordColor(7);
        _getch();
        return;
    }
    // Hiển thị giao diện nhập thông tin lịch học
    ShowScheduleCreationForm(student, tutor, subject);
}

void ScreenDanhGiaTuTor_8()
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

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
    gotoXY(labelX, contentY);
    cout << "Nhap stt gia su do     :";
    gotoXY(valueX, contentY);
    string id;
    getline(cin, id);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap so sao (***/5)    :";
    gotoXY(valueX, contentY + 1);
    string sao;
    getline(cin, sao);

    gotoXY(labelX, contentY + 2);
    cout << "Gia su duoc danh gia   :";
    gotoXY(valueX, contentY + 2);
    for (int i = 1; i <= sao.length(); i++)
    {
        cout << "*";
    }
    cout << "/5 sao";
    string lop;
    getline(cin, lop);

    gotoXY(labelX, contentY + 3);
    cout << "Binh luan ve gia su    :";
    string cmt;
    getline(cin, cmt);
    gotoXY(labelX, contentY + 4);
    cout << cmt;
    gotoXY(labelX, contentY + 7);
    cout << "Nhap phim bat ky de thoat";
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_one(Tutor *tutor)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(5);

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    tutor->DisplayInfo();

    // In footer (căn giữa)
    SetWordColor(10);
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void Screen_Tutor_2(Tutor *tutor)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT THONG TIN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 5; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 28;  // Lề trái cho dữ liệu
    gotoXY(labelX, contentY - 1);
    cout << "(Nhap N/n o vi tri ban muon bo qua)";
    gotoXY(labelX, contentY);
    cout << "Nhap ma so gia su moi:   ";
    gotoXY(valueX, contentY);
    string id;
    getline(cin, id);
    if (id != "N" && id != "n" && !id.empty())
        tutor->SetID(id);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap Ho va ten moi     : ";
    gotoXY(valueX, contentY + 1);
    string name;
    getline(cin, name);
    if (name != "N" && name != "n" && !name.empty())
        tutor->SetUserName(name);

    gotoXY(labelX, contentY + 2);
    cout << "Dia chi moi            : ";
    gotoXY(valueX, contentY + 2);
    string location;
    getline(cin, location);
    if (location != "N" && location != "n")
        tutor->SetLocation(location);

    gotoXY(labelX, contentY + 3);
    cout << "Nhap mat khau moi      : ";
    gotoXY(valueX, contentY + 3);
    string password;
    getline(cin, password);
    if (password != "N" && password != "n" && !password.empty())
        tutor->SetPassword(password);
    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    FileHandler::SaveTutors();
    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_3(Tutor *tutor)
{
    system("cls");

    int x = 20;
    int y = 5;
    int width = 73; // 71 ky tu ben trong + 2 vien
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
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // Duong chia 2 (truoc footer)
    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 5. In noi dung
    // Tieu de
    SetWordColor(15); // Trang sang
    gotoXY(x + 28, y + 1);
    cout << "[ 3. KIEM TRA SO DU ]";

    // Nhan
    SetWordColor(7); // Trang xam
    gotoXY(x + 4, y + 4);
    cout << "So du hien tai cua ban:";

    SetWordColor(10); // Set mau XANH LA (Bright Green)
    string balance = to_string(tutor->GetBalance());
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 5);
    cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Rut Tien, hoac phim bat ky de quay lai)";
    int footerX = x + (width - footer.length()) / 2; // Can giua
    gotoXY(footerX, y + 8);
    cout << footer;

    // Reset mau
    SetWordColor(7);
    while (true)
    {
        char key = getch();
        if (key == 'N' || key == 'n')
        {
            ShowRutTienScreen(tutor);
            break;
        }
        else
            break;
    }
}

void Screen_Tutor_4(Tutor *tutor)
{
    MyVector<SubjectRecord *> sbjlist = tutor->getSubjectList();
    MyVector<string> stdnames;
    MyVector<string> subnames;
    int currentPage = 0;
    int itemsPerPage = 10; // Số môn học mỗi trang
    int totalItems = 0;
    for (int i = 0; i < sbjlist.getSize(); i++)
    {
        totalItems += sbjlist[i]->GetStudentList().getSize();
        for (int j = 0; j < sbjlist[i]->GetStudentList().getSize(); j++)
        {
            stdnames.push_back(sbjlist[i]->GetStudentList()[j]->GetName());
            subnames.push_back(sbjlist[i]->GetSubject()->GetName());
        }
    }
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
    while (1)
    {
        system("cls");
        int x = 10, y = 5;
        int width = 70; // Tăng chiều rộng để chứa 2 cột

        // Tính toán chiều cao các phần
        int header_height = 3;
        int body_height = 18;
        int footer_height = 3;

        int total_height = header_height + body_height + footer_height - 2;

        char Border = 205;
        char LeftTee = 204;
        char RightTee = 185;

        // Vẽ khung ngoài
        SetWordColor(14);
        rectangle(x, y, width, total_height);

        // Vẽ các đường chia ngang
        int header_divider_y = y + header_height - 1;
        gotoXY(x, header_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        int footer_divider_y = y + header_height + body_height - 2;
        gotoXY(x, footer_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        // Tiêu đề
        SetWordColor(6);
        string title = "DANH SACH HOC VIEN - Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Nội dung - 2 cột
        int contentX = x + 3;
        int contentY_start = y + header_height;

        // Tiêu đề các cột
        gotoXY(contentX + 2, contentY_start + 1);
        cout << "TEN MON HOC";
        gotoXY(contentX + 35, contentY_start + 1);
        cout << " HOC VIEN";

        // Đường kẻ ngang dưới tiêu đề
        gotoXY(contentX, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";
        gotoXY(contentX + 35, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";

        // Hiển thị danh sách môn học
        int startIndex = currentPage * itemsPerPage;
        int endIndex = min(startIndex + itemsPerPage, totalItems);
        int currentY = contentY_start + 4;
        for (int i = startIndex; i < endIndex; i++)
        {
            // Cột tên môn học
            gotoXY(contentX + 2, currentY);
            cout << (i + 1) << ". " << subnames[i];

            // Cột tên học viên
            gotoXY(contentX + 35, currentY);
            cout << stdnames[i];
            currentY++;
        }

        // Thông tin phân trang
        string pageInfo = "Hien thi " + to_string(startIndex + 1) + "-" + to_string(endIndex) +
                          " tren tong " + to_string(totalItems) + " mon hoc";
        gotoXY(x + (width - pageInfo.length()) / 2, currentY + 1);
        cout << pageInfo;

        // Hướng dẫn điều hướng
        SetWordColor(6);
        string footer;
        if (totalPages > 1)
        {
            footer = "Quay lai        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "                            Quay lai";
        }
        gotoXY(x + 1, footer_divider_y + 1);
        cout << footer;

        // Di chuyển con trỏ ra khỏi khung
        gotoXY(0, y + total_height + 2);

        SetWordColor(7);
        Coord d = MouseCoord();
        if (totalPages > 1)
        {
            if (d.SE != 25)
                continue;
            if (d.FI >= 27 && d.SE <= 40)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 47 && d.FI <= 58)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
            }
            if (d.FI >= 11 && d.FI <= 18)
                break;
        }
        else
        {
            if (d.SE != 25)
                continue;
            if (d.FI <= 48 && d.FI >= 40)
            {
                break;
            }
        }
    }
}

void Screen_Tutor_5(Tutor *tutor)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

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

    gotoXY(labelX, contentY);
    cout << "Nhap ten mon hoc moi    :";
    gotoXY(valueX, contentY);
    string mon;
    getline(cin, mon);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap hoc phi cho mon hoc:";
    gotoXY(valueX, contentY + 1);
    int hp;
    if (!IntInput(hp))
    {
        gotoXY(labelX, contentY + 2);
        SetWordColor(4);
        cout << "Hoc phi da nhap khong hop le!";
        gotoXY(labelX, contentY + 3);
        SetWordColor(6);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }

    gotoXY(labelX, contentY + 6);
    cout << "Da them mon hoc         :" << mon;
    gotoXY(labelX, contentY + 7);
    cout << " va hoc phi la " << hp;

    Subject *newsubject = new Subject(mon, hp);
    SubjectRecord *sr = new SubjectRecord(newsubject, tutor);
    tutor->getSubjectList().push_back(sr);
    FileHandler::AppendSubjectRecordToFile(sr);
    // tutor->AddSubject(newsubject);

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_6(Tutor *tutor)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
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
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

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

    gotoXY(labelX, contentY);
    cout << "Nhap Mon hoc can chinh sua  :";
    gotoXY(valueX, contentY);
    string subject;
    getline(cin, subject);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap hoc phi moi            :";
    gotoXY(valueX, contentY + 1);
    string hp;
    getline(cin, hp);

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
// Hàm so sánh để sắp xếp theo thời gian tăng dần
void Screen_Tutor_8(Tutor *tutor)
{
    system("cls");
    if (!tutor)
    {
        return;
    }

    MyVector<Schedule *> schedules = tutor->GetSchedules();
    int total = schedules.getSize();
    int itemsPerPage = 8;
    int currentPage = 0;
    int totalPages = (total + itemsPerPage - 1) / itemsPerPage;

    while (true)
    {
        system("cls");
        int x = 6, y = 4;
        int width = 100;
        int header_height = 3;
        int body_height = 18;
        int footer_height = 3;
        int total_height = header_height + body_height + footer_height;

        SetWordColor(14);
        rectangle(x, y, width, total_height);

        // header divider
        gotoXY(x, y + 2);
        cout << (char)204;
        for (int i = 0; i < width - 2; ++i)
            cout << (char)205;
        cout << (char)185;

        // title
        SetWordColor(6);
        string title = "LICH DAY - " + tutor->GetName();
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // columns
        SetWordColor(7);
        int contentX = x + 2;
        int contentY = y + 3;
        gotoXY(contentX, contentY);
        cout << "STT    NGAY         GIO         MON HOC                      HOC SINH               TRANG THAI";
        gotoXY(contentX, contentY + 1);
        for (int i = 0; i < width - 4; ++i)
            cout << "-";

        int start = currentPage * itemsPerPage;
        int end = min(start + itemsPerPage, total);
        int line = contentY + 3;
        SortSchedulesByTime(schedules);
        for (int i = start; i < end; ++i)
        {
            Schedule *s = schedules[i];
            string date = s ? s->GetDate() : string("-");
            string time = s ? (s->GetStartTime() + "-" + s->GetEndTime()) : string("-");
            string subj = "-";
            if (s && s->GetSubjectRecord() && s->GetSubjectRecord()->GetSubject())
                subj = s->GetSubjectRecord()->GetSubject()->GetName();
            string student = s && s->GetStudent() ? s->GetStudent()->GetName() : string("-");
            string status = s ? s->GetStatus() : string("-");

            gotoXY(contentX, line);
            // cout << " ";
            cout << setw(3) << left << (i + 1) << "   " << setw(10) << left << date << "   " << setw(9) << left
                 << time << "  " << setw(28) << left << subj << " " << setw(23) << left << student
                 << status;
            line++;
        }

        // footer
        SetWordColor(10);
        string footer = "Trang " + to_string(currentPage + 1) + "/" + to_string(max(1, totalPages)) + "    (<- Trang truoc    -> Trang sau)    Nhan phim bat ky de quay lai";
        gotoXY(x + (width - footer.length()) / 2, y + total_height - 1);
        cout << footer;

        SetWordColor(7);
        // simple keyboard navigation
        int c = getch();
        if (c == 75) // left arrow
        {
            if (currentPage > 0)
                currentPage--;
        }
        else if (c == 77) // right arrow
        {
            if (currentPage + 1 < totalPages)
                currentPage++;
        }
        else
        {
            break;
        }
    }
}

void HandleStudentMenu(Student *student)
{
    ShowStudentMenu(student); // 1. Ve menu sinh vien lan dau tien.

    while (true)
    {                               // 2. Bat dau vong lap su kien cho menu sinh vien.
        Coord click = MouseCoord(); // 3. Cho mot CLICK MOI tu nguoi dung.
        if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
        {
            FindTutorScreen(); // Chay chuc nang tim kiem
            // QUAN TRONG: Sau khi chuc nang ket thuc, ve lai menu
            ShowStudentMenu(student);
        }
        else if (click.FI >= 21 && click.FI <= 54 && click.SE >= 9 && click.SE <= 11)
        {
            Screen_Student_one(student);
            // man hinh hien thi thong tin ca nhan
            ShowStudentMenu(student);
            // quay ve menu
        }
        else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98)
        {
            CreateSchedule(student);
            // Screen_Student_2(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Student_3(student);
            ShowStudentMenu(student);
        }

        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 65 && click.FI <= 98)
        {
            ShowNapTienScreen_4(student);
            ShowStudentMenu(student);
        }

        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 21 && click.FI <= 54)
        {
            ShowDanhSachMonHoc_5(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 65 && click.FI <= 98)
        {
            ShowLichHoc_6(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 65 && click.FI <= 98)
        {
            ScreenDanhGiaTuTor_8();
            ShowStudentMenu(student);
        }

        // nut dang xuat
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
        {
            break; // 4. Thoat khoi vong lap while(true) nay
        }
    }
    // 5. Sau khi 'break', ham nay ket thuc va quay tro lai ham main
}
void HandleTutorMenu(Tutor *tutor)
{
    ShowTutorMenu(tutor);
    while (true)
    {
        Coord click = MouseCoord();
        if (click.SE >= 9 && click.SE <= 11 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_one(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_2(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_3(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_4(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_5(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 65 && click.FI <= 98)
        {
           // Screen_Tutor_6(tutor);//update subject
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
        {
            //Screen_Tutor_7();xac nhan lich day
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_8(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
        {
            break;
        }
    }
}
/**
 * @brief Hàm main
 */
int main()
{
    PrintMenu();
    while (1)
    {
        Coord click = MouseCoord();

        if (click.SE >= 19 && click.SE <= 21 && click.FI >= 28 && click.FI <= 45)
        {
            Student *student = LoginStudent();
            if (student != nullptr)
                HandleStudentMenu(student);
            system("cls");
            PrintMenu();
        }

        // Kiem tra nut [Teacher]
        // Y: 19 -> 21, X: 70 -> 86
        else if (click.SE >= 19 && click.SE <= 21 && click.FI >= 52 && click.FI <= 69)
        {
            Tutor *tutor = LoginTutor();
            if (tutor != nullptr)
                HandleTutorMenu(tutor);
            system("cls");
            PrintMenu();
        }

        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 46 && click.FI <= 70)
        {
            // LoginUser();
            Program prg;
            system("cls");
            prg.RegisterNewUser();
            _getch();
            system("cls");
            PrintMenu();
        }

        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 76 && click.FI <= 93)
        {
            break;
        }
    }
    return 0;
}