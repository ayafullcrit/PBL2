#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "Program.h"
#include "../Models/Tutor.h"
#include "../Models/SubjectRecord.h"
#include "../Models/Schedule.h"
#include "FileHandler.h"
#include "Screen.h"
#include "../Models/Schedule.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <time.h>
string TutorDB = "Tutor.txt";
string StudentDB = "Student.txt";
string SubjectRecordDB = "SubjectRecord.txt";
MyVector<Tutor *> Program::TutorList;
MyVector<Student *> Program::StudentList;
MyVector<User *> Program::UserList;
MyVector<Schedule *> Program::ScheduleList;
MyVector<SubjectRecord *> Program::srList;
MyVector<Admin *> Program::AdminList;
unordered_map<string, Tutor *> Program::ttid;
unordered_map<string, Student *> Program::stdid;
unordered_map<string, SubjectRecord *> Program::sbjid;
bool Program::DataLoaded = 0;
void normalize_string(string &t)
{
    if (t.empty())
        return;
    stringstream ss(t);
    string res = "", word;
    while (ss >> word)
    {
        res += toupper(word[0]);
        for (int j = 1; j < word.size(); j++)
        {
            res += tolower(word[j]);
        }
        res += " ";
    }
    if (!res.empty())
        res.pop_back();
    t = res;
}
bool ValidateRegisData(RegisData &data)
{
    // check empty
    if (data.ID.empty())
    {
        cout << "ID khong duoc de trong!" << endl;
        return 0;
    }
    if (data.Name.empty())
    {
        cout << "Ten khong duoc de trong!" << endl;
        return 0;
    }
    if (data.Password.empty())
    {
        cout << "Mat khau khong duoc de trong!" << endl;
        return 0;
    }
    if (data.Location.empty())
    {
        cout << "Dia chi khong duoc de trong!" << endl;
        return 0;
    }
    data.Balance = 0;
    if (data.Role.empty())
    {
        cout << "Vai tro khong duoc de trong!" << endl;
        return 0;
    }
    // Role check
    if (data.Role != "Tutor" && data.Role != "Student")
    {
        cout << "Vai tro khong hop le! Vui long chon Gia su hoac Hoc vien!" << endl;
        return 0;
    }
    // specific check
    if (data.Role == "Student")
    {
        if (data.GradeLevel < 1 || data.GradeLevel > 12)
        {
            cout << "Cap hoc khong hop le! Vui long chon cap hoc tu 1 den 12!" << endl;
            return 0;
        }
    }
    if (data.Role == "Tutor")
    {
        if (data.Subjects.getSize() == 0)
        {
            cout << "Gia su phai co it nhat mot mon hoc!" << endl;
            return 0;
        }
    }
    return 1;
}

