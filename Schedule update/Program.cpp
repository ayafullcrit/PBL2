#include "Program.h"
#include "Tutor.h"
#include "SubjectRecord.h"
#include "Schedule.h"
#include "FileHandler.h"
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
unordered_map<string, Tutor *> Program::ttid;
unordered_map<string, Student *> Program::stdid;
unordered_map<string, SubjectRecord *> Program::sbjid;
bool Program::DataLoaded = 0;
bool IntInput(int &a)
{
    cin >> a;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vui long nhap so hop le!" << endl;
        return 0;
    }
    if (a < 0)
    {
        cout << "Vui long nhap so hop le!" << endl;
        return 0;
    }

    return 1;
}
void normalize_string(string &t)
{
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
    cin >> data.ID;
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
        getline(cin, data.Role);
        if (data.Role == "Gia su")
            data.Role = "Tutor";
        else if (data.Role == "Hoc vien")
            data.Role = "Student";
        else
            cout << "Vai tro khong hop le! Vui long chon Gia su hoac Hoc vien!" << endl;
    } while (data.Role != "Tutor" && data.Role != "Student");
    cout << "Nhap ten: ";
    getline(cin, data.Name);
    normalize_string(data.Name);
    cout << "Nhap mat khau: ";
    getline(cin, data.Password);
    cout << "Nhap dia chi: ";
    getline(cin, data.Location);
    normalize_string(data.Location);
    if (data.Role == "Student")
    {
        cout << "Nhap cap hoc (1-12): ";
        if (!IntInput(data.GradeLevel))
            return 0;
    }
    else if (data.Role == "Tutor")
    {
        cout << "Nhap so mon hoc day: ";
        IntInput(data.subjectCount);
        cin.ignore();
        for (int i = 0; i < data.subjectCount; ++i)
        {
            string subject;
            string ID = GenID();
            int cost;
            cout << "-Nhap ten mon hoc thu " << (i + 1) << ": ";
            getline(cin, subject);
            normalize_string(subject);
            cout << "-Nhap hoc phi cho mon " << subject << " : ";
            IntInput(cost);
            data.Subjects.push_back(new Subject(subject, cost));
            cin.ignore();
        }
    }
    if (!ValidateRegisData(data))
        return 0;
    if (data.Role == "Student")
    {
        Student *newStudent = new Student(data.ID, data.Name, data.Location, data.Password, data.Balance, data.GradeLevel);
        //  tempstd = tempstd;
        StudentList.push_back(newStudent);
        UserList.push_back(static_cast<User *>(newStudent));
        this->getStdId()[data.ID] = newStudent;
        FileHandler::AppendStudentToFile(newStudent);
    }
    else if (data.Role == "Tutor")
    {
        Tutor *newTutor = new Tutor(data.ID, data.Name, data.Location, data.Password, data.Balance, data.subjectCount);
        this->getTutorId()[data.ID] = newTutor;
        for (int i = 0; i < data.Subjects.getSize(); ++i)
        {
            //  cout << data.Subjects[i]->GetName() << endl;
            newTutor->AddSubject(data.Subjects[i]);
            SubjectRecord *sr = new SubjectRecord(data.Subjects[i], newTutor);
            srList.push_back(sr);
            this->getSbjId()[sr->GetID()] = sr;
            FileHandler::AppendSubjectRecordToFile(sr);
        }
        TutorList.push_back(newTutor);
        UserList.push_back(static_cast<User *>(newTutor));
        FileHandler::AppendTutorToFile(newTutor);
    }
    // FileHandler::SaveAllData();
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
Schedule* Program::GetScheduleByID(const string& id) {
    for (int i = 0; i < ScheduleList.getSize(); ++i) {
        if (ScheduleList[i]->GetID() == id) {
            return ScheduleList[i];
        }
    }
    return nullptr;
}
void Program::LoadData()
{
    DataLoaded = 1;
    FileHandler::LoadTutors();
    FileHandler::LoadStudents();
    // cout << "Loaded!";
    // MyVector<SubjectRecord *> subjectRecords; // Temporary, not stored
    FileHandler::LoadSubjectRecords();
    FileHandler::LoadSchedules();
    // cout << "??";
}
void Program::SaveAllData()
{
    FileHandler::SaveAllData();
}
Tutor *Program::LoginTutor(const string &id, const string &password)
{
    Tutor *tutor = GetTutorByID(id);
    // cout << tutor->GetPassword() << ' ' << password << endl;
    if (tutor != nullptr)
    {
        if (tutor->Authenticate(password))
        {
            cout << "Dang nhap thanh cong! Chao mung Gia su " << tutor->GetName() << endl;
            cout << "ID: " << tutor->GetID() << endl;
            return tutor;
        }
        else
        {
            cout << "Mat khau khong dung!" << endl;
            return nullptr;
        }
    }
   // cout << "Khong tim thay gia su voi ID nay!" << endl;
    return nullptr;
}
Student *Program::LoginStudent(const string &id, const string &password)
{
    Student *student = GetstdByID(id);
    if (student != nullptr)
    {
        if (student->Authenticate(password))
        {
            cout << "Dang nhap thanh cong! Chao mung Hoc sinh " << student->GetName() << endl;
            return student;
        }
        else
        {
            cout << "Mat khau khong dung!" << endl;
            return nullptr;
        }
    }
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
    if(!student && !tutor)
    {
        cout << "Khong tim thay nguoi dung voi ID " << id << endl;
        return nullptr; 
    }   
    cout << "ID hoac mat khau khong dung!" << endl;
    return nullptr;
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
void Program::FindTutor(Student *student)
{
    if (TutorList.getSize() == 0)
    {
        cout << "Hien tai chua co gia su nao trong he thong!" << endl;
        return;
    }

    int choice;
    do
    {
        cout << "\n===== TIM KIEM GIA SU =====" << endl;
        cout << "1. Hien thi tat ca gia su" << endl;
        cout << "2. Tim kiem theo ten" << endl;
        cout << "3. Tim kiem theo mon hoc" << endl;
        cout << "4. Tim kiem theo dia chi" << endl;
        cout << "5. Quay lai" << endl;
        cout << "Chon chuc nang: ";
        if (!IntInput(choice))
        {
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
            continue;
        }
        MyVector<Tutor *> searchResults;

        switch (choice)
        {
        case 1:
        {
            // Hiển thị tất cả gia sư
            DisplayTutors(TutorList);
            searchResults = TutorList;
            break;
        }
        case 2:
        {
            cout << "Nhap ten gia su can tim: ";
            string name;
            cin.ignore();
            getline(cin, name);

            for (int i = 0; i < TutorList.getSize(); ++i)
            {
                if (TutorList[i]->GetName().find(name) != string::npos)
                {
                    searchResults.push_back(TutorList[i]);
                }
            }

            if (searchResults.getSize() == 0)
            {
                cout << "Khong tim thay gia su nao voi ten: " << name << endl;
                break;
            }

            cout << "\n=== KET QUA TIM KIEM ===" << endl;
            DisplayTutors(searchResults);
            break;
        }
        case 3:
        {
            cout << "Nhap ten mon hoc can tim: ";
            string subject;
            cin.ignore();
            getline(cin, subject);

            for (int i = 0; i < TutorList.getSize(); ++i)
            {
                Tutor *tutor = TutorList[i];
                MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

                for (int j = 0; j < subjectList.getSize(); ++j)
                {
                    if (subjectList[j]->GetSubject()->GetName().find(subject) != string::npos)
                    {
                        searchResults.push_back(tutor);
                        break;
                    }
                }
            }

            if (searchResults.getSize() == 0)
            {
                cout << "Khong tim thay gia su nao day mon: " << subject << endl;
                break;
            }

            cout << "\n=== KET QUA TIM KIEM ===" << endl;
            for (int i = 0; i < searchResults.getSize(); ++i)
            {
                cout << "\n--- Gia su " << i + 1 << " ---" << endl;
                cout << "ID: " << searchResults[i]->GetID() << endl;
                cout << "Ten: " << searchResults[i]->GetName() << endl;
                cout << "Dia chi: " << searchResults[i]->GetLocation() << endl;
                cout << "Danh gia: " << searchResults[i]->GetRating() << "/5" << endl;

                // Hiển thị môn học phù hợp
                MyVector<SubjectRecord *> &subjectList = searchResults[i]->getSubjectList();
                cout << "Mon hoc: ";
                for (int j = 0; j < subjectList.getSize(); ++j)
                {
                    if (subjectList[j]->GetSubject()->GetName().find(subject) != string::npos)
                    {
                        cout << subjectList[j]->GetSubject()->GetName();
                        if (j < subjectList.getSize() - 1)
                            cout << ", ";
                    }
                }
                cout << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Nhap dia chi can tim: ";
            string location;
            cin.ignore();
            getline(cin, location);

            for (int i = 0; i < TutorList.getSize(); ++i)
            {
                if (TutorList[i]->GetLocation().find(location) != string::npos)
                {
                    searchResults.push_back(TutorList[i]);
                }
            }

            if (searchResults.getSize() == 0)
            {
                cout << "Khong tim thay gia su nao o dia chi: " << location << endl;
                break;
            }

            cout << "\n=== KET QUA TIM KIEM ===" << endl;
            DisplayTutors(searchResults);
            break;
        }
        case 5:
            return;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }

        // Nếu có kết quả tìm kiếm, cho phép học sinh chọn để thêm vào danh sách
        if (searchResults.getSize() > 0 && choice != 5)
        {
            cout << "\nBan co muon them gia su vao danh sach cua minh? (y/n): ";
            string addChoice;
            if (choice == 1)
                cin.ignore();
            cin >> addChoice;

            if (addChoice != "y" && addChoice != "Y" && addChoice != "n" && addChoice != "N")
            {
                cout << "Lua chon khong hop le";
                continue;
            }
            if (addChoice != "y" && addChoice != "Y")
                continue;
            cout << "Chon gia su theo so thu tu (1-" << searchResults.getSize() << "): ";
            int tutorChoice;
            if (!IntInput(tutorChoice))
                continue;

            // cin.ignore();
            if (tutorChoice < 1 || tutorChoice > searchResults.getSize())
            {
                cout << "Lua chon khong hop le!" << endl;
                continue;
            }
            Tutor *selectedTutor = searchResults[tutorChoice - 1];
            MyVector<SubjectRecord *> &subjectList = selectedTutor->getSubjectList();
            // show subject list
            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                Subject *subject = subjectList[j]->GetSubject();
                cout << j + 1 << "." << subject->GetName() << " (Hoc phi: " << subject->GetCost() << " VND)" << endl;
            }
            cout << "Chon mon hoc muon them: ";
            int subjectchoice;
            if (!IntInput(subjectchoice))
                continue;
            if (subjectchoice < 1 || subjectchoice > subjectList.getSize())
                continue;
            // check exist
            SubjectRecord *selectedSubject = subjectList[subjectchoice - 1];
            bool ExistTutor = false, ExistSubject = false;
            MyVector<Tutor *> &studentTutors = student->GetTutorList();
            MyVector<Subject *> &studentSubject = student->GetSubjectList();
            for (int i = 0; i < studentTutors.getSize(); ++i)
            {
                if (studentTutors[i]->GetID() == selectedTutor->GetID())
                {
                    ExistTutor = true;
                    break;
                }
            }
            if (ExistTutor)
            {
                for (int i = 0; i < studentSubject.getSize(); i++)
                {
                    if (selectedSubject->GetID() == studentSubject[i]->GetID())
                    {
                        ExistSubject = true;
                        break;
                    }
                }
            }
            if (ExistSubject)
            {
                cout << "Da co mon " << selectedSubject->GetSubject()->GetName() << " cua giao vien"
                     << selectedTutor->GetName() << "!" << endl;
                continue;
            }
            selectedTutor->addStudentToSubject(student, subjectList[subjectchoice - 1]->GetSubject());
            FileHandler::SaveAllData();
            cout << "Da them gia su " << selectedTutor->GetName() << " vao danh sach!" << endl;
            cout << "------------------------" << endl;
        }

        if (choice != 5)
        {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }
    } while (choice != 5);
}
void Program::CreateSchedule(Student* student, Tutor* tutor, SubjectRecord* subjectRecord) {
    if (!student || !tutor || !subjectRecord) {
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
    Schedule* newSchedule = new Schedule(scheduleID, date, startTime, endTime, 
                                        "pending", subjectRecord, student, tutor, 
                                        location, notes);
    
    if (CheckScheduleConflict(*newSchedule)) {
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
void Program::ViewStudentSchedule(const string& studentID) {
    Student* student = GetstdByID(studentID);
    if (!student) {
        cout << "Khong tim thay hoc sinh!" << endl;
        return;
    }
    
    student->ViewWeeklySchedule();
}
void Program::ViewTutorSchedule(const string& tutorID) {
    Tutor* tutor = GetTutorByID(tutorID);
    if (!tutor) {
        cout << "Khong tim thay gia su!" << endl;
        return;
    }
    
    tutor->ViewTeachingSchedule();
}
bool Program::CheckScheduleConflict(const Schedule& newSchedule) {
    for (int i = 0; i < ScheduleList.getSize(); ++i) {
        if (ScheduleList[i]->IsTimeConflict(newSchedule)) {
            return true;
        }
    }
    return false;
}
void Program::MarkAttendance(Schedule* schedule, bool attended, const string& notes) {
    if (!schedule) return;
    
    schedule->SetAttendance(attended);
    schedule->SetNotes(notes);
    
    if (attended) {
        schedule->UpdateStatus("completed");
        cout << "Da diem danh thanh cong!" << endl;
        
        //ProcessSchedulePayment(schedule);
    } else {
        cout << "Da danh dau la vang mat!" << endl;
    }
    
    FileHandler::SaveSchedules();
}
Program::~Program()
{
}