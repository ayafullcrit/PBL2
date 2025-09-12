
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include"Username.hpp"
using namespace std;

class Teacher : public User{//ke thua tu User
	private:
		vector<Student> StudentList;
		vector<Subject> SubjectList;	
	//ƠU
	public:
		
		void AddSubject();
		void Update_SubjectInfo();
		void DeleteSubJect();
		
		void Show_StudentList();// xem danh sach hoc sinh dang theo hoc
		void Find_NewStudent();
		void Find_ByLocation();
		void AddStudent();
		void DeleteStudent();
	
		void Update_Schedule();	
		
		void Get_TeachingFee();
		vector <Subject> Getsubject(){
			return this-> SubjectList;
		}
		
};

class Subject{
	private: 
	unsigned int Fee;
	string Name;
	vector<string> Session;
	float rate;
	public:
	string Getname(){
		return this->Name;
	}
};


class Student : public User {
private:
    vector<Teacher> TeacherList;
    vector<Subject> SubjectList;
public:
    Student(string accName = "", string pass = "", string uname = "", string id = "", string loc = "", int balance = 0);

    void AddTeacher(Teacher t);
    void Show_TeacherList() ;

    void Find_BySubject(string& subjectName);
    void Find_ByLocation( string& location) ;

    void Pay_TeachingFee(Teacher* t, int amount);
    void FeedBack();
};

