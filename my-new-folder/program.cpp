#include "Admin.h"
#include "SubjectRecord.h"
#include "Tutor.h"

void displayStudentMenu(Student *student, Admin &admin)
{
    int choice;
    do
    {
        cout << "\n===== MENU HOC SINH =====" << endl;
        cout << "Chao mung: " << student->GetName() << " (ID: " << student->GetID() << ")" << endl;
        cout << "1. Hien thi thong tin ca nhan" << endl;
        cout << "2. Cap nhat thong tin ca nhan" << endl;
        cout << "3. Kiem tra so du" << endl;
        cout << "4. Nap tien" << endl;
        cout << "5. Hien thi danh sach mon hoc" << endl;
        cout << "6. Hien thi danh sach gia su" << endl;
        cout << "7. Tim kiem va them gia su" << endl;
        cout << "8. Danh gia gia su" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            student->DisplayInfo();
            break;
        case 2:
            student->UpdateInfo();
            break;
        case 3:
            cout << "So du hien tai: " << student->GetBalance() << " VND" << endl;
            break;
        case 4:
        {
            int amount;
            cout << "Nhap so tien can nap: ";
            cin >> amount;
            student->Deposit(amount);
            cout << "Nap tien thanh cong! So du moi: " << student->GetBalance() << " VND" << endl;
            break;
        }
        case 5:
            student->Show_SubjectList();
            break;
        case 6:
            student->Show_TutorList();
            break;
        case 7:
        {
            admin.FindTutor(student); 
            break;
        }
        case 8:
        {
            cout << "\n===== DANH GIA GIA SU =====" << endl;

            MyVector<Tutor *> &tutorList = student->GetTutorList();
            if (tutorList.getSize() == 0)
            {
                cout << "Ban chua co gia su nao de danh gia!" << endl;
                break;
            }

            student->Show_TutorList();

            int tutorIndex;
            cout << "Chon gia su can danh gia (nhap so thu tu): ";
            cin >> tutorIndex;
            cin.ignore();

            if (tutorIndex < 1 || tutorIndex > tutorList.getSize())
            {
                cout << "So thu tu khong hop le!" << endl;
                break;
            }

            Tutor *selectedTutor = tutorList[tutorIndex - 1];
            double rating;
            cout << "Nhap diem danh gia cho gia su " << selectedTutor->GetName() << " (0-5): ";
            cin >> rating;
            cin.ignore();

            student->Rating(*selectedTutor, rating);
            break;
        }
        case 0:
            cout << "Dang xuat..." << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }

        if (choice != 0)
        {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }
    } while (choice != 0);
}

void displayTutorMenu(Tutor *tutor, Admin &admin)
{
    int choice;
    do
    {
        cout << "\n===== MENU GIA SU =====" << endl;
        cout << "Chao mung: " << tutor->GetName() << " (ID: " << tutor->GetID() << ")" << endl;
        cout << "1. Hien thi thong tin ca nhan" << endl;
        cout << "2. Cap nhat thong tin ca nhan" << endl;
        cout << "3. Kiem tra so du" << endl;
        cout << "4. Hien thi danh sach mon hoc" << endl;
        cout << "5. Hien thi danh sach hoc sinh" << endl;
        cout << "6. Them mon hoc moi" << endl;
        cout << "7. Cap nhat thong tin mon hoc" << endl;
        cout << "8. Xem danh gia" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            tutor->DisplayInfo();
            break;
        case 2:
            tutor->UpdateInfo();
            break;
        case 3:
            cout << "So du hien tai: " << tutor->GetBalance() << " VND" << endl;
            break;
        case 4:
            tutor->Show_SubjectList();
            break;
        case 5:
            tutor->Show_StudentList();
            break;
        case 6:
        {
            string subjectName;
            int cost;
            cout << "Nhap ten mon hoc moi: ";
            getline(cin, subjectName);
            cout << "Nhap hoc phi: ";
            cin >> cost;
            cin.ignore();

            Subject newSubject(subjectName, cost);
            tutor->AddSubject(newSubject);
            cout << "Da them mon hoc: " << subjectName << " voi hoc phi: " << cost << endl;
            break;
        }
        case 7:
        {
            tutor->Show_SubjectList();
            int subjectIndex;
            cout << "Chon mon hoc can cap nhat (nhap so thu tu): ";
            cin >> subjectIndex;
            cin.ignore();

            if (subjectIndex >= 1 && subjectIndex <= tutor->getSubjectList().getSize())
            {
                Subject *subject = tutor->getSubjectList()[subjectIndex - 1]->GetSubject();
                subject->Update_SubjectInfo();
            }
            else
            {
                cout << "So thu tu khong hop le!" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Diem danh gia hien tai: " << tutor->GetRating() << "/5" << endl;
            cout << "So luot danh gia: " << tutor->GetNumOfRatings() << endl;
            break;
        }
        case 0:
            cout << "Dang xuat..." << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }

        if (choice != 0)
        {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }
    } while (choice != 0);
}

int main()
{
    Admin admin;
   int mainChoice;
    cout << "CHUONG TRINH QUAN LY GIA SU - KHOI TAO THANH CONG!" << endl;

    do
    {
        cout << "\n===== MENU CHINH =====" << endl;
        cout << "1. Dang nhap (Hoc sinh)" << endl;
        cout << "2. Dang nhap (Gia su)" << endl;
        cout << "3. Dang nhap (Tu dong phan loai)" << endl;
        cout << "4. Dang ky tai khoan moi" << endl;
        cout << "5. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice)
        {
        case 1:
        {
            string id, password;
            cout << "Nhap ID: ";
            getline(cin, id);
            cout << "Nhap mat khau: ";
            getline(cin, password);

            Student *student = admin.LoginStudent(id, password);
            if (student != nullptr)
            {
                displayStudentMenu(student, admin);
            }
            break;
        }
        case 2:
        {
            string id, password;
            cout << "Nhap ID: ";
            getline(cin, id);
            cout << "Nhap mat khau: ";
            getline(cin, password);

            Tutor *tutor = admin.LoginTutor(id, password);
            if (tutor != nullptr)
            {
                displayTutorMenu(tutor, admin);
            }
            break;
        }
        case 3:
        {
            string id, password;
            cout << "Nhap ID: ";
            getline(cin, id);
            cout << "Nhap mat khau: ";
            getline(cin, password);

            User *user = admin.LoginUser(id, password);
            if (user != nullptr)
            {
                if (user->GetRole() == "Hoc sinh")
                {
                    Student *student = dynamic_cast<Student *>(user);
                    displayStudentMenu(student, admin);
                }
                else if (user->GetRole() == "Gia su")
                {
                    Tutor *tutor = dynamic_cast<Tutor *>(user);
                    displayTutorMenu(tutor, admin);
                }
            }
            break;
        }
        case 4:
            admin.RegisterNewUser();
            break;
        case 5:
            cout << "Cam on ban da su dung dich vu! Tam biet!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (mainChoice != 5);

    return 0;
}