#pragma once
#include <string>
using namespace std;
class User{
    private:
        string Role;
        string AccountName;
        string UserName;
        string Password;
        string Location;
        int AccountBalance;
    public:
        User();
        User(const string& role, const string& accountName, const string& userName, const string& password,const string& location, const int& accountBalance);
        void Register();
        void Login();
        void Logout();
        void ShowInfo();
        void Update_UserName();
        void Update_Location();
        string GetRole() const { return this->Role; }
        string GetLocation() const { return this->Location ; }
        string GetName() const { return this->UserName; }
        string GetAccountName() const { return this->AccountName; }
        int GetBalance() const { return this->AccountBalance; }
        void SetBalance(int amount) { this->AccountBalance = amount; }
};