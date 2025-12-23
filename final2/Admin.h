#pragma once
#include "MyVector.h"
#include "User.h"
#include "Tutor.h"
class Admin : public User
{
private:
public:
    Admin(const string &userID = "000000", const string &userName = "DefaultName", const string &location = "Viet Nam",
          const string &password = "12345", const string &phoneNumber = "0000000000",
          const int &userbalance = 0)
         : User(userID,userName,location,password,phoneNumber,userbalance){};
         string GetRole() const override
         {
             return "Admin";
         }
         bool RemoveUser(const string &UserID);
         bool ResetPassword(const string &UserID);
         void ApproveTutor(Tutor *tutor);
};