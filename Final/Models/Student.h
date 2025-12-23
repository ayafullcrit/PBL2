#pragma once
#include "User.h"
#include "MyVector.h"
class Tutor;
class Subject;
class Schedule;
class Student : public User
{
private:
    int GradeLevel;
    MyVector<Subject *> SubjectList;
    MyVector<Tutor *> TutorList;
    MyVector<Schedule *> studentSchedules;

public:
    // con/destructor
    Student(const string & = "000000", const string & = "DefaultName",
            const string & = "Viet Nam", const string & = "12345", const string & = "0000000000",
            const int & = 0, const int & = 1, const int & = 0,
            const int & = 0);
    Student(const Student &);
    ~Student();
    // override funcion
    string GetRole() const override { return "Hoc sinh"; };
    void DisplayInfo() const override;
    //
    MyVector<Subject *> &GetSubjectList() { return this->SubjectList; };
    MyVector<Tutor *> &GetTutorList() { return TutorList; };
    MyVector<Schedule *> &GetSchedules() { return studentSchedules; }
    int GetGradeLevel() const { return GradeLevel; }
    void SetGradeLevel(const int &gradelevel) { GradeLevel = gradelevel; }
    //  class's method
    Student &operator=(const Student &);
    void AddSubject(Subject *);
    void AddTutor(Tutor *);
    void AddSchedule(Schedule *);
    void Show_SubjectList();
    void Show_TutorList();
    void ViewWeeklySchedule() const;
    void RequestScheduleChange(Schedule *schedule, const string &newTime);
    void PayCost(Subject &);
    void Rating(Tutor *, const double);
};