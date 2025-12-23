#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "User.h"
#include "FileHandler.h"
#include "Screen.h"
#include <limits>
User::User(const User &other)
{
    *this = other;
    // cout << "User copy constructor is called!" << endl;
}
bool User::Authenticate(const string &InputPassword) const
{
    return this->Password == InputPassword;
}
void User::Deposit(const int &t)
{
    this->SetBalance(this->UserBalance + t);
    if (this->GetRole() == "Hoc sinh")
        FileHandler::SaveStudents();
    else
        FileHandler::SaveTutors();
}
bool User::Withdraw(const int &t)
{
    if (this->UserBalance < t)
        return 0;
    this->UserBalance -= t;
    if (this->GetRole() == "Hoc sinh")
        FileHandler::SaveStudents();
    else
        FileHandler::SaveTutors();
    return 1;
}
void User::DisplayInfo() const
{
    int x = 10, y = 5;
    int contentY = y + 4; 
    int labelX = x + 3;   
    int valueX = x + 24; 
    SetWordColor(10); // Màu Vàng Cam
    gotoXY(labelX, contentY + 1);
    cout << "Vai tro         :";
    SetWordColor(15); // Màu trắng
    gotoXY(valueX, contentY + 1);
    cout << GetRole();

    SetWordColor(10); // Màu Vàng Cam
    gotoXY(labelX, contentY + 2);
    cout << "ID              :";
    SetWordColor(15); // Màu trắng
    gotoXY(valueX, contentY + 2);
    cout << UserID;

    gotoXY(labelX, contentY + 3);
    SetWordColor(10); // Màu Vàng Cam
    cout << "Ten nguoi dung  :";
    gotoXY(valueX, contentY + 3);
    SetWordColor(15); // Màu trắng
    cout << UserName;

    SetWordColor(10); // Màu Vàng Cam
    gotoXY(labelX, contentY + 4);
    cout << "So dien thoai   :";
    SetWordColor(15); // Màu trắng
    gotoXY(valueX, contentY + 4);
    cout << PhoneNumber;

    SetWordColor(10); // Màu Vàng Cam
    gotoXY(labelX, contentY + 5);
    cout << "Dia chi         :";
    SetWordColor(15); // Màu trắng
    gotoXY(valueX, contentY + 5);
    cout << Location;

    SetWordColor(10); // Màu Vàng Cam
    gotoXY(labelX, contentY + 6);
    cout << "So du tai khoan :";
    SetWordColor(15); // Màu trắng
    gotoXY(valueX, contentY + 6);
    cout << UserBalance;

}
void User::UpdateInfo()
{
    cout << "Cap nhat thong tin nguoi dung:" << endl;
    cout << "Ten nguoi dung hien tai: " << this->UserName << endl;
    cout << "Ban can cap nhat ten nguoi dung khong? (Y/N): ";
    string choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice != "Y" && choice != "y" && choice != "N" && choice != "n")
    {
        cout << "Lua chon khong hop le!";
        return;
    }
    else if (choice != "N" && choice != "n")
    {
        cout << "Nhap ten nguoi dung moi: ";
        getline(cin, this->UserName);
        cout << "Ten cua ban da duoc doi thanh: " << this->UserName;
        cout << endl;
    }
    cout << "Cap nhat thong tin dia chi:" << endl;
    cout << "Dia chi hien tai: " << this->Location << endl;
    cout << "Ban can cap nhat dia chi moi hay khong? (Y/N): ";
    cin >> choice;
    cin.ignore();
    if (choice != "Y" && choice != "y" && choice != "N" && choice != "n")
    {
        cout << "Lua chon khong hop le!";
        return;
    }
    if(choice != "Y" && choice != "y") return;
    cout << "Nhap dia chi moi: ";
    getline(cin, this->Location);
    if (this->GetRole() == "Hoc sinh")
        FileHandler::SaveStudents();
    else
        FileHandler::SaveTutors();
}
User &User::operator=(const User &other)
{
    if (this == &other)
        return *this;
    this->UserID = other.UserID;
    this->UserName = other.UserName;
    this->Password = other.Password;
    this->Location = other.Location;
    this->UserBalance = other.UserBalance;

    return *this;
}