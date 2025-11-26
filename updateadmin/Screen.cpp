#include "Screen.h"
#include "Schedule.h"
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
    if(b.size() == 0) return 0;
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
        return 0;
    }
    return 1;
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
MyVector<Schedule *> SortSchedulesByTime(MyVector<Schedule *> schedules)
{
    int n = schedules.getSize();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (!compareSchedulesByTime(schedules[j], schedules[j + 1]))
            {
                // Hoán đổi hai phần tử
                Schedule *temp = schedules[j];
                schedules[j] = schedules[j + 1];
                schedules[j + 1] = temp;
            }
        }
    }
    return schedules;
}