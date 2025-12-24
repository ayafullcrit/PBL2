#pragma once
#include "../Core/User.h"
#include "../Template/MyVector.h"
class SubjectRecord;
class Student;
class Subject;
class Schedule;
class Tutor : public User
{
private:
    bool approved;
    double Rating;
    int NumOfRatings;
    MyVector<SubjectRecord *> SubjectList;
    MyVector<Schedule *> tutorSchedules;
    string availableSlots;

public:
    // con/destructor
    Tutor(const string & = "000000", const string & = "DefaultName",
          const string & = "Viet Nam", const string & = "12345", const string & = "0000000000",
          const bool & = false, const int & = 0, const int & = 0, const double & = 0, const int & = 0);
    Tutor(const Tutor &);
    ~Tutor();
    // override funcion
    string GetRole() const override { return "Gia su"; };
    void DisplayInfo() const override;
    //
    double GetRating() const { return Rating; }
    void SetRating(const double rating)
    {
        Rating = rating;
    }
    int GetNumOfRatings() const { return NumOfRatings; }
    bool IsApproved() const { return approved; }
    void SetApproved(const bool &app) { approved = app; }
    MyVector<Schedule *> &GetSchedules() { return tutorSchedules; }
    string GetAvailableSlots() const { return availableSlots; }
    void SetNumOfRatings(const int numofratings)
    {
        NumOfRatings = numofratings;
    };
    MyVector<SubjectRecord *> &getSubjectList() { return SubjectList; }
    SubjectRecord *operator[](int);
    Tutor &operator=(const Tutor &);
    //  class's method
    void AddSubject(Subject *);
    void AddSubject(const string &);
    void addStudentToSubject(Student *, string);
    void AddSchedule(Schedule *);
    void Show_SubjectList();
    void Show_StudentList();
    void ViewTeachingSchedule() const;
    void DeleteStudent(Student *);
    bool IsTimeAvailable(const string &, const string &) const;
    void ConfirmSchedule(Schedule *);
    void CancelSchedule(Schedule *, const string &);
    //
};