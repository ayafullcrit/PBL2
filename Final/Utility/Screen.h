#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <regex>
#include "MyVector.h"
#define Coord pair<int, int>
#define SE second
#define FI first
using namespace std;
class Schedule;
bool IsMouseClicked(COORD &mousePos);
void SetWordColor(WORD wAttributes);
void gotoXY(short x, short y);
void GetConsoleSize(int &width, int &height);
void ShowFile(const string &fileName);
void rectangle(int x, int y, int width, int height);
string getPassword(int x, int y, int maxLength);
bool IntInput(int &a);
bool compareSchedulesByTime(Schedule *a, Schedule *b);
MyVector<Schedule *> SortSchedulesByTime(MyVector<Schedule *> schedules);
Coord MouseCoord();
#endif