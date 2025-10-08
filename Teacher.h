#include<iostream>
#include"User.hpp"
#include <vector>
#include"Student.h"
class Teacher : public User{//ke thua tu User
	private:
		vector<Student> StudentList;
		vector<Subject> SubjectList;	
	//ƠU
	public:
		//friend Update_AccountInfo()
		
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

        
		
		//friend Show_Schedule();
		//Update_Schedule();	
		
		//Get_TeachingFee();
};