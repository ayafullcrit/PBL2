#pragma once
#include <string>
using namespace std;

class Subject
{
private:
    string SubjectName;
    int Cost;

public:
    // con/destructor
    Subject(const string &sbjname = "DefaultName", const int &cost = 200)
        : SubjectName(sbjname), Cost(cost) {};
    Subject(const Subject &) = default;
    ~Subject(){};
    // Setter
    // Getter
    string GetName() { return this->SubjectName; };
};