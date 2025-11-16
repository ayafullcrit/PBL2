#include "Schedule.h"
#include <iostream>
#include <iomanip>

using namespace std;

Schedule::Schedule(const string &id, const string &d, const string &st,
                   const string &et, const string &stat, SubjectRecord *sr,
                   Student *s, Tutor *t, const string &loc, const string &note, bool att)
    : scheduleID(id), date(d), startTime(st), endTime(et), status(stat),
      subjectRecord(sr), student(s), tutor(t), location(loc), notes(note), attendance(att) {}

Schedule::Schedule(const Schedule &other)
{
    *this = other;
}

bool Schedule::IsTimeConflict(const Schedule &other) const
{

    if (this->date != other.date)
        return false;

    bool sameTutor = (this->tutor && other.tutor && this->tutor->GetID() == other.tutor->GetID());
    bool sameStudent = (this->student && other.student && this->student->GetID() == other.student->GetID());

    if (!sameTutor && !sameStudent)
        return false;

    bool startsDuringOther = (this->startTime >= other.startTime && this->startTime < other.endTime);
    bool endsDuringOther = (this->endTime > other.startTime && this->endTime <= other.endTime);
    bool encompassesOther = (this->startTime <= other.startTime && this->endTime >= other.endTime);

    return startsDuringOther || endsDuringOther || encompassesOther;
}

void Schedule::UpdateStatus(const string &newStatus)
{
    this->status = newStatus;
    if (newStatus == "completed")
    {
        this->attendance = true;
    }
}

void Schedule::DisplayScheduleInfo() const
{
    cout << "=== THONG TIN LICH HOC ===" << endl;
    cout << "Ma lich: " << scheduleID << endl;
    cout << "Ngay: " << date << endl;
    cout << "Thoi gian: " << startTime << " - " << endTime << endl;
    cout << "Thoi luong: " << GetDuration() << " phut" << endl;
    cout << "Trang thai: " << status << endl;
    cout << "Dia diem: " << location << endl;

    if (subjectRecord && subjectRecord->GetSubject())
    {
        cout << "Mon hoc: " << subjectRecord->GetSubject()->GetName() << endl;
    }
    
    if (tutor)
    {
        cout << "Gia su: " << tutor->GetName() << endl;
    }

    if (student)
    {
        cout << "Hoc sinh: " << student->GetName() << endl;
    }

    if (!notes.empty())
    {
        cout << "Ghi chu: " << notes << endl;
    }

    cout << "Diem danh: " << (attendance ? "Da diem danh" : "Chua diem danh") << endl;
    cout << "==========================" << endl;
}

string Schedule::GetDuration() const
{
    // Tính thời lượng buổi học (phút)
    int startHour = stoi(startTime.substr(0, 2));
    int startMinute = stoi(startTime.substr(3, 2));
    int endHour = stoi(endTime.substr(0, 2));
    int endMinute = stoi(endTime.substr(3, 2));

    int totalMinutes = (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
    return to_string(totalMinutes);
}

Schedule &Schedule::operator=(const Schedule &other)
{
    if (this == &other)
        return *this;

    this->scheduleID = other.scheduleID;
    this->date = other.date;
    this->startTime = other.startTime;
    this->endTime = other.endTime;
    this->status = other.status;
    this->subjectRecord = other.subjectRecord;
    this->student = other.student;
    this->tutor = other.tutor;
    this->location = other.location;
    this->notes = other.notes;
    this->attendance = other.attendance;

    return *this;
}