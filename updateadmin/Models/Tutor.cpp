#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "../Utility/Screen.h"
#include "Tutor.h"
#include "Student.h"
#include "Subject.h"
#include "SubjectRecord.h"
#include "../Utility/FileHandler.h"
#include "Schedule.h"
#include "../Utility/Program.h"
Tutor::Tutor(const string &id, const string &name, const string &location, const string &pass,
             const string &phoneNumber, const bool &approved, const int &balance, const int &sbjlist,
             const double &rating, const int &numrating)
    : User(id, name, location, pass, phoneNumber, balance), approved(approved), SubjectList(sbjlist), Rating(rating),
      NumOfRatings(numrating) {
          // cout << "Tutor constructor is called!" << endl;
      };
Tutor::Tutor(const Tutor &other)
    : User(other)
{
    SubjectList = MyVector<SubjectRecord *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new SubjectRecord(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }
};
Tutor::~Tutor() {
    // for (int i = 0; i < SubjectList.getSize(); ++i)
    // {
    //     SubjectRecord *subjRec = SubjectList[i];
    //     delete subjRec;
    // }
};
void Tutor::DisplayInfo() const
{
    int x = 10, y = 5;
    int contentY = y + 4;
    int labelX = x + 3;
    int valueX = x + 24;
    this->User::DisplayInfo();
    SetWordColor(10);
    gotoXY(labelX, contentY + 7);
    cout << "Danh gia        :";
    gotoXY(valueX, contentY + 7);
    SetWordColor(15);
    if (this->NumOfRatings == 0)
    {
        cout << "Chua co danh gia" << endl;
    }
    else
        cout << this->Rating / this->NumOfRatings << " (" << this->NumOfRatings << " danh gia)" << endl;
}
void Tutor::AddSubject(Subject *NewSubject)
{
    //  cout << "Da them mon " << NewSubject.GetName() << "!" << endl;
    SubjectRecord *newSubjRec = new SubjectRecord(NewSubject, this);
    this->SubjectList.push_back(newSubjRec);
    // FileHandler::SaveTutors();
}
void Tutor::AddSubject(const string &subjectName)
{
    Subject *subject = new Subject(subjectName);
    AddSubject(subject);
}
void Tutor::addStudentToSubject(Student *NewStudent, string subjectID)
{
    if (!NewStudent)
        return;
    for (int i = 0; i < this->SubjectList.getSize(); ++i)
    {
        SubjectRecord *rec = this->SubjectList[i];
        if (!rec)
            continue;
        Subject *subj = rec->GetSubject();
        if (!subj)
            continue;
        if (subj->GetID() == subjectID)
        {
            // cout << "Exist!" << endl;
            MyVector<Student *> &students = rec->GetStudentList();
            bool exists = false;
            for (int j = 0; j < students.getSize(); ++j)
                if (students[j]->GetID() == NewStudent->GetID())
                {
                    exists = true;
                    break;
                }
            if (!exists)
            {
                rec->AddStudent(NewStudent);
                // cout << "Added 1" << endl;
                NewStudent->AddTutor(this);
                // cout << "Added 2" << endl;
                NewStudent->AddSubject(subj);
                //  cout << "Added 3" << endl;
            }
            return;
        }
    }
    cout << "Khong tim thay mon co ID: " << subjectID << '\n';
}
void Tutor::Show_StudentList()
{
    cout << "Danh sach hoc sinh cua giao vien " << this->GetName() << ":\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << "Mon hoc: " << SubjectList[i]->GetSubject()->GetName() << endl;
        SubjectList[i]->ShowStudentList();
    }
}
void Tutor::Show_SubjectList()
{
    cout << "Danh sach cac mon hoc cua giao vien " << this->GetName() << ":\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << i + 1 << "." << SubjectList[i]->GetSubject()->GetName() << endl;
    }
}
void Tutor::DeleteStudent(Student *std)
{
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        SubjectRecord *subjRec = this->SubjectList[i];
        if (!subjRec)
            continue;
        MyVector<Student *> &studentList = subjRec->GetStudentList();
        for (int j = 0; j < studentList.getSize(); ++j)
        {
            if (studentList[j] && studentList[j]->GetID() == std->GetID())
            {
                studentList.removeAt(j);
                cout << "Da xoa hoc sinh " << std->GetName() << " khoi mon " << (subjRec->GetSubject() ? subjRec->GetSubject()->GetName() : string("(unknown)")) << endl;
                return;
            }
        }
    }
}
SubjectRecord *Tutor::operator[](int index)
{
    if (index < 0 || index >= this->SubjectList.getSize())
    {
        throw out_of_range("Index out of range in Tutor::operator[]");
    }
    return this->SubjectList[index];
}
Tutor &Tutor::operator=(const Tutor &other)
{
    if (this == &other)
        return *this;
    User::operator=(other);
    this->Rating = other.Rating;
    this->NumOfRatings = other.NumOfRatings;
    // Deep copy of SubjectList
    for (int i = 0; i < this->SubjectList.getSize(); ++i)
    {
        delete this->SubjectList[i];
    }
    this->SubjectList = MyVector<SubjectRecord *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            this->SubjectList.push_back(new SubjectRecord(*other.SubjectList[i]));
        else
            this->SubjectList.push_back(nullptr);
    }

    return *this;
}
void Tutor::AddSchedule(Schedule *schedule)
{
    tutorSchedules.push_back(schedule);
}

