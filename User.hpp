#pragma once
#include <string>
using namespace std;
class User{
    private:
        string Role;
        string AccountName;
        string UserName;
        string Password;
        string location;
        int AccountBalance;
    public:
        User();
        User(const string& role, const string& accountName, const string& userName, const string& password,const string& location, const int& accountBalance);
        void Register();
        void Login();
        void ShowInfo();
        string GetLocation() const { return Location; }
       string GetName() const { return this->UserName; }
        int GetBalance() const { return AccountBalance; }
        // bool IsExisted();
        // bool IsValid();

};
