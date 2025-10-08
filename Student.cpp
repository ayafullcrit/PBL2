#include <iostream>
#include <vector>
#include <string>
#include"Student.h"
#include"User.hpp"
#include"Teacher.h"
#include"Subject.h"
using namespace std;

Student::Student(string accName, string pass, string uname, string id, string loc, int balance)
    : User("Student", accName, uname, pass, loc, balance) {}

void Student::AddTeacher(const Teacher& t) {
    TeacherList.push_back(t);
    cout << "Added teacher: " << t.GetName() << endl;
}

void Student::Show_TeacherList(){
    cout<<"Danh sach gia su"<<endl;
    for (auto t: TeacherList){
        cout<<t.GetName()<<endl; 
    }
}

void Student::Find_BySubject( string& subjectName){
    cout << "Searching teachers for subject: " << subjectName << endl;
    for (auto t : TeacherList) {
        for (auto s : t.GetSubjectList()) {
            if (s.GetSubject() == subjectName) {
                t.ShowInfo();
            }
        }
    }
}

void Student::Find_ByLocation( string& location) {
    cout << "Searching teachers in location: " << location << endl;
    for (auto t : TeacherList) {
        if (t.GetLocation() == location) {
            t.ShowInfo();
        }
    }
}

void Student::Pay_TeachingFee(Teacher t, int amount) {
    if ( t.GetBalance()>= amount) {
        t.UpdateBalance(-amount);
        cout << "Paid " << amount << " VND to teacher " << t.GetName() << endl;
    } else {
        cout << "Not enough balance!" << endl;
    }
}

void Student::FeedBack(){
    string s;
    getline(cin,s);
    int n;
    cout<<"Nhan xet cua Sinh vien"<<s<<endl;
    cout<<"Đánh giá số sao cho giao vien"<<endl;
    cin>>n;
    cout<<n<<endl;
}
