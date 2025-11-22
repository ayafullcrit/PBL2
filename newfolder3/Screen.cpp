#include "Screen.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;
void rectangle(int x, int y, int width, int height)
{
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186;

    // màu vàng sáng

    // --- góc trên ---
    gotoXY(x, y);
    cout << LeftTop;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTop;

    // --- thân ---
    for (int i = 0; i < height - 2; i++)
    {
        gotoXY(x, y + i + 1);
        cout << UpBorder;
        for (int j = 0; j < width - 2; j++)
            cout << " ";
        cout << UpBorder;
    }

    // --- góc duoi ---
    gotoXY(x, y + height - 1);
    cout << LeftBottom;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightBottom;
}
void SetWordColor(WORD wAttributes)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, wAttributes);
}
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
void gotoXY(short x, short y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GetConsoleSize(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ShowFile(const string &fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Khong the mo file: " << fileName << endl;
        return;
    }

    ostringstream oss;
    string line;
    while (getline(file, line))
    {
        oss << line << '\n';
    }
    file.close();

    SetWordColor(6);
    cout << oss.str();
    SetWordColor(7);
}
bool IntInput(int &a)
{
    string b;
    cin >> b;
    for(int i = 0; i < b.size(); i++)
    {
        if(!isdigit(b[i])) return 0;
    }
    a = stoi(b);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    if (a < 0)
    {
        cout << "Vui long nhap so hop le!" << endl;
        return 0;
    }
    return 1;
}