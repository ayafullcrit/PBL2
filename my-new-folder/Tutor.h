#pragma once
#include "User.h"
#include "MyVector.h"
class SubjectRecord;
class Student;
class Subject;
class Tutor : public User
{
private:
    double Rating;
    int NumOfRatings;
    MyVector<SubjectRecord *> SubjectList;

public:
    // con/destructor
    Tutor(const string & = "000000", const string & = "DefaultName",
          const string & = "Viet Nam", const string & = "12345",
          const int & = 0, const int & = 0, const double & = 0);
    Tutor(const Tutor &);
    ~Tutor();
    // override funcion
    string GetRole() const override { return "Gia su"; };
    void DisplayInfo() const override;
    //
    double GetRating() const { return Rating; }
    void SetRating(const double &rating)
    {
        Rating = rating;
    }
    int GetNumOfRatings() const { return NumOfRatings; }
    void SetNumOfRatings(const int &numofratings)
    {
        NumOfRatings = numofratings;
    };
    MyVector<SubjectRecord *> &getSubjectList() { return SubjectList; }
    SubjectRecord* operator[](int);
    Tutor& operator=(const Tutor&);
    //  class's method
    void AddSubject(Subject &);
    void AddSubject(const string &);
    void addStudentToSubject(Student &, Subject &s);
    void Show_SubjectList();
    void Show_StudentList();
    void DeleteStudent(Student&);
    //
};