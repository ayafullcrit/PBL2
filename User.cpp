#include <iostream>
#include <fstream>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include "User.hpp"
using namespace std;

User::User(const string &role, const string &accountName, const string &userName, const string &password,const string& location, const int &accountBalance)
    : Role(role), AccountName(accountName), UserName(userName), Password(password), location(location), AccountBalance(accountBalance) {}

User::User() : Role("User"), AccountName(""), UserName(""), Password(""), location(""), AccountBalance(0) {}

void User::ShowInfo()
{
    cout << "Ban la :" << this->Role << endl;
    cout << "Ten tai khoan: " << this->AccountName << endl;
    cout << "Ten nguoi dung: " << this->UserName << endl;
    cout << "Mat khau: " << this->Password << endl;
    cout << "Dia chi: " << this->location << endl;
    cout << "So du tai khoan: " << this->AccountBalance << endl;
}

void User::Register()
{
    string tempstr;
    unordered_map<string, bool> users;
    fstream UserDB("User.txt");
    if (UserDB.fail())
    {
        cerr << "Error opening User database file." << endl;
        return;
    }
    //<Role> <AccountName> <UserName> <Password> <location> <AccountBalance>
    while (!UserDB.eof())
    {
        UserDB >> tempstr;
        users[tempstr] = true;
        UserDB >> tempstr;
        UserDB.ignore((numeric_limits<streamsize>::max)(), '\n'); // skip line
    }
    cout << "Dang ky" << endl;
    cout << "Nhap ten tai khoan: ";
    cin >> this->AccountName;
    if (users[this->AccountName])
    {
        cout << "Tai khoan da ton tai. Vui long chon ten khac." << endl;
        return;
    }
    cout << "Nhap mat khau: ";
    cin >> this->Password;
    string TempPassword;
    cout << "Nhap lai mat khau: ";
    cin >> TempPassword;
    if (TempPassword != this->Password)
    {
        cout << "Mat khau khong khop. Vui long thu lai." << endl;
        return;
    }
    // Xoa_man_hinh();
    cout << "Ban la giao vien/hoc sinh? (G/H): ";
    char choice;
    cin >> choice;
    if (choice == 'G' || choice == 'g')
    {
        this->Role = "GiaoVien";
    }
    else if (choice == 'H' || choice == 'h')
    {
        this->Role = "HocSinh";
    }
    else
    {
        cout << "Lua chon khong hop le. Mac dinh ban la hoc sinh." << endl;
        this->Role = "Hoc sinh";
    }
    cout << "Nhap ten nguoi dung: ";
    cin.ignore();
    getline(cin, this->UserName);
    cout << "Nhap dia chi: ";
    getline(cin, this->location);
    this->AccountBalance = 0;
    UserDB.clear();            // clear EOF flag
    UserDB.seekp(0, ios::end); // move to end of file for appending
    UserDB << this->Role << " " << this->AccountName << " " << '\"' + this->UserName + '\"' << " " << this->Password << " " << this->location << " " << this->AccountBalance << endl;
    cout << "Dang ky thanh cong!";
    UserDB.close();
}

void User::Login()
{
    string tempstr;
    unordered_map<string, User> users; // AccountName -> (Password, User)
    fstream UserDB("User.txt");
    if (UserDB.fail())
    {
        cerr << "Error opening User database file." << endl;
        return;
    }
    while (!UserDB.eof())
    {
        string Role, AccountName, UserName, Password, location;
        int AccountBalance;
        UserDB >> Role >> AccountName;
        if(Role.empty()) break; // to avoid processing empty lines
        UserDB.ignore();                 // ignore space before getline
        getline(UserDB, UserName, '\"'); // read until first quote
        getline(UserDB, UserName, '\"'); // read until second quote
        UserDB >> Password >> location >> AccountBalance;
        users[AccountName] = User(Role, AccountName, UserName, Password, location,AccountBalance);
        UserDB.ignore((numeric_limits<streamsize>::max)(), '\n'); // skip line
    }
    cout << "Dang nhap" << endl;
    cout << "Nhap ten tai khoan: ";
    cin >> AccountName;
    if (users.find(AccountName) == users.end())
    {
        cerr << "Tai khoan khong ton tai. Vui long dang ky." << endl;
        return;
    }
    cout << "Nhap mat khau: ";
    cin >> Password;
    if (users[this->AccountName].Password != Password)
    {
        cerr << "Mat khau khong dung. Vui long thu lai." << endl;
        return;
    }
    *this = users[this->AccountName];
    cout << "Dang nhap thanh cong, chao mung !" << endl;
    ShowInfo();
    UserDB.close();
}