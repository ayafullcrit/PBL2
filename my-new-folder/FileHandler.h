#pragma once

#include "Tutor.h"
#include "Student.h"
#include "SubjectRecord.h"
#include "MyVector.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class FileHandler {
private:
    static const string TUTOR_FILE;
    static const string STUDENT_FILE;
    static const string SUBJECT_RECORD_FILE;

public:
    // Load methods
    static bool LoadTutors(MyVector<Tutor*>& tutors, MyVector<User*>& users);
    static bool LoadStudents(MyVector<Student*>& students, MyVector<User*>& users, MyVector<Tutor*>);
    static bool LoadSubjectRecords(MyVector<SubjectRecord*>& subjectRecords, 
                                  MyVector<Tutor*>& tutors, MyVector<Student*>& students);
    
    // Save methods
    static bool SaveTutors();
    static bool SaveStudents();
    static bool SaveSubjectRecords();
    
    // Utility methods
    static bool SaveAllData(MyVector<Tutor*>& tutors, MyVector<Student*>& students);
    static bool BackupData();
    static bool ValidateFile(const string& filename);
    
    // Specific write operations for registration
    static bool AppendTutorToFile(Tutor* tutor);
    static bool AppendStudentToFile(Student* student);
    static bool AppendSubjectRecordToFile(SubjectRecord* subjectRecord);
};