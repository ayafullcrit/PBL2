#include<iostream>
#include"Username.hpp"
#include <vector>
#include"Student.h"
#include"Teacher.h"

istream& operator >>(istream& , Student& p){

}

ostream& operator <<(ostream&, const Student& p){
    
}

void Teacher::AddStudent(const Student& t){
    StudentList.push_back(t);
    cout<<"Them giao vien:"<<t.GetName()<<endl;
}

void Teacher::AddSubject(const Subject& m ){
    SubjectList.push_back(m);
    cout<<""

}