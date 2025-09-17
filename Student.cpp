#include <iostream>
#include <vector>
#include <string>
#include"Username.hpp"
#include"Student.h"
using namespace std;

User::User(string accName, string pass, string uname, string id, string loc, int balance) {
    this->AccountName = accName;
    this->Password = pass;
    this->UserName = uname;
    this->AccountId = id;
    this->Location = loc;
    this->AccountBalance = balance;
}

void Student::AddTeacher(const Teacher& t){
    TeacherList.push_back(t);
    cout<<"Them giao vien:"<<t.GetName()<<endl;
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
        for (auto s : t.Getsubject()) {
            if (s.Getname() == subjectName) {
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
