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
    Subject(const string &, const int & = 0, const string& = "SUBJ000");
        
    Subject(const Subject &) = default;
    ~Subject() {};
    // Setter
    // Getter
    string GetName() { return this->SubjectName; };
    int GetCost() { return this->Cost; }
    string GetID() { return this->sbjID; };
    void SetID(const string& id){ this->sbjID = id; };
    void SetName(const string name) {this->SubjectName = name;};
    void SetCost(const int cost){this->Cost = cost;};
    //
    void Update_SubjectInfo();
};