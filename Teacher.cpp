#include <iostream>
#include <vector>
#include "User.hpp"
#include "Student.h"
#include "Teacher.h"
#include <algorithm>
#include "Subject.h"
using namespace std;


void Teacher::AddStudent(const Student& t) {
    StudentList.push_back(t);
    cout << "Them hoc sinh: " << t.GetName() << endl;
}

void Teacher::AddSubject(const Subject& m) {
    SubjectList.push_back(m);
    cout << "Them mon hoc: " << m.GetSubject() << endl;
}

void Teacher::Show_StudentList() {
    cout << "Danh sach hoc sinh cua giao vien " << this->GetName() << ":\n";
    for (const auto& student : StudentList) {
        cout << student.GetName() << endl;
    }
}
void Teacher::Find_NewStudent() {
    string subjectName;
    cout << "Nhap ten mon hoc can tim: ";
    cin >> subjectName;

    cout << "Hoc sinh dang tim mon " << subjectName << ":\n";
    for (const auto& student : StudentList) {
        for (const auto& subject : student.SubjectList) {
            if (subject.GetSubject() == subjectName) {
                cout << student.GetName() << endl;
                break;
            }
        }
    }
}
void Teacher::Find_ByLocation(){
    string location;
    cout << "Nhap vi tri can tim: ";
    cin >> location;

    cout << "Hoc sinh o vi tri " << location << ":\n";
    for (const auto& s : StudentList) {
        if (s.GetLocation() == location) {
            cout << s.GetLocation() << endl;
        }
    }
}
void Teacher::DeleteStudent() {
    string studentName;
    cout << "Nhap ten hoc sinh can xoa: ";
    cin >> studentName;

    auto it = remove_if(StudentList.begin(), StudentList.end(),
                        [&studentName](const Student& s) { return s.GetName() == studentName; });

    if (it != StudentList.end()) {
        StudentList.erase(it, StudentList.end());
        cout << "Da xoa hoc sinh: " << studentName << endl;
    } else {
        cout << "Khong tim thay hoc sinh: " << studentName << endl;
    }
}
void Teacher::Update_SubjectInfo() {
    string subjectName;
    cout << "Nhap ten mon hoc can cap nhat: ";
    cin >> subjectName;

    for (auto& subject : SubjectList) {
        if (subject.GetSubject() == subjectName) {
            unsigned int newFee;
            cout << "Nhap hoc phi moi: ";
            cin >> newFee;
            // Giả sử Subject có phương thức để cập nhật học phí
            // subject.UpdateFee(newFee);
            cout << "Da cap nhat hoc phi cho mon " << subjectName << endl;
            return;
        }
    }
    cout << "Khong tim thay mon hoc: " << subjectName << endl;
}
