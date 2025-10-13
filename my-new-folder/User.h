#pragma once
#include "IUser.h"
#include <iostream>

class User : public IUser
{
protected:
    string UserID;
    string UserName;
    string Password;
    string Location;
    int UserBalance;

public:
    // con/destructor
    User(const string &userID = "000000", const string &userName = "DefaultName", 
        const string &password = "12345", const string &location = "Viet Nam", 
        const int &userbalance = 0)
        : UserID(userID), UserName(userName), Password(password), 
          Location(location), UserBalance(userbalance) {
           // cout << "User constructor is called!" << endl;
        };
    User(const User &) = default;
    ~User() override {};
    // override function
    virtual string GetRole() const override {return "User";};
    virtual void DisplayInfo() const override;
    bool Authenticate(const string&) const override;
    void UpdateInfo();
    // Getter
    string GetID() { return this->UserID; }
    string GetName() const { return UserName; }
    string GetPassword() const { return Password; }
    string GetLocation() const { return Location; }
    int GetBalance() const { return UserBalance; }
    //Setter
    void SetUserName(const string& userName) { UserName = userName; }
    void SetPassword(const string& password) { Password = password; }
    void SetLocation(const string& location) { Location = location; }
    void SetBalance(int balance) { UserBalance = balance; }
    //Balance fucntion
    void Deposit(const int&);//Add money
    bool Withdraw(const int&);// Withdraw money
};