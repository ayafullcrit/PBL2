#pragma once

#include "Tutor.h"
#include "Student.h"
#include "SubjectRecord.h"
#include "MyVector.h"
#include "Schedule.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class FileHandler
{
private:
    static const string TUTOR_FILE;
    static const string STUDENT_FILE;
    static const string SUBJECT_RECORD_FILE;
    static const string SCHEDULE_FILE;

public:
    // Load methods
    static bool LoadTutors();
    static bool LoadStudents();
    static bool LoadSubjectRecords();
    static bool LoadSchedules();

    // Save methods
    static bool SaveTutors();
    static bool SaveStudents();
    static bool SaveSubjectRecords();
    static bool SaveSchedules();

    // Utility methods
    static bool SaveAllData();
    static bool ValidateFile(const string &filename);

    // Specific write operations for registration
    static bool AppendTutorToFile(Tutor *tutor);
    static bool AppendStudentToFile(Student *student);
    static bool AppendSubjectRecordToFile(SubjectRecord *subjectRecord);
    static bool AppendScheduleToFile(Schedule* schedule);
};