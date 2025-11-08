#include "User.h"
#include "FileHandler.h"
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
    return 1;
    if (this->GetRole() == "Hoc sinh")
        FileHandler::SaveStudents();
    else
        FileHandler::SaveTutors();
}
void User::DisplayInfo() const
{
    cout << "Vai tro: " << this->GetRole() << endl;
    cout << "ID tai khoan: " << this->UserID << endl;
    cout << "Ten nguoi dung: " << this->UserName << endl;
    cout << "Dia chi: " << this->Location << endl;
    cout << "So du tai khoan: " << this->UserBalance << endl;
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