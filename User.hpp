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
        // bool IsExisted();
        // bool IsValid();
};