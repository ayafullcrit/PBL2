#include "Subject.h"
#include "../Utility/FileHandler.h"
#include "../Utility/Program.h"
#include <iostream>
using namespace std;
Subject::Subject(const string &sbjname = "DefaultName", const int &cost, const string &ID)
    : SubjectName(sbjname), Cost(cost), sbjID(ID)
{
    if (sbjID != "SUBJ000")
        return;
    Program t;
    this->sbjID = t.GenID();
}
void Subject::Update_SubjectInfo()
{
    char c = 'y';
    cout << "Ten mon hoc: " << this->SubjectName;
    cout << "Ban co muon doi ten mon hoc nay? (y/n): ";
    cin >> c;
    if (c == 'y')
    {
        string temp_string;
        cout << "Nhap ten moi cua mon hoc :";
        cin >> temp_string;
        this->SubjectName = temp_string;
        cout << "Ten mon hoc da duoc thay doi thanh: " << temp_string;
    }
    cout << "Hoc phi cua mon hoc hien tai: " << this->Cost;
    cout << "Ban co muon cap nhat hoc phi moi? (y/n): ";
    cin >> c;
    if (c == 'y')
    {
        int temp_int;
        cout << "Nhap hoc phi moi: ";
        cin >> temp_int;
        this->Cost = temp_int;
        cout << "Hoc phi moi cua mon " << this->SubjectName << " la " << temp_int;
    }
    FileHandler::SaveTutors();
    FileHandler::SaveSubjectRecords();
}