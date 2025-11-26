
class Student;
class Schedule;
#include "MyVector.h"
void ShowStudentMenu(Student *student);
void HandleStudentMenu(Student *student);
void ShowNapTienScreen_4(Student *student);
void ShowDanhSachMonHoc_5(Student *student);
void ShowLichHoc_6(Student *student);
void ScreenDanhGiaTuTor_8(Student *student);
void HandleStudentMenu(Student *student);
void Screen_Student_2(Student *student);
void Screen_Student_3(Student *student);
void Screen_Student_one(Student* student);
void SortSchedulesByTime(MyVector<Schedule *> &schedules);
void FindTutorScreen(Student* student);
void CreateSchedule(Student *student);
Student* LoginStudent();