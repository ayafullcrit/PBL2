#include "Tutor.h"
#include "Student.h"
#include "Subject.h"
#include "Pointer.h"
Tutor::Tutor(const string &id, const string &name, const string &location, const string &pass,
             const int &balance, const int &sbjlist, const double &rating, const int &stdlist)
    : User(id, name, location, pass, balance), SubjectList(sbjlist), Rating(rating),
      StudentList(stdlist)
{
    this->NumOfRatings = 0;
    // cout << "Tutor constructor is called!" << endl;
};
Tutor::Tutor(const Tutor &other)
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
    StudentList = MyVector<Student *>(other.StudentList.getSize());
    for (int i = 0; i < other.StudentList.getSize(); ++i)
    {
        if (other.StudentList[i] != nullptr)
            StudentList.push_back(new Student(*other.StudentList[i]));
        else
            StudentList.push_back(nullptr);
    }
};
Tutor::~Tutor()
{
    for (int i = 0; i < SubjectList.getSize(); ++i)
    {
        Subject *subj = SubjectList[i];
        delete subj;
    }

    // Giải phóng từng Tutor* trong danh sách
    for (int i = 0; i < StudentList.getSize(); ++i)
    {
        Student *t = StudentList[i];
        delete t;
    }
};
void Tutor::DisplayInfo() const
{
    this->User::DisplayInfo();
    cout << "Danh gia: ";
    if (this->NumOfRatings != 0)
        cout << this->Rating / this->NumOfRatings << endl;
    else cout << "Chua co danh gia" << endl;
}
void Tutor::AddSubject(Subject &NewSubject)
{
    cout << "Da them mon " << NewSubject.GetName() << "!" << endl;
    this->SubjectList.push_back(&NewSubject);
}
void Tutor::AddStudent(Student &NewStudent)
{
    cout << "Da them hoc sinh " << NewStudent.GetName() << endl;
    this->StudentList.push_back(&NewStudent);
}
void Tutor::Show_StudentList()
{
    cout << "Danh sach hoc sinh cua giao vien " << this->GetName() << ":\n";
    for (int i = 0; i < this->StudentList.getSize(); i++)
    {
        cout << StudentList[i]->GetName() << endl;
    }
}
void Tutor::Show_SubjectList()
{
    cout << "Danh sach cac mon hoc cua giao vien " << this->GetName() << ":\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << SubjectList[i]->GetName() << endl;
    }
}
void Tutor::DeleteStudent(const string &studentID)
{
    for(int i = 0; i < StudentList.getSize(); ++i) 
    {
        if(StudentList[i]->GetID() == studentID) {
            StudentList.removeAt(i);
            cout << "Da xoa hoc sinh voi ID: " << studentID << endl;
            return;
        }
    }
    // Implementation for deleting a student by ID can be added here
}