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
#define Coord pair<int, int>
#define SE second
#define FI first
using namespace std;
void SetWordColor(WORD wAttributes);
void gotoXY(short x, short y);
void GetConsoleSize(int &width, int &height);
void ShowFile(const string &fileName);
void rectangle(int x, int y, int width, int height);
bool IntInput(int &a);
Coord MouseCoord();

#endif