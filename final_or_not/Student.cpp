#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "Student.h"
#include "Tutor.h"
#include "Subject.h"
#include "FileHandler.h"
#include "Screen.h"
#include "Schedule.h"
Student::Student(const string &id, const string &name, const string &location, const string &pass,
                 const string &phoneNumber, const int &balance, const int &grade, const int &sbjlist
                 , const int &ttlist)
    : User(id, name, location, pass, phoneNumber, balance), GradeLevel(grade), SubjectList(sbjlist),
      TutorList(ttlist) {
          // cout << "Tutor constructor is called!" << endl;
      };
Student::Student(const Student &other)
    : User(other)
{
    SubjectList = MyVector<Subject *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new Subject(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }
    TutorList = MyVector<Tutor *>(other.TutorList.getSize());
    for (int i = 0; i < other.TutorList.getSize(); ++i)
    {
        if (other.TutorList[i] != nullptr)
            TutorList.push_back(new Tutor(*other.TutorList[i]));
        else
            TutorList.push_back(nullptr);
    }
}
Student::~Student()
{
    // for (int i = 0; i < SubjectList.getSize(); ++i)
    // {
    //     Subject *subj = SubjectList[i];
    //     delete subj;
    // }

    // Giải phóng từng Tutor* trong danh sách
    // for (int i = 0; i < TutorList.getSize(); ++i)
    // {
    //     Tutor *t = TutorList[i];
    //     delete t;
    // }
}
void Student::DisplayInfo() const
{

    int x = 10, y = 5;
    int contentY = y + 4;
    int labelX = x + 3;
    int valueX = x + 24;
    this->User::DisplayInfo();
    SetWordColor(10);
    gotoXY(labelX, contentY + 6);
    cout << "Lop             :";
    SetWordColor(15);
    gotoXY(valueX, contentY + 6);
    cout << GradeLevel;
}
void Student::AddSubject(Subject *NewSubject)
{
    //   cout << "Da them mon " << NewSubject->GetName() << " thanh cong!\n";
    this->SubjectList.push_back(NewSubject);
    //  FileHandler::SaveStudents();
}
void Student::AddTutor(Tutor *NewTutor)
{
    // cout << "Da them giao vien " << NewTutor->GetName() << endl;
    this->TutorList.push_back(NewTutor);
    // FileHandler::SaveStudents();
}
void Student::Show_SubjectList()
{
    cout << "Danh sach cac mon hoc dang theo hoc:\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << i + 1 << '.';
        cout << "Mon " << SubjectList[i]->GetName() << " ,";
        cout << "Giao vien: " << TutorList[i]->GetName() << endl;
    }
}
void Student::Show_TutorList()
{
    cout << "Danh sach cac giao vien dang theo hoc:\n";
    for (int i = 0; i < this->TutorList.getSize(); i++)
    {
        cout << i + 1 << "." << TutorList[i]->GetName() << endl;
    }
}
void Student::PayCost(Subject &sbj)
{
    if (this->UserBalance >= sbj.GetCost())
    {
        this->Withdraw(sbj.GetCost());
        cout << "Da thanh toan " << sbj.GetCost() << " cho mon " << sbj.GetName() << endl;
    }
    else
    {
        cout << "So du khong du de thanh toan mon " << sbj.GetName() << endl;
    }
}
Student &Student::operator=(const Student &other)
{
    if (this == &other)
        return *this;

    User::operator=(other); // Gọi toán tử gán của lớp cơ sở User

    GradeLevel = other.GradeLevel;

    // Giải phóng bộ nhớ hiện tại của SubjectList
    for (int i = 0; i < SubjectList.getSize(); ++i)
    {
        delete SubjectList[i];
    }
    SubjectList = MyVector<Subject *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new Subject(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }

    // Giải phóng bộ nhớ hiện tại của TutorList
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        delete TutorList[i];
    }
    TutorList = MyVector<Tutor *>(other.TutorList.getSize());
    for (int i = 0; i < other.TutorList.getSize(); ++i)
    {
        if (other.TutorList[i] != nullptr)
            TutorList.push_back(new Tutor(*other.TutorList[i]));
        else
            TutorList.push_back(nullptr);
    }

    return *this;
}
void Student::Rating(Tutor *tutor, const double rating)
{ // Tính điểm trung bình mới
    double currentTotal = tutor->GetRating() * tutor->GetNumOfRatings();
    double newTotal = currentTotal + rating;
    int newNumRatings = tutor->GetNumOfRatings() + 1;
    double newRating = newTotal / newNumRatings;

    // Cập nhật đánh giá
    tutor->SetRating(newRating);
    tutor->SetNumOfRatings(newNumRatings);

    FileHandler::SaveTutors();
}
void Student::AddSchedule(Schedule *schedule)
{
    studentSchedules.push_back(schedule);
}

void Student::ViewWeeklySchedule() const
{
}
void Student::RequestScheduleChange(Schedule *schedule, const string &newTime)
{
    if (!schedule)
        return;

    cout << "Gui yeu cau doi lich hoc..." << endl;
    cout << "Lich hien tai: " << schedule->GetDate() << " " << schedule->GetStartTime() << endl;
    cout << "Thoi gian moi: " << newTime << endl;

    // Trong thực tế, sẽ gửi thông báo cho gia sư
    // Ở đây chỉ cập nhật tạm
    schedule->SetNotes("Yeu cau doi lich: " + newTime);
    cout << "Da gui yeu cau doi lich cho gia su!" << endl;
}