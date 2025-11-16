#include "Tutor.h"
#include "Student.h"
#include "Subject.h"
#include "SubjectRecord.h"
#include "FileHandler.h"
Tutor::Tutor(const string &id, const string &name, const string &location, const string &pass,
             const int &balance, const int &sbjlist, const double &rating,const int& numrating)
    : User(id, name, location, pass, balance), SubjectList(sbjlist), Rating(rating), 
    NumOfRatings(numrating)
{
    // cout << "Tutor constructor is called!" << endl;
};
Tutor::Tutor(const Tutor &other)
    : User(other)
{
    SubjectList = MyVector<SubjectRecord *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new SubjectRecord(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }
};
Tutor::~Tutor()
{
    // for (int i = 0; i < SubjectList.getSize(); ++i)
    // {
    //     SubjectRecord *subjRec = SubjectList[i];
    //     delete subjRec;
    // }
};
void Tutor::DisplayInfo() const
{
    this->User::DisplayInfo();
    cout << "Danh gia: ";
    if (this->NumOfRatings != 0)
        cout << this->Rating << endl;
    else
        cout << "Chua co danh gia" << endl;
}
void Tutor::AddSubject(Subject* NewSubject)
{
    //  cout << "Da them mon " << NewSubject.GetName() << "!" << endl;
    SubjectRecord* newSubjRec = new SubjectRecord(NewSubject, this);
    this->SubjectList.push_back(newSubjRec);
   // FileHandler::SaveSubjectRecords();
   // FileHandler::SaveTutors();
}
void Tutor::AddSubject(const string &subjectName)
{
    Subject* subject = new Subject(subjectName);
    AddSubject(subject);
}
void Tutor::addStudentToSubject(Student* NewStudent, Subject* s)
{
    for (int i = 0; i < this->SubjectList.getSize(); ++i)
    {
        if (this->SubjectList[i]->GetSubject()->GetName() == s->GetName())
        {
            this->SubjectList[i]->AddStudent(NewStudent);
            NewStudent->AddTutor(this);
            NewStudent->AddSubject(this->SubjectList[i]->GetSubject());
            return;
        }
    }
    // FileHandler::SaveStudents();
    // FileHandler::SaveTutors();
    // cout << "Da them hoc sinh " << NewStudent.GetName() << endl;
}
void Tutor::Show_StudentList()
{
    cout << "Danh sach hoc sinh cua giao vien " << this->GetName() << ":\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << "Mon hoc: " << SubjectList[i]->GetSubject()->GetName() << endl;
        SubjectList[i]->ShowStudentList();
    }
}
void Tutor::Show_SubjectList()
{
    cout << "Danh sach cac mon hoc cua giao vien " << this->GetName() << ":\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << "- " << SubjectList[i]->GetSubject()->GetName() << endl;
    }
}
void Tutor::DeleteStudent(Student &std)
{
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        SubjectRecord *subjRec = this->SubjectList[i];
        MyVector<Student *> studentList = subjRec->GetStudentList();
        for (int j = 0; j < studentList.getSize(); ++j)
        {
            if (studentList[j]->GetID() == std.GetID())
            {
                studentList.removeAt(j);
                cout << "Da xoa hoc sinh " << std.GetName() << " khoi mon " << subjRec->GetSubject()->GetName() << endl;
                return;
            }
        }
    }
}
SubjectRecord *Tutor::operator[](int index)
{
    if (index < 0 || index >= this->SubjectList.getSize())
    {
        throw out_of_range("Index out of range in Tutor::operator[]");
    }
    return this->SubjectList[index];
}
Tutor &Tutor::operator=(const Tutor &other)
{
    if (this == &other)
        return *this;
    User::operator=(other);
    this->Rating = other.Rating;
    this->NumOfRatings = other.NumOfRatings;
    // Deep copy of SubjectList
    for( int i = 0; i < this->SubjectList.getSize(); ++i)
    {
        delete this->SubjectList[i];
    }
    this->SubjectList = MyVector<SubjectRecord *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            this->SubjectList.push_back(new SubjectRecord(*other.SubjectList[i]));
        else
            this->SubjectList.push_back(nullptr);
    }

    return *this;
}