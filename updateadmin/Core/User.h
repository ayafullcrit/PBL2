#pragma once
#include "IUser.h"
#include <iostream>

class User : public IUser
{
protected:
    string UserID;
    string UserName;
    string Password;
    string PhoneNumber;
    string Location;
    int UserBalance;

public:
    // con/destructor
    User(const string &userID = "000000", const string &userName = "DefaultName", const string &location = "Viet Nam",
         const string &password = "12345", const string &phoneNumber = "0000000000", const int &userbalance = 0)
        : UserID(userID), UserName(userName), Password(password), PhoneNumber(phoneNumber),
          Location(location), UserBalance(userbalance) {
              // cout << "User constructor is called!" << endl;
          };
    User(const User &);
    virtual ~User() = default;
    // override function
    virtual string GetRole() const override { return "User"; };
    virtual void DisplayInfo() const override;
    bool Authenticate(const string &) const override;
    void UpdateInfo();
    // Getter
    string GetID() { return this->UserID; }
    string GetName() const { return UserName; }
    string GetPassword() const { return Password; }
    string GetLocation() const { return Location; }
    string GetPhoneNumber() const { return PhoneNumber; }
    int GetBalance() const { return UserBalance; }
    // Setter
    void SetID(const string &id) { UserID = id; }
    void SetUserName(const string &userName) { UserName = userName; }
    void SetPassword(const string &password) { Password = password; }
    void SetLocation(const string &location) { Location = location; }
    void SetBalance(int balance) { UserBalance = balance; }
    User &operator=(const User &);
    // Balance fucntion
    void Deposit(const int &);  // Add money
    bool Withdraw(const int &); // Withdraw money
};