#include "User.h"
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
}
bool User::Withdraw(const int &t)
{
    if (this->UserBalance < t)
        return 0;
    this->UserBalance -= t;
    return 1;
}
void User::DisplayInfo() const
{
    cout << "Vai tro: " << this->GetRole() << endl;
    cout << "ID tai khoan: " << this->UserID << endl;
    cout << "Dia chi: " << this->Location << endl;
    cout << "So du tai khoan: " << this->UserBalance << endl;
}
void User::UpdateInfo()
{
    cout << "Cap nhat thong tin nguoi dung:" << endl;
    cout << "Ten nguoi dung hien tai: " << this->UserName << endl;
    cin.ignore();
    cout << "Ban can cap nhat ten nguoi dung khong? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        return;
    if (choice == 'N' || choice == 'n')
        return;
    cout << "Nhap ten nguoi dung moi: ";
    getline(cin, this->UserName);
    cout << "Ten cua ban da duoc doi thanh: " << this->UserName;
    cout << endl;
    cout << "Cap nhat thong tin dia chi:" << endl;
    cout << "Dia chi hien tai: " << this->Location << endl;
    cin.ignore();
    cout << "Ban can cap nhat dia chi moi hay khong? (Y/N): ";
    cin >> choice;
    if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
        return;
    if (choice == 'N' || choice == 'n')
        return;
    cout << "Nhap dia chi moi: ";
    getline(cin, this->Location);
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