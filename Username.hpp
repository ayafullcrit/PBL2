#pragma once
#include <string>
using namespace std;
class User {
private:
    string AccountName;
    string Password;
    string UserName;
    string AccountId;
    string Location;
    int AccountBalance;
public:
    User(string accName = "", string pass = "", string uname = "", string id = "", string loc = "", int balance = 0);

    void ShowInfo() const;
    string GetLocation() const { return Location; }
    string GetName() const { return this->UserName; }
    int GetBalance() const { return AccountBalance; }
    void UpdateBalance(int amount) { AccountBalance += amount; }

};