string Program::GenID()
{
    MyVector<SubjectRecord *> vec = srList;
    srand(time(NULL));
    string id = "";
    bool IsExist = false;
    do
    {
        id = "";
        for (int i = 0; i < 6; ++i)
        {
            id += to_string(rand() % 10);
        }
        // check exist
        for (int i = 0; i < vec.getSize(); ++i)
        {
            if (vec[i]->GetID() == id)
            {
                IsExist = true;
                break;
            }
            IsExist = false;
        }
    } while (IsExist);
    return id;
}
bool Program::RegisterNewUser()
{
    RegisData data;
    cout << "----- Dang ky tai khoan moi -----" << endl;
    cout << "Nhap ID tai khoan: ";
    SetWordColor(15);
    cin >> data.ID;
    SetWordColor(10);
    // check
    bool checkExist = 0;
    for (int i = 0; i < UserList.getSize(); i++)
    {
        if (UserList[i]->GetID() == data.ID)
        {
            checkExist = 1;
        }
    }
    if (checkExist)
    {
        cout << "ID nay da duoc dang ky, vui long nhap ID khac!";
        return 0;
    }
    cin.ignore();
    do
    {
        cout << "Nhap vai tro (Gia su/Hoc vien): ";
        SetWordColor(15);
        getline(cin, data.Role);
        SetWordColor(10);
        if (data.Role == "Gia su")
            data.Role = "Tutor";
        else if (data.Role == "Hoc vien")
            data.Role = "Student";
        else
            cout << "Vai tro khong hop le! Vui long chon Gia su hoac Hoc vien!" << endl;
    } while (data.Role != "Tutor" && data.Role != "Student");
    cout << "Nhap ten: ";
    SetWordColor(15);
    getline(cin, data.Name);
    SetWordColor(10);
    normalize_string(data.Name);
    cout << "Nhap mat khau: ";
    SetWordColor(15);
    getline(cin, data.Password);
    SetWordColor(10);
    cout << "Nhap dia chi: ";
    SetWordColor(15);
    getline(cin, data.Location);
    SetWordColor(10);
    normalize_string(data.Location);
    cout << "Nhap so dien thoai: ";
    SetWordColor(15);
    getline(cin, data.PhoneNumber);
    SetWordColor(10);
    for (int i = 0; i < data.PhoneNumber.size(); i++)
    {
        if (!isdigit(data.PhoneNumber[i]))
        {
            cout << "So dien thoai khong hop le!" << endl;
            return 0;
        }
    }
    if (data.Role == "Student")
    {
        cout << "Nhap cap hoc (1-12): ";
        SetWordColor(15);
        if (!IntInput(data.GradeLevel))
            return 0;
        SetWordColor(10);
    }
    else if (data.Role == "Tutor")
    {
        cout << "Nhap so mon hoc day: ";
        SetWordColor(15);
        if (!IntInput(data.subjectCount))
            return 0;
        SetWordColor(10);
        cin.ignore();
        for (int i = 0; i < data.subjectCount; ++i)
        {
            string subject;
            string ID = GenID();
            int cost;
            cout << "-Nhap ten mon hoc thu " << (i + 1) << ": ";
            SetWordColor(15);
            getline(cin, subject);
            SetWordColor(10);
            normalize_string(subject);
            cout << "-Nhap hoc phi cho mon " << subject << " : ";
            SetWordColor(15);
            if (!IntInput(cost))
                return 0;
            SetWordColor(10);
            data.Subjects.push_back(new Subject(subject, cost));
            cin.ignore();
        }
    }
    if (!ValidateRegisData(data))
        return 0;
    if (data.Role == "Student")
    {
        Student *newStudent = new Student(data.ID, data.Name, data.Location, data.Password,
                                          data.PhoneNumber, data.Balance, data.GradeLevel);
        //  tempstd = tempstd;
        StudentList.push_back(newStudent);
        UserList.push_back(static_cast<User *>(newStudent));
        this->getStdId()[data.ID] = newStudent;
        FileHandler::AppendStudentToFile(newStudent);
    }
    else if (data.Role == "Tutor")
    {
        Tutor *newTutor = new Tutor(data.ID, data.Name, data.Location, data.Password,
                                    data.PhoneNumber, false, data.Balance, data.subjectCount);
        this->getTutorId()[data.ID] = newTutor;
        for (int i = 0; i < data.Subjects.getSize(); ++i)
        {
            newTutor->AddSubject(data.Subjects[i]);
            SubjectRecord *sr = new SubjectRecord(data.Subjects[i], newTutor);
            srList.push_back(sr);
            this->getSbjId()[sr->GetID()] = sr;
            FileHandler::AppendSubjectRecordToFile(sr);
        }
        TutorList.push_back(newTutor);
        UserList.push_back(static_cast<User *>(newTutor));
        FileHandler::AppendTutorToFile(newTutor);
        cout << "Dang ky tai khoan thanh cong!" << "Vui long cho admin duyet" << endl;
        return 1;
    }
    cout << "Dang ky tai khoan thanh cong!" << endl;
    return 1;
}
Program::Program()
{
    if (!DataLoaded)
    {
        LoadData();
        DataLoaded = 1;
    }
}
SubjectRecord *Program::GetsrByID(const string &id)
{
    return sbjid[id];
}
Student *Program::GetstdByID(const string &id)
{
    return stdid[id];
}
Tutor *Program::GetTutorByID(const string &id)
{
    return ttid[id];
}
User *Program::GetUserByID(const string &id)
{
    if (this->GetstdByID(id))
        return dynamic_cast<User *>(this->GetstdByID(id));
    if (this->GetTutorByID(id))
        return dynamic_cast<User *>(this->GetTutorByID(id));
    return nullptr;
}
Schedule *Program::GetScheduleByID(const string &id)
{
    for (int i = 0; i < ScheduleList.getSize(); ++i)
    {
        if (ScheduleList[i]->GetID() == id)
        {
            return ScheduleList[i];
        }
    }
    return nullptr;
}
void Program::LoadData()
{
    DataLoaded = 1;
    // cout << "Go Load Tutor!";
    // _getch();
    FileHandler::LoadTutors();
    // cout << "Tutor Loaded!" << endl;
    // _getch();
    FileHandler::LoadStudents();
    // cout << "Student Loaded!" << endl;
    // _getch();
    FileHandler::LoadSubjectRecords();
    // cout << "Subject Loaded!" << endl;
    // _getch();
    FileHandler::LoadSchedules();
    // cout << "Schedule Loaded!" << endl;
    //  _getch();
    FileHandler::LoadAdmins();
    // cout << "Admin Loaded";
    // _getch();
}
void Program::SaveAllData()
{
    FileHandler::SaveAllData();
}
Tutor *Program::LoginTutor(const string &id, const string &password)
{
    Tutor *tutor = GetTutorByID(id);
    Sleep(1000);
    if (tutor != nullptr)
    {
        if (!tutor->IsApproved())
        {
            SetWordColor(4);
            cout << "Tai khoan nay chua duoc duyet!";
            return nullptr;
        }
        if (tutor->Authenticate(password))
        {
            SetWordColor(10);
            cout << "Dang nhap thanh cong! Chao mung Gia su " << tutor->GetName() << endl;
            return tutor;
        }
        else
        {
            SetWordColor(4);
            cout << "Mat khau khong dung!" << endl;
            return nullptr;
        }
    }
    SetWordColor(4);
    cout << "Khong tim thay gia su voi ID nay!" << endl;
    return nullptr;
}
Student *Program::LoginStudent(const string &id, const string &password)
{
    Student *student = GetstdByID(id);
    Sleep(1000);
    if (student != nullptr)
    {
        if (student->Authenticate(password))
        {
            SetWordColor(10);
            cout << "Dang nhap thanh cong! Chao mung Hoc sinh " << student->GetName() << endl;
            return student;
        }
        else
        {
            SetWordColor(4);
            cout << "Mat khau khong dung!" << endl;
            return nullptr;
        }
    }
    SetWordColor(4);
    cout << "Khong tim thay hoc sinh voi ID nay!" << endl;
    return nullptr;
}
User *Program::LoginUser(const string &id, const string &password)
{
    Tutor *tutor = LoginTutor(id, password);
    if (tutor != nullptr)
    {
        return static_cast<User *>(tutor);
    }

    Student *student = LoginStudent(id, password);
    if (student != nullptr)
    {
        return static_cast<User *>(student);
    }
    if (!student && !tutor)
    {
        cout << "Khong tim thay nguoi dung voi ID " << id << endl;
        return nullptr;
    }
    cout << "ID hoac mat khau khong dung!" << endl;
    return nullptr;
}
void Program::DisplayStudents(MyVector<Student *> v)
{
    for (int i = 0; i < v.getSize(); i++)
    {
        v[i]->DisplayInfo();
    }
}
void Program::DisplayTutors(MyVector<Tutor *> tt)
{
    cout << "\n===== DANH SACH TAT CA GIA SU =====" << endl;
    if (tt.getSize() == 0)
    {
        cout << "Hien tai chua co gia su nao trong he thong!" << endl;
        return;
    }

    for (int i = 0; i < tt.getSize(); ++i)
    {
        Tutor *tutor = tt[i];
        if (tutor == NULL)
            return;
        cout << "\n--- Gia su " << i + 1 << " ---" << endl;
        cout << "Ten: " << tutor->GetName() << endl;
        cout << "Dia chi: " << tutor->GetLocation() << endl;
        cout << "Danh gia: " << tutor->GetRating() << "/5" << endl;
        cout << "So luot danh gia: " << tutor->GetNumOfRatings() << endl;
        // Hiển thị các môn học của gia sư
        cout << "Cac mon hoc:" << endl;
        MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
        for (int j = 0; j < subjectList.getSize(); ++j)
        {
            Subject *subject = subjectList[j]->GetSubject();
            cout << "  - " << subject->GetName() << " (Hoc phi: " << subject->GetCost() << " VND)" << endl;
        }
        cout << "------------------------" << endl;
    }
}

