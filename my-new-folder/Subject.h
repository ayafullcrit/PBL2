#pragma once
#include <string>
using namespace std;

class Subject
{
private:
    string sbjID;
    string SubjectName;
    int Cost;
    
public:
    // con/destructor
    Subject(const string &sbjname = "DefaultName", const int &cost = 200
            ,const string &id = "SUBJ0000")
        : SubjectName(sbjname), Cost(cost), sbjID(id) {};
    Subject(const Subject &) = default;
    ~Subject() {};
    // Setter
    // Getter
    string GetName() { return this->SubjectName; };
    int GetCost() { return this->Cost; }
    string GetID() { return this->sbjID; };
    void SetID(const string& id){ this->sbjID = id; };
    //
    void Update_SubjectInfo();
};