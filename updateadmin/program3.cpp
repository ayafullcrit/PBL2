#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <limits>
#include "../Utility/Screen.h"
#include "../Utility/FileHandler.h"
#include "../Utility/Program.h"
#include "../Models/Student.h"
#include "../Models/Admin.h"
#include "../Screen/StudentScreen.h"
#include "../Screen/TutorScreen.h"
#include "../Screen/AdminScreen.h"
#define FOR(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

int LeftMargin = 50;
int TopMargin = 2;

void PrintTitle()
{
    SetWordColor(6);
    SetConsoleOutputCP(65001); // chuyen doi qua UCRT -8
    ShowFile("DataBase/MenuTutor.txt");
    SetConsoleOutputCP(437); // chuyen ve lai ASCII
    // SetConsoleOutputCP(65001);
    // ShowFile("MenuTutor.txt");
}

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
        else if (click.SE >= 20 && click.SE <= 22 && click.FI >= 76 && click.FI <= 93)
        {
            Admin *admin = LoginAdmin();
            if (admin)
                HandleAdminMenu(admin);
            system("cls");
            PrintMenu();
        }
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 46 && click.FI <= 70)
        {
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
// /*
// g++  -o program3
// */
