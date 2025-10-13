#pragma once
#include <iostream>
#include <vector>
#include "User.hpp"
#include "Student.h"


using namespace std;
class Student;
class Teacher : public User { //ke thua tu User
private:
    Student a;
    vector<Student> StudentList;
    vector<Subject> SubjectList;    
public:
    //friend Update_AccountInfo()
    Teacher(string accName = "", string pass = "", string uname = "", string id = "", string loc = "", int balance = 0);

    void AddSubject(const Subject&);
    void Update_SubjectInfo();
    void DeleteSubJect();
    
    void Show_StudentList();// xem danh sach hoc sinh dang theo hoc
    void Find_NewStudent();
    void Find_ByLocation();
    void AddStudent(const Student& );
    void DeleteStudent();
    friend ostream& operator <<(ostream&, const Student&);
    friend istream& operator >>(istream&, Student&);
    friend class Subject;
    vector<Subject> GetSubjectList() const;
};
