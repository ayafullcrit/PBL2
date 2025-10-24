#pragma once
#include "User.h"
#include "MyVector.h"
class Tutor;
class Subject;

class Student : public User
{
private:
    int GradeLevel;
    MyVector<Subject *> SubjectList;
    MyVector<Tutor *> TutorList;

public:
    // con/destructor
    Student(const string & = "000000", const string & = "DefaultName",
            const string & = "Viet Nam", const string & = "12345",
            const int & = 0, const double & = 1, const int & = 0,
            const int & = 0);
    Student(const Student &);
    ~Student();
    // override funcion
    string GetRole() const override { return "Hoc sinh"; };
    void DisplayInfo() const override;
    //
    MyVector<Tutor *>& GetTutorList() { return TutorList; };
    int GetGradeLevel() const { return GradeLevel; }
    void SetGradeLevel(const int &gradelevel) { GradeLevel = gradelevel; }
    //  class's method
    Student& operator=(const Student&);
    void AddSubject(Subject &);
    void AddTutor(Tutor &);
    void Show_SubjectList();
    void Show_TutorList();
    void PayCost(Subject &);
    void Rating(Tutor &, const double &);
    // void AddStudent()
    //
};