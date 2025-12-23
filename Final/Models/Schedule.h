#pragma once
#include "SubjectRecord.h"
#include "Student.h"
#include "Tutor.h"
#include <string>

using namespace std;

class Schedule {
private:
    string scheduleID;
    string date;         
    string startTime;    
    string endTime;     
    string status;    
    SubjectRecord* subjectRecord;
    Student* student;
    Tutor* tutor;
    string location;   
    string notes;         
    bool attendance;       

public:
    // Constructor
    Schedule(const string& id = "", const string& d = "", const string& st = "", 
             const string& et = "", const string& stat = "pending", 
             SubjectRecord* sr = nullptr, Student* s = nullptr, Tutor* t = nullptr,
             const string& loc = "Online", const string& note = "", bool att = false);
    
    Schedule(const Schedule& other);
    ~Schedule() = default;

    // Getter methods
    string GetID() const { return scheduleID; }
    string GetDate() const { return date; }
    string GetStartTime() const { return startTime; }
    string GetEndTime() const { return endTime; }
    string GetStatus() const { return status; }
    SubjectRecord* GetSubjectRecord() const { return subjectRecord; }
    Student* GetStudent() const { return student; }
    Tutor* GetTutor() const { return tutor; }
    string GetLocation() const { return location; }
    string GetNotes() const { return notes; }
    bool GetAttendance() const { return attendance; }

    // Setter methods
    void SetDate(const string& d) { date = d; }
    void SetStartTime(const string& st) { startTime = st; }
    void SetEndTime(const string& et) { endTime = et; }
    void SetStatus(const string& stat) { status = stat; }
    void SetLocation(const string& loc) { location = loc; }
    void SetNotes(const string& note) { notes = note; }
    void SetAttendance(bool att) { attendance = att; }

    // Utility methods
    bool IsTimeConflict(const Schedule& other) const;
    void UpdateStatus(const string& newStatus);
    void DisplayScheduleInfo() const;
    string GetDuration() const;
    bool IsCompleted() const { return status == "completed"; }
    bool IsConfirmed() const { return status == "confirmed"; }
    bool IsPending() const { return status == "pending"; }

    Schedule& operator=(const Schedule& other);
};