void Tutor::ViewTeachingSchedule() const
{
    cout << "\n===== LICH DAY CUA GIA SU " << this->GetName() << " =====" << endl;

    if (tutorSchedules.getSize() == 0)
    {
        cout << "Chua co lich day nao!" << endl;
        return;
    }

    MyVector<Schedule *> sortedSchedules = tutorSchedules;

    for (int i = 0; i < sortedSchedules.getSize(); ++i)
    {
        Schedule *schedule = sortedSchedules[i];
        cout << "\n--- Buoi " << i + 1 << " ---" << endl;
        cout << "Ngay: " << schedule->GetDate() << endl;
        cout << "Gio: " << schedule->GetStartTime() << " - " << schedule->GetEndTime() << endl;
        cout << "Mon hoc: " << (schedule->GetSubjectRecord() ? schedule->GetSubjectRecord()->GetSubject()->GetName() : "Khong xac dinh") << endl;
        cout << "Hoc sinh: " << (schedule->GetStudent() ? schedule->GetStudent()->GetName() : "Khong xac dinh") << endl;
        cout << "Trang thai: " << schedule->GetStatus() << endl;
        cout << "Dia diem: " << schedule->GetLocation() << endl;

        if (!schedule->GetNotes().empty())
        {
            cout << "Ghi chu: " << schedule->GetNotes() << endl;
        }
    }
}

bool Tutor::IsTimeAvailable(const string &date, const string &time) const
{

    for (int i = 0; i < tutorSchedules.getSize(); ++i)
    {
        Schedule *existingSchedule = tutorSchedules[i];
        if (existingSchedule->GetDate() == date)
        {

            if (existingSchedule->IsTimeConflict(*existingSchedule))
            {
                return false;
            }
        }
    }
    return true;
}

void Tutor::ConfirmSchedule(Schedule *schedule)
{
    if (!schedule)
        return;

    schedule->UpdateStatus("confirmed");
    cout << "Da xac nhan lich hoc!" << endl;
    cout << "Thong tin lich hoc:" << endl;
    schedule->DisplayScheduleInfo();
}

void Tutor::CancelSchedule(Schedule *schedule, const string &reason)
{
    if (!schedule)
        return;

    schedule->UpdateStatus("cancelled");
    schedule->SetNotes("Ly do huy: " + reason);
    cout << "Da huy lich hoc!" << endl;
    cout << "Ly do: " << reason << endl;
}