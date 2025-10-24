#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h> 
#include <cstdlib>
#define FOR(i, a, b) for (int i = a; i <= b; i++)
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
int LeftMargin = 50;
int TopMargin = 2;

void PrintTitle()
{
	SetWordColor(2);
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186;
    gotoXY(LeftMargin, TopMargin);
    cout << LeftTop;
    FOR(i, 1, 58)
    cout << Border;
    cout << RightTop;
    gotoXY(LeftMargin, TopMargin + 1);
    cout << UpBorder;
    FOR(i, 1, 10)
    cout << " ";
    SetWordColor(10);
    cout << "        DU AN CO SO LAP TRINH    ";
    FOR(i, 1, 15)
    cout << " ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 2);
    cout << UpBorder;
    FOR(i, 1, 3)
    cout << " ";
    SetWordColor(10);
    cout << "       Ung dung ho tro quan ly gia su và hoc vien ";
    FOR(i, 1, 5)
    cout << " ";
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
    FOR(i,1,58)
    cout<<" ";
    SetWordColor(2);
    cout << UpBorder;
    gotoXY(LeftMargin, TopMargin + 10);
    cout << LeftBottom;
    FOR(i, 1, 58)
    cout << Border;
    cout << RightBottom;
    // in ra 8 dong
    TopMargin = 14;
}

void PrintMenu(){
    PrintTitle();
    int LeftMargin = 50;
    int TopMargin = 14;

    SetWordColor(14);
    gotoXY(LeftMargin, TopMargin);
    FOR(i,1,15)
        cout<<" ";
    cout << char(201);
    FOR(i,1,25)  
        cout<<char(205);
    cout<<char(187);

    LeftMargin = 50 + 15;
    gotoXY(LeftMargin, TopMargin + 1);
    cout<<char(186);
    FOR(i,1,6)
        cout<<" ";
    SetWordColor(6);
    cout<<"Who are you? ";
    FOR(i,1,6)
        cout<<" ";
    SetWordColor(14);
    cout<<char(186);

    gotoXY(LeftMargin, TopMargin + 2);
    cout<<char(200);
    FOR(i,1,25)
        cout<<char(205);
    cout<<char(188);

    int boxWidth = 16;      
    int spaceBetween = 8;   
    int totalWidth = 3 * boxWidth + 2 * spaceBetween;
    int screenCenter = LeftMargin + 13; 
    int firstBoxX = screenCenter - totalWidth / 2;

    int boxY = TopMargin + 5;
    string titles[3] = {"Hoc Vien", "Teacher", "Admin"};

    FOR(b,0,2) {
        int x = firstBoxX + b * (boxWidth + spaceBetween);

        gotoXY(x, boxY);
        SetWordColor(14);
        cout << char(201);
        FOR(i,1,boxWidth)
            cout<<char(205);
        cout<<char(187);

        gotoXY(x, boxY + 1);
        cout<<char(186);
        int padding = (boxWidth - titles[b].length()) / 2;
        FOR(i,1,padding)
            cout<<" ";
        SetWordColor(6);
        cout<<titles[b];
        FOR(i,1,boxWidth - padding - titles[b].length())
            cout<<" ";
        SetWordColor(14);
        cout<<char(186);

        gotoXY(x, boxY + 2);
        cout<<char(200);
        FOR(i,1,boxWidth)
            cout<<char(205);
        cout<<char(188);
    }
    gotoXY(30, 100);
}

void PrintLoginOrRegister() 
{
	system("cls");
	int n; 
	string s;
	SetWordColor(6);
	cout<<"Nhap 1 neu da co tai khoan"<<endl;
	cout<<"Nhap 2 neu chua co tai khoan"<<endl;
	cout<<"nhap lua chon cua ban: "<<" ";
	cin >>n;
	if(n==1){
		system("cls");
		cout<<"Ten dang nhap"<<": ";
		cin.ignore();
		getline(cin, s);
		cout<<"Password: ";
		getline(cin, s);
	}
	else if (n==2){
		system("cls");
		cout<<"Vui long tao tai khoan o nut dang ky"<<endl;
	}
	else {
		cout<< "Cu phap ko hop le. Vui long nhap lai";
	}
	
	
}


int main() {
    PrintMenu();
    int a;
    cout<<"Nhap lua chon cua ban ";
    cin>>a;
    if(a==4){
    	PrintLoginOrRegister();
    	
	}
    


    return 0;
}
