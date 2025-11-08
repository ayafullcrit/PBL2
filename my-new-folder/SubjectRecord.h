#pragma once
#include "Subject.h"
#include "MyVector.h"
#include "Student.h"
class SubjectRecord
{
    private:
        Subject* subject;
        MyVector<Student*> StudentList;
    public:
        SubjectRecord(Subject* subj = nullptr) : subject(subj) {};
        SubjectRecord(const SubjectRecord& other);
        ~SubjectRecord();

        Subject* GetSubject() const { return subject; }
        MyVector<Student*>& GetStudentList() { return StudentList; }
        string GetID(){return subject->GetID();};
        void SetID(const string& id){ subject->SetID(id); };
        Student* operator[](int index) { return StudentList[index]; }
        void AddStudent(Student* student);
        void ShowStudentList() const;
        void ClearStudents();
        
};
