#pragma once
#include "User.h"
#include "MyVector.h"
class Subject;
class Student;
class Tutor : public User
{
private:
    double Rating;
    MyVector<Subject*> SubjectList;
    MyVector<Student*> StudentList;

public:
    // con/destructor
    Tutor(const string & = "000000", const string & = "DefaultName",
          const string & = "Viet Nam", const string & = "12345",
          const int & = 0,const double& = 0,const int& = 10,
          const int & = 10);
    Tutor(const Tutor &);
    ~Tutor();
    // override funcion
    string GetRole() const override { return "Gia su"; };
    void DisplayInfo() const override;
    // bool Authenticate
    //  class's method
    void AddSubject(Subject &);
    void AddStudent(Student &);
    void Show_SubjectList();
    void Show_StudentList();
    //
};