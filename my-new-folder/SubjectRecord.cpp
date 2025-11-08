#include "SubjectRecord.h"
#include <iostream>
using namespace std;
SubjectRecord::SubjectRecord(const SubjectRecord& other)
{
    subject = other.subject;
    StudentList = MyVector<Student*>(other.StudentList.getSize());
    for (int i = 0; i < other.StudentList.getSize(); ++i)
    {
        StudentList.push_back(other.StudentList[i]);
    }
}
void SubjectRecord::ShowStudentList() const
{
    for (int i = 0; i < StudentList.getSize(); ++i)
    {
        cout << "- " << StudentList[i]->GetName() << endl;
    }
}
void SubjectRecord::AddStudent(Student* student)
{
    StudentList.push_back(student);
}
void SubjectRecord::ClearStudents()
{
    while(StudentList.getSize() > 0) {
        StudentList.pop_back();
    }
}
SubjectRecord::~SubjectRecord()
{
    delete subject;
}