void Program::CreateSchedule(Student *student, Tutor *tutor, SubjectRecord *subjectRecord)
{
    if (!student || !tutor || !subjectRecord)
    {
        cout << "Thong tin khong hop le!" << endl;
        return;
    }

    cout << "\n===== TAO LICH HOC MOI =====" << endl;

    string date, startTime, endTime, location, notes;

    cout << "Nhap ngay hoc (YYYY-MM-DD): ";
    cin >> date;

    cout << "Nhap gio bat dau (HH:MM): ";
    cin >> startTime;

    cout << "Nhap gio ket thuc (HH:MM): ";
    cin >> endTime;

    cin.ignore();
    cout << "Nhap dia diem hoc: ";
    getline(cin, location);

    cout << "Nhap ghi chu (neu co): ";
    getline(cin, notes);

    string scheduleID = GenID();
    Schedule *newSchedule = new Schedule(scheduleID, date, startTime, endTime,
                                         "pending", subjectRecord, student, tutor,
                                         location, notes);

    if (CheckScheduleConflict(*newSchedule))
    {
        cout << "Lich hoc bi trung! Vui long chon thoi gian khac." << endl;
        delete newSchedule;
        return;
    }

    ScheduleList.push_back(newSchedule);
    student->AddSchedule(newSchedule);
    tutor->AddSchedule(newSchedule);

    cout << "Da tao lich hoc thanh cong!" << endl;
    cout << "Lich hoc dang cho gia su xac nhan..." << endl;

    newSchedule->DisplayScheduleInfo();

    FileHandler::AppendScheduleToFile(newSchedule);
}
void Program::ViewStudentSchedule(const string &studentID)
{
    Student *student = GetstdByID(studentID);
    if (!student)
    {
        cout << "Khong tim thay hoc sinh!" << endl;
        return;
    }

    student->ViewWeeklySchedule();
}
void Program::ViewTutorSchedule(const string &tutorID)
{
    Tutor *tutor = GetTutorByID(tutorID);
    if (!tutor)
    {
        cout << "Khong tim thay gia su!" << endl;
        return;
    }

    tutor->ViewTeachingSchedule();
}
bool Program::CheckScheduleConflict(const Schedule &newSchedule)
{
    for (int i = 0; i < ScheduleList.getSize(); ++i)
    {
        if (ScheduleList[i]->IsTimeConflict(newSchedule))
        {
            return true;
        }
    }
    return false;
}
void Program::MarkAttendance(Schedule *schedule, bool attended, const string &notes)
{
    if (!schedule)
        return;

    schedule->SetAttendance(attended);
    schedule->SetNotes(notes);

    if (attended)
    {
        schedule->UpdateStatus("completed");
        cout << "Da diem danh thanh cong!" << endl;

        // ProcessSchedulePayment(schedule);
    }
    else
    {
        cout << "Da danh dau la vang mat!" << endl;
    }

    FileHandler::SaveSchedules();
}
Program::~Program()
{
}