// #include "Program.h"
// #include "SubjectRecord.h"
// #include "Tutor.h"
// #include "Schedule.h"
// #include "FileHandler.h"
// #include <limits>

// bool ChoiceInput(int &choice)
// {
//     cin >> choice;
//     if (cin.fail())
//     {
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         cout << "Vui long nhap so hop le!" << endl;
//         return 0;
//     }
//     return 1;
// }

// void displayStudentMenu(Student *student, Program &program)
// {
//     int choice;
//     do
//     {
//         cout << "\n===== MENU HOC SINH =====" << endl;
//         cout << "Chao mung: " << student->GetName() << " (ID: " << student->GetID() << ")" << endl;
//         cout << "1. Hien thi thong tin ca nhan" << endl;
//         cout << "2. Cap nhat thong tin ca nhan" << endl;
//         cout << "3. Quan ly tai khoan" << endl;
//         cout << "4. Danh sach mon hoc va gia su" << endl;
//         cout << "5. Tim kiem va them gia su" << endl;
//         cout << "6. Quan ly lich hoc" << endl;
//         cout << "7. Danh gia gia su" << endl;
//         cout << "0. Dang xuat" << endl;
//         cout << "Chon chuc nang: ";
//         if (!ChoiceInput(choice))
//             continue;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         switch (choice)
//         {
//         case 1:
//             student->DisplayInfo();
//             break;
//         case 2:
//             student->UpdateInfo();
//             break;
//         case 3:
//         {
//             int accountChoice;
//             do {
//                 cout << "\n===== QUAN LY TAI KHOAN =====" << endl;
//                 cout << "1. Kiem tra so du" << endl;
//                 cout << "2. Nap tien" << endl;
//                 cout << "0. Quay lai" << endl;
//                 cout << "Chon chuc nang: ";
//                 if (!ChoiceInput(accountChoice)) continue;
                
//                 switch(accountChoice) {
//                     case 1:
//                         cout << "So du hien tai: " << student->GetBalance() << " VND" << endl;
//                         break;
//                     case 2:
//                     {
//                         int amount;
//                         cout << "Nhap so tien can nap: ";
//                         cin >> amount;
//                         if (amount > 0) {
//                             student->Deposit(amount);
//                             cout << "Nap tien thanh cong! So du moi: " << student->GetBalance() << " VND" << endl;
//                         } else {
//                             cout << "So tien khong hop le!" << endl;
//                         }
//                         break;
//                     }
//                     case 0:
//                         break;
//                     default:
//                         cout << "Lua chon khong hop le!" << endl;
//                 }
//             } while (accountChoice != 0);
//             break;
//         }
//         case 4:
//         {
//             cout << "\n===== DANH SACH MON HOC =====" << endl;
//             student->Show_SubjectList();
//             break;
//         }
//         case 5:
//             program.FindTutor(student);
//             break;
//         case 6:
//         {
//             int scheduleChoice;
//             do {
//                 cout << "\n===== QUAN LY LICH HOC =====" << endl;
//                 cout << "1. Xem lich hoc" << endl;
//                 cout << "2. Dang ky lich hoc moi" << endl;
//                 cout << "3. Yeu cau doi lich" << endl;
//                 cout << "0. Quay lai" << endl;
//                 cout << "Chon chuc nang: ";
//                 if (!ChoiceInput(scheduleChoice)) continue;
                
//                 switch(scheduleChoice) {
//                     case 1:
//                         program.ViewStudentSchedule(student->GetID());
//                         break;
//                     case 2:
//                     {
//                         // Hiển thị danh sách gia sư và môn học để chọn
//                         student->Show_TutorList();
//                         MyVector<Tutor*> &tutorList = student->GetTutorList();
//                         if (tutorList.getSize() == 0) {
//                             cout << "Ban chua co gia su nao! Vui long them gia su truoc." << endl;
//                             break;
//                         }
                        
//                         int tutorIndex;
//                         cout << "Chon gia su (nhap so thu tu): ";
//                         if (!ChoiceInput(tutorIndex)) break;
                        
//                         if (tutorIndex < 1 || tutorIndex > tutorList.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         Tutor* selectedTutor = tutorList[tutorIndex - 1];
//                         selectedTutor->Show_SubjectList();
                        
//                         MyVector<SubjectRecord*> &subjectList = selectedTutor->getSubjectList();
//                         if (subjectList.getSize() == 0) {
//                             cout << "Gia su nay chua co mon hoc nao!" << endl;
//                             break;
//                         }
                        
//                         int subjectIndex;
//                         cout << "Chon mon hoc (nhap so thu tu): ";
//                         if (!ChoiceInput(subjectIndex)) break;
                        
//                         if (subjectIndex < 1 || subjectIndex > subjectList.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         SubjectRecord* selectedSubject = subjectList[subjectIndex - 1];
//                         program.CreateSchedule(student, selectedTutor, selectedSubject);
//                         break;
//                     }
//                     case 3:
//                     {
//                         // Yêu cầu đổi lịch
//                         program.ViewStudentSchedule(student->GetID());
//                         MyVector<Schedule*> &schedules = student->GetSchedules();
//                         if (schedules.getSize() == 0) {
//                             cout << "Khong co lich hoc nao!" << endl;
//                             break;
//                         }
                        
//                         int scheduleIndex;
//                         cout << "Chon lich hoc can doi (nhap so thu tu): ";
//                         if (!ChoiceInput(scheduleIndex)) break;
                        
//                         if (scheduleIndex < 1 || scheduleIndex > schedules.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         string newTime;
//                         cout << "Nhap thoi gian moi (YYYY-MM-DD HH:MM): ";
//                         cin.ignore();
//                         getline(cin, newTime);
                        
//                         student->RequestScheduleChange(schedules[scheduleIndex - 1], newTime);
//                         break;
//                     }
//                     case 0:
//                         break;
//                     default:
//                         cout << "Lua chon khong hop le!" << endl;
//                 }
//             } while (scheduleChoice != 0);
//             break;
//         }
//         case 7:
//         {
//             cout << "\n===== DANH GIA GIA SU =====" << endl;
//             MyVector<Tutor *> &tutorList = student->GetTutorList();
//             if (tutorList.getSize() == 0)
//             {
//                 cout << "Ban chua co gia su nao de danh gia!" << endl;
//                 break;
//             }

//             student->Show_TutorList();
//             int tutorIndex;
//             cout << "Chon gia su can danh gia (nhap so thu tu): ";
//             if (!ChoiceInput(tutorIndex)) break;

//             if (tutorIndex < 1 || tutorIndex > tutorList.getSize())
//             {
//                 cout << "So thu tu khong hop le!" << endl;
//                 break;
//             }

//             Tutor *selectedTutor = tutorList[tutorIndex - 1];
//             double rating;
//             cout << "Nhap diem danh gia cho gia su " << selectedTutor->GetName() << " (0-5): ";
//             cin >> rating;
//             cin.ignore();

//             student->Rating(selectedTutor, rating);
//             break;
//         }
//         case 0:
//             cout << "Dang xuat..." << endl;
//             break;
//         default:
//             cout << "Lua chon khong hop le!" << endl;
//         }

//         if (choice != 0)
//         {
//             cout << "\nNhan Enter de tiep tuc...";
//             cin.get();
//         }
//     } while (choice != 0);
// }

// void displayTutorMenu(Tutor *tutor, Program &program)
// {
//     int choice;
//     do
//     {
//         cout << "\n===== MENU GIA SU =====" << endl;
//         cout << "Chao mung: " << tutor->GetName() << " (ID: " << tutor->GetID() << ")" << endl;
//         cout << "1. Hien thi thong tin ca nhan" << endl;
//         cout << "2. Cap nhat thong tin ca nhan" << endl;
//         cout << "3. Quan ly tai khoan" << endl;
//         cout << "4. Danh sach mon hoc va hoc sinh" << endl;
//         cout << "5. Quan ly lich day" << endl;
//         cout << "6. Quan ly mon hoc" << endl;
//         cout << "7. Xem danh gia" << endl;
//         cout << "0. Dang xuat" << endl;
//         cout << "Chon chuc nang: ";
//         if (!ChoiceInput(choice))
//             continue;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         switch (choice)
//         {
//         case 1:
//             tutor->DisplayInfo();
//             break;
//         case 2:
//             tutor->UpdateInfo();
//             break;
//         case 3:
//         {
//             int accountChoice;
//             do {
//                 cout << "\n===== QUAN LY TAI KHOAN =====" << endl;
//                 cout << "1. Kiem tra so du" << endl;
//                 cout << "0. Quay lai" << endl;
//                 cout << "Chon chuc nang: ";
//                 if (!ChoiceInput(accountChoice)) continue;
                
//                 switch(accountChoice) {
//                     case 1:
//                         cout << "So du hien tai: " << tutor->GetBalance() << " VND" << endl;
//                         break;
//                     case 0:
//                         break;
//                     default:
//                         cout << "Lua chon khong hop le!" << endl;
//                 }
//             } while (accountChoice != 0);
//             break;
//         }
//         case 4:
//         {
//             cout << "\n===== DANH SACH MON HOC =====" << endl;
//             tutor->Show_SubjectList();
//             cout << "\n===== DANH SACH HOC SINH =====" << endl;
//             tutor->Show_StudentList();
//             break;
//         }
//         case 5:
//         {
//             int scheduleChoice;
//             do {
//                 cout << "\n===== QUAN LY LICH DAY =====" << endl;
//                 cout << "1. Xem lich day" << endl;
//                 cout << "2. Xac nhan lich hoc" << endl;
//                 cout << "3. Diem danh hoc sinh" << endl;
//                 cout << "4. Huy lich hoc" << endl;
//                 cout << "0. Quay lai" << endl;
//                 cout << "Chon chuc nang: ";
//                 if (!ChoiceInput(scheduleChoice)) continue;
                
//                 switch(scheduleChoice) {
//                     case 1:
//                         program.ViewTutorSchedule(tutor->GetID());
//                         break;
//                     case 2:
//                     {
//                         // Xác nhận lịch học pending
//                         MyVector<Schedule*> &schedules = tutor->GetSchedules();
//                         bool hasPending = false;
                        
//                         cout << "\n===== LICH CHO CHO XAC NHAN =====" << endl;
//                         for (int i = 0; i < schedules.getSize(); ++i) {
//                             if (schedules[i]->GetStatus() == "pending") {
//                                 cout << i + 1 << ". ";
//                                 schedules[i]->DisplayScheduleInfo();
//                                 hasPending = true;
//                             }
//                         }
                        
//                         if (!hasPending) {
//                             cout << "Khong co lich nao cho xac nhan!" << endl;
//                             break;
//                         }
                        
//                         int scheduleIndex;
//                         cout << "Chon lich hoc de xac nhan (nhap so thu tu): ";
//                         if (!ChoiceInput(scheduleIndex)) break;
                        
//                         if (scheduleIndex < 1 || scheduleIndex > schedules.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         Schedule* selectedSchedule = schedules[scheduleIndex - 1];
//                         if (selectedSchedule->GetStatus() != "pending") {
//                             cout << "Lich hoc nay khong can xac nhan!" << endl;
//                             break;
//                         }
                        
//                         tutor->ConfirmSchedule(selectedSchedule);
//                         FileHandler::SaveSchedules();
//                         break;
//                     }
//                     case 3:
//                     {
//                         // Điểm danh học sinh
//                         program.ViewTutorSchedule(tutor->GetID());
//                         MyVector<Schedule*> &schedules = tutor->GetSchedules();
//                         bool hasConfirmed = false;
                        
//                         cout << "\n===== LICH DA XAC NHAN =====" << endl;
//                         for (int i = 0; i < schedules.getSize(); ++i) {
//                             if (schedules[i]->GetStatus() == "confirmed") {
//                                 cout << i + 1 << ". ";
//                                 schedules[i]->DisplayScheduleInfo();
//                                 hasConfirmed = true;
//                             }
//                         }
                        
//                         if (!hasConfirmed) {
//                             cout << "Khong co lich da xac nhan!" << endl;
//                             break;
//                         }
                        
//                         int scheduleIndex;
//                         cout << "Chon lich hoc de diem danh (nhap so thu tu): ";
//                         if (!ChoiceInput(scheduleIndex)) break;
                        
//                         if (scheduleIndex < 1 || scheduleIndex > schedules.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         Schedule* selectedSchedule = schedules[scheduleIndex - 1];
//                         if (selectedSchedule->GetStatus() != "confirmed") {
//                             cout << "Lich hoc nay chua duoc xac nhan!" << endl;
//                             break;
//                         }
                        
//                         string notes;
//                         cout << "Hoc sinh co dien khong? (1: Co, 0: Khong): ";
//                         int attended;
//                         if (!ChoiceInput(attended)) break;
                        
//                         cout << "Nhap ghi chu buoi hoc: ";
//                         cin.ignore();
//                         getline(cin, notes);
                        
//                         program.MarkAttendance(selectedSchedule, attended == 1, notes);
//                         break;
//                     }
//                     case 4:
//                     {
//                         // Hủy lịch học
//                         program.ViewTutorSchedule(tutor->GetID());
//                         MyVector<Schedule*> &schedules = tutor->GetSchedules();
                        
//                         int scheduleIndex;
//                         cout << "Chon lich hoc de huy (nhap so thu tu): ";
//                         if (!ChoiceInput(scheduleIndex)) break;
                        
//                         if (scheduleIndex < 1 || scheduleIndex > schedules.getSize()) {
//                             cout << "So thu tu khong hop le!" << endl;
//                             break;
//                         }
                        
//                         string reason;
//                         cout << "Nhap ly do huy: ";
//                         cin.ignore();
//                         getline(cin, reason);
                        
//                         tutor->CancelSchedule(schedules[scheduleIndex - 1], reason);
//                         FileHandler::SaveSchedules();
//                         break;
//                     }
//                     case 0:
//                         break;
//                     default:
//                         cout << "Lua chon khong hop le!" << endl;
//                 }
//             } while (scheduleChoice != 0);
//             break;
//         }
//         case 6:
//         {
//             int subjectChoice;
//             do {
//                 cout << "\n===== QUAN LY MON HOC =====" << endl;
//                 cout << "1. Them mon hoc moi" << endl;
//                 cout << "2. Cap nhat thong tin mon hoc" << endl;
//                 cout << "0. Quay lai" << endl;
//                 cout << "Chon chuc nang: ";
//                 if (!ChoiceInput(subjectChoice)) continue;
                
//                 switch(subjectChoice) {
//                     case 1:
//                     {
//                         string subjectName;
//                         int cost;
//                         cout << "Nhap ten mon hoc moi: ";
//                         getline(cin, subjectName);
//                         cout << "Nhap hoc phi: ";
//                         cin >> cost;
//                         cin.ignore();

//                         Subject *newSubject = new Subject(subjectName, cost);
//                         SubjectRecord *t = new SubjectRecord(newSubject, tutor);
//                         program.getSrList().push_back(t);
//                         tutor->AddSubject(newSubject);
//                         FileHandler::AppendSubjectRecordToFile(t);
//                         cout << "Da them mon hoc: " << subjectName << " voi hoc phi: " << cost << endl;
//                         break;
//                     }
//                     case 2:
//                     {
//                         tutor->Show_SubjectList();
//                         int subjectIndex;
//                         cout << "Chon mon hoc can cap nhat (nhap so thu tu): ";
//                         cin >> subjectIndex;
//                         cin.ignore();

//                         if (subjectIndex >= 1 && subjectIndex <= tutor->getSubjectList().getSize())
//                         {
//                             Subject *subject = tutor->getSubjectList()[subjectIndex - 1]->GetSubject();
//                             subject->Update_SubjectInfo();
//                         }
//                         else
//                         {
//                             cout << "So thu tu khong hop le!" << endl;
//                         }
//                         break;
//                     }
//                     case 0:
//                         break;
//                     default:
//                         cout << "Lua chon khong hop le!" << endl;
//                 }
//             } while (subjectChoice != 0);
//             break;
//         }
//         case 7:
//         {
//             cout << "Diem danh gia hien tai: " << tutor->GetRating() << "/5" << endl;
//             cout << "So luot danh gia: " << tutor->GetNumOfRatings() << endl;
//             break;
//         }
//         case 0:
//             cout << "Dang xuat..." << endl;
//             break;
//         default:
//             cout << "Lua chon khong hop le!" << endl;
//         }

//         if (choice != 0)
//         {
//             cout << "\nNhan Enter de tiep tuc...";
//             cin.get();
//         }
//     } while (choice != 0);
// }

// int main()
// {
//     Program program;
//     int mainChoice;
//     cout << "CHUONG TRINH QUAN LY GIA SU - KHOI TAO THANH CONG!" << endl;

//     do
//     {
//         cout << "\n===== MENU CHINH =====" << endl;
//         cout << "1. Dang nhap" << endl;
//         cout << "2. Dang ky tai khoan moi" << endl;
//         cout << "3. Thoat" << endl;
//         cout << "Chon chuc nang: ";
//         if (!ChoiceInput(mainChoice))
//             continue;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         switch (mainChoice)
//         {
//         case 1:
//         {
//             string id, password;
//             cout << "Nhap ID: ";
//             getline(cin, id);
//             cout << "Nhap mat khau: ";
//             getline(cin, password);

//             User *user = program.LoginUser(id, password);
//             if (user != nullptr)
//             {
//                 if (user->GetRole() == "Hoc sinh")
//                 {
//                     Student *student = dynamic_cast<Student *>(user);
//                     if (student) displayStudentMenu(student, program);
//                 }
//                 else if (user->GetRole() == "Gia su")
//                 {
//                     Tutor *tutor = dynamic_cast<Tutor *>(user);
//                     if (tutor) displayTutorMenu(tutor, program);
//                 }
//             }
//             break;
//         }
//         case 2:
//             program.RegisterNewUser();
//             break;
//         case 3:
//             cout << "Cam on ban da su dung dich vu! Tam biet!" << endl;
//             program.SaveAllData();
//             break;
//         default:
//             cout << "Lua chon khong hop le!" << endl;
//         }
//     } while (mainChoice != 3);
    
//     return 0;
// }