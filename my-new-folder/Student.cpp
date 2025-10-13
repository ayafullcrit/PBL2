#include "Student.h"
#include "Tutor.h"
#include "Subject.h"
Student::Student(const string &id, const string &name, const string &location, const string &pass,
                 const int &balance, const double &grade, const int &sbjlist, const int &ttlist)
    : User(id, name, location, pass, balance), GradeLevel(grade), SubjectList(sbjlist),
      TutorList(ttlist) {
          // cout << "Tutor constructor is called!" << endl;
      };
Student::Student(const Student &other)
      : User(other)
{
    SubjectList = MyVector<Subject *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new Subject(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }
    TutorList = MyVector<Tutor *>(other.TutorList.getSize());
    for (int i = 0; i < other.TutorList.getSize(); ++i)
    {
        if (other.TutorList[i] != nullptr)
            TutorList.push_back(new Tutor(*other.TutorList[i]));
        else
            TutorList.push_back(nullptr);
    }
}
Student::~Student()
{
    for (int i = 0; i < SubjectList.getSize(); ++i)
    {
        Subject *subj = SubjectList[i];
        delete subj;
    }

    // Giải phóng từng Tutor* trong danh sách
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        Tutor *t = TutorList[i];
        delete t;
    }
}
void Student::DisplayInfo() const
{
    this->User::DisplayInfo();
    cout << "Lop: " << GradeLevel << endl;
}