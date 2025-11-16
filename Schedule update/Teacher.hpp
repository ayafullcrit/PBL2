#pragma once
#include "User.hpp"
#include <vector>
#include "Subject.h"
class Teacher : public User
{
    public:
        vector<Subject> GetSubjectList();
        bool HasSubject(string);
};