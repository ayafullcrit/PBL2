#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "Admin.h"
#include "../Utility/Program.h"
#include "Student.h"
#include "Tutor.h"
#include "../Utility/FileHandler.h"
#include "../Utility/Screen.h"
bool Admin::RemoveUser(const string &UserID)
{
    Program prg;
    User *user = nullptr;
    int si = -1, ti = -1;
    Student *student = NULL;
    Tutor *tutor = NULL;
    for (int i = 0; i < prg.getStudentList().getSize(); i++)
    {
        if (prg.getStudentList()[i]->GetID() == UserID)
        {
            si = i;
            student = prg.getStudentList()[i];
        }
    }
    for (int i = 0; i < prg.getTutorList().getSize(); i++)
    {
        if (prg.getTutorList()[i]->GetID() == UserID)
        {
            ti = i;
            tutor = prg.getTutorList()[i];
        }
    }
    if (si != -1)
    {
        prg.getStudentList().removeAt(si);
        FileHandler::SaveStudents();
    }
    else if (ti != -1)
    {
        prg.getTutorList().removeAt(ti);
        FileHandler::SaveTutors();
    }
    else{
        cout << "Khong tim thay nguoi dung !";
        return 0;
    }
    return 1;
}
void Admin::ApproveTutor(Tutor *tutor)
{
    Program prg;
    gotoXY(13, 8 + prg.getTutorList().getSize());
    cout << "Ban muon duyet/ tu choi gia su " << tutor->GetName() << " (Y/N)? ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        tutor->SetApproved(true);
       // cout << "Da duyet gia su " << tutor->GetName() << "." << endl;
    }
    else
    {
        tutor->SetApproved(false);
      //  cout << "Da tu choi gia su " << tutor->GetName() << "." << endl;
    }
    FileHandler::SaveTutors();
}
bool Admin::ResetPassword(const string& UserID)
{
    Program prg;
    User* user = NULL;
    Student* student = prg.GetstdByID(UserID);
    Tutor* tutor = prg.GetTutorByID(UserID);
    if(student) {
        student->SetPassword("123456");
        FileHandler::SaveStudents();
    }
    else if(tutor) {
        tutor->SetPassword("123456");
        FileHandler::SaveTutors();
    }
    else
    {
        cout << "Khong tim thay nguoi dung!";
        return 0;
    }
    return 1;
}