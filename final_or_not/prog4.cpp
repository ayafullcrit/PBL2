// #include "Screen.h"
// #include "Tutor.h"
// #include "TutorScreen.h"
// #include "StudentScreen.h"
// #include "FileHandler.h"
// #include "Program.h"
// void Screen_Tutor_7(Tutor *tutor)
// {
//     system("cls");
//     int x = 30, y = 5;
//     int width = 60;      // Chiều rộng của khung
//     int bodyHeight = 10; // Chiều cao của phần thân
//     // 3 dòng cho Header, 3 dòng cho Footer
//     int totalHeight = 3 + bodyHeight + 3;

//     char HL = 205; // ═
//     char ML = 204; // ╠
//     char MR = 185; // ╣

//     // Vẽ khung
//     SetWordColor(14);
//     rectangle(x, y, width, totalHeight);

//     // Vẽ đường phân cách
//     // Dải phân cách Header
//     gotoXY(x, y + 2);
//     cout << ML;
//     for (int i = 0; i < width - 2; i++)
//         cout << HL;
//     gotoXY(x + width - 1, y + 2);
//     cout << MR;

//     // Dải phân cách Footer
//     int footerSeparatorY = y + 2 + bodyHeight + 1;
//     gotoXY(x, footerSeparatorY);
//     cout << ML;
//     for (int i = 0; i < width - 2; i++)
//         cout << HL;
//     gotoXY(x + width - 1, footerSeparatorY);
//     cout << MR;

//     // In nội dung (Màu Vàng Cam)
//     SetWordColor(10);

//     // In tiêu đề (căn giữa)
//     string title = "CAP NHAT MON HOC";
//     gotoXY(x + (width - title.length()) / 2, y + 1);
//     cout << title;

//     // Hiển thị danh sách môn học
//     int contentY = y + 4; // Bắt đầu in từ dòng y + 4
//     int labelX = x + 3;   // Lề trái cho nhãn
//     SetWordColor(10);
//     gotoXY(labelX, contentY);
//     cout << "Danh sach mon hoc:";

//     int index = 1;
//     for (int i = 0; i < tutor->getSubjectList().getSize(); i++)
//     {
//         Subject *subject = tutor->getSubjectList()[i]->GetSubject();
//         gotoXY(labelX, contentY + index);
//         cout << index << ". " << left << setw(20) << subject->GetName() << " - Hoc phi: " << right << setw(10) << subject->GetCost();
//         index++;
//     }

//     // Nhập số thứ tự môn học cần chỉnh sửa
//     int selectedIndex;
//     gotoXY(labelX, contentY + index + 1);
//     cout << "Nhap so thu tu mon hoc can xoa: ";
//     bool valid = IntInput(selectedIndex);
//     if (selectedIndex < 1 || selectedIndex > tutor->getSubjectList().getSize() || !valid)
//     {
//         gotoXY(labelX, contentY + index + 2);
//         SetWordColor(4);
//         cout << "So thu tu khong hop le!";
//         gotoXY(labelX, contentY + index + 3);
//         SetWordColor(4);
//         cout << "An phim bat ky de quay lai menu!";
//         _getch();
//         return;
//     }

//     SubjectRecord *sr = tutor->getSubjectList()[selectedIndex - 1];
//     MyVector<Student*>& studentList = sr->GetStudentList();
//     for(int i = 0; i < studentList.getSize(); i++)
//     {
//         for(int j = 0; j < studentList[i]->GetSubjectList().getSize(); j++)
//         {
//             if(studentList[i]->GetSubjectList()[j]->GetID() == sr->GetID())
//             {
//                 studentList[i]->GetSubjectList().removeAt(j);
//                 studentList[i]->GetTutorList().removeAt(j);
//                 break;
//             }
//         }
//     }
//     cout << "1 delete call!";
//     _getch();
//     Program prg;
//     for (int i = 0; i < prg.getSrList().getSize(); i++)
//     {
//         if (prg.getSrList()[i]->GetID() == sr->GetID())
//         {
//             prg.getSrList().removeAt(i);
//             break;
//         }
//     }
//     cout << "2 delete call!";
//     _getch();
//     tutor->getSubjectList().removeAt(selectedIndex - 1);
//     cout << "3 delete call!";
//     _getch();
//     FileHandler::SaveSubjectRecords();
//     cout << "Delete called!";
//     _getch();
//     // In footer (căn giữa)
//     string footer = "Nhan phim bat ky de quay lai menu...";
//     gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
//     cout << footer;

//     // 5. Reset màu về mặc định
//     SetWordColor(7);
//     _getch();
// }
// int main()
// {
//     SetConsoleOutputCP(437);
//     Program prg;
//     Tutor *tutor = LoginTutor();
//     Screen_Tutor_7(tutor);
//     return 0;
// }