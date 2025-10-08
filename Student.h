
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include"User.hpp"
using namespace std;

class Student : public User {
private:
    vector<Teacher> TeacherList;
    vector<Subject> SubjectList;
public:
    Student(string accName = "", string pass = "", string uname = "", string id = "", string loc = "", int balance = 0);

    void AddTeacher(const Teacher& t);
    void Show_TeacherList() ;

    void Find_BySubject(string& subjectName);
    void Find_ByLocation( string& location) ;

    void Pay_TeachingFee(Teacher t, int amount);
    void FeedBack();
	friend class Subject;
	friend class Teacher;
};
// code mỗi class 1 file
