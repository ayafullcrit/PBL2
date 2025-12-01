#include "FileHandler.h"
#include "Program.h"
#include "Admin.h"
const string FileHandler::TUTOR_FILE = "Tutor.txt";
const string FileHandler::STUDENT_FILE = "Student.txt";
const string FileHandler::SUBJECT_RECORD_FILE = "SubjectRecord.txt";
const string FileHandler::SCHEDULE_FILE = "Schedule.txt";
const string FileHandler::ADMIN_FILE = "Admin.txt";
bool FileHandler::LoadAdmins()
{
    Program a;
    ifstream file(ADMIN_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << ADMIN_FILE << endl;
        return false;
    }
    if (file.peek() == ifstream::traits_type::eof())
    {
       // cout << "File " << ADMIN_FILE << " rong." << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location, phoneNumber;
        int balance;
        getline(file, name);
        getline(file, password);
        getline(file, location);
        getline(file, phoneNumber);
        getline(file, line);
        balance = stoi(line);

        // Create Tutor object
        Admin *admin = new Admin(id, name, location, password, phoneNumber);

        a.getAdminList().push_back(admin);

        getline(file, line); // Skip separator
    }

    file.close();
    // cout << "Da tai " << tutors.getSize() << " gia su tu file." << endl;
    return true;
}
bool FileHandler::LoadTutors()
{
    Program a;
    ifstream file(TUTOR_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << TUTOR_FILE << endl;
        return false;
    }
    if (file.peek() == ifstream::traits_type::eof())
    {
       // cout << "File " << TUTOR_FILE << " rong." << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location, phoneNumber;
        int balance, numrating;
        double rating;
        bool approved;
        getline(file, name);
        getline(file, password);
        getline(file, location);
        getline(file, phoneNumber);
        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        rating = stod(line);

        getline(file, line);
        numrating = stoi(line);

        getline(file, line);
        approved = (line == "1");
        // Create Tutor object
        Tutor *tutor = new Tutor(id, name, location, password, phoneNumber, approved, balance, 0, rating);

        a.getTutorId()[id] = tutor;
        a.getTutorList().push_back(tutor);
        a.getUserList().push_back(static_cast<User *>(tutor));

        getline(file, line); // Skip separator
    }

    file.close();
    // cout << "Da tai " << tutors.getSize() << " gia su tu file." << endl;
    return true;
}

bool FileHandler::LoadStudents()
{
    ifstream file(STUDENT_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << STUDENT_FILE << endl;
        return false;
    }
    if (file.peek() == ifstream::traits_type::eof())
    {
        //cout << "File " << STUDENT_FILE << " rong." << endl;
        return false;
    }
    // Program a;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location, phoneNumber;
        int balance, gradeLevel; //, tutorCount, subjectCount;

        getline(file, name);
        getline(file, password);
        getline(file, location);
        getline(file, phoneNumber);

        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        gradeLevel = stoi(line);

        // getline(file, line);
        // tutorCount = stoi(line);
        // Create Student object
        Student *student = new Student(id, name, location, password, phoneNumber, balance, gradeLevel);
        Program a;
        a.getStdId()[id] = student;
        a.getStudentList().push_back(student);
        a.getUserList().push_back(static_cast<User *>(student));

        getline(file, line); // Skip separator
    }

    file.close();
    // cout << "Da tai " << students.getSize() << " hoc sinh tu file." << endl;
    return true;
}

bool FileHandler::LoadSubjectRecords()
{
    ifstream file(SUBJECT_RECORD_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << SUBJECT_RECORD_FILE << endl;
        return false;
    }

    string line;
    string subjectID, tutorID, studentID, subjectName, costStr, studentCountStr;
    Program a;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        subjectID = line;
        getline(file, subjectName);
        getline(file, costStr);
        getline(file, tutorID);
        getline(file, studentCountStr);
        int cost = stoi(costStr);
        int studentCount = stoi(studentCountStr);
        Tutor *tutor = a.GetTutorByID(tutorID);
        Subject *newSubject = new Subject(subjectName, cost, subjectID);
        tutor->AddSubject(newSubject);
        SubjectRecord *newSr = tutor->getSubjectList()[tutor->getSubjectList().getSize() - 1];
        for (int i = 0; i < studentCount; i++)
        {
            getline(file, line);
            Student *curstd = a.GetstdByID(line);
            tutor->addStudentToSubject(curstd, newSubject);
        }
        a.getSbjId()[subjectID] = newSr;
        a.getSrList().push_back(newSr);
        getline(file, line); // Skip separator
    }
    // cout << "Before closing file" << endl;
    file.close();
    // cout << "After closing file" << endl;
    return true;
}
bool FileHandler::LoadSchedules()
{
    Program a;
    ifstream file(SCHEDULE_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << SCHEDULE_FILE << " hoac file chua duoc tao!" << endl;
        return false;
    }

    if (file.peek() == ifstream::traits_type::eof())
    {
      //  cout << "File " << SCHEDULE_FILE << " rong." << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string scheduleID = line;
        string date, startTime, endTime, status, location, notes;
        string studentID, tutorID, subjectRecordID;
        bool attendance;

        getline(file, date);
        getline(file, startTime);
        getline(file, endTime);
        getline(file, status);
        getline(file, location);
        getline(file, notes);
        getline(file, studentID);
        getline(file, tutorID);
        getline(file, subjectRecordID);
        getline(file, line);
        attendance = (line == "1");

        // Tìm các đối tượng liên quan
        Student *student = a.GetstdByID(studentID);
        Tutor *tutor = a.GetTutorByID(tutorID);
        SubjectRecord *subjectRecord = a.GetsrByID(subjectRecordID);

        if (student && tutor && subjectRecord)
        {
            Schedule *schedule = new Schedule(scheduleID, date, startTime, endTime, status,
                                              subjectRecord, student, tutor, location, notes, attendance);
            a.getScheduleList().push_back(schedule);
            student->GetSchedules().push_back(schedule);
            tutor->GetSchedules().push_back(schedule);
        }

        getline(file, line); // Skip separator
    }

    file.close();
    cout << "Da tai " << a.getScheduleList().getSize() << " lich hoc tu file." << endl;
    return true;
}
bool FileHandler::SaveTutors()
{
    Program d;
    MyVector<Tutor *> &tutors = d.getTutorList();
    ofstream file(TUTOR_FILE, ios::trunc);
    if (!file.is_open())
    {
        cout << "Loi: Khong the mo file " << TUTOR_FILE << " de ghi!" << endl;
        return false;
    }

    for (int i = 0; i < tutors.getSize(); ++i)
    {
        Tutor *tutor = tutors[i];
        if(tutor == nullptr) continue;
        file << tutor->GetID() << endl;
        file << tutor->GetName() << endl;
        file << tutor->GetPassword() << endl;
        file << tutor->GetLocation() << endl;
        file << tutor->GetPhoneNumber() << endl;
        file << tutor->GetBalance() << endl;
        file << tutor->GetRating() << endl;
        file << tutor->GetNumOfRatings() << endl;
        file << (tutor->IsApproved() ? "1" : "0") << endl;
        file << "_______" << endl;
    }

    file.close();
    return true;
}

bool FileHandler::SaveStudents()
{
    Program d;
    MyVector<Student *> &students = d.getStudentList();
   // cout << d.getStudentList()[0]->GetGradeLevel() << endl;
    ofstream file(STUDENT_FILE, ios::trunc);
    if (!file.is_open())
    {
        cout << "Loi: Khong the mo file " << STUDENT_FILE << " de ghi!" << endl;
        return false;
    }

    for (int i = 0; i < students.getSize(); ++i)
    {
        Student *student = students[i];
        if(student == nullptr) continue;
        file << student->GetID() << endl;
        file << student->GetName() << endl;
        file << student->GetPassword() << endl;
        file << student->GetLocation() << endl;
        file << student->GetPhoneNumber() << endl;
        file << student->GetBalance() << endl;
        file << student->GetGradeLevel() << endl;
        file << "_______" << endl;
    }

    file.close();
    // cout << "Da luu " << students.getSize() << " hoc sinh vao file." << endl;
    return true;
}

bool FileHandler::SaveSubjectRecords()
{
    Program d;
    MyVector<Tutor *> &tutors = d.getTutorList();
    ofstream file(SUBJECT_RECORD_FILE, ios::trunc);
    if (!file.is_open())
    {
        cout << "Loi: Khong the mo file " << SUBJECT_RECORD_FILE << " de ghi!" << endl;
        return false;
    }
    MyVector<SubjectRecord *> subjectList = d.getSrList();
    for (int i = 0; i < subjectList.getSize(); i++)
    {
        if(subjectList[i] == nullptr) continue;
        SubjectRecord *sr = subjectList[i];
        Subject *subject = sr->GetSubject();
        MyVector<Student *> &studentList = sr->GetStudentList();
        file << sr->GetID() << endl;
        file << subject->GetName() << endl;
        file << subject->GetCost() << endl;
        file << sr->GetTutor()->GetID() << endl;
        file << studentList.getSize() << endl;
        for (int k = 0; k < studentList.getSize(); ++k)
        {
            file << studentList[k]->GetID() << endl;
        }
        file << "_______" << endl;
    }

    file.close();
    // cout << "Da luu " << totalRecords << " mon hoc vao file." << endl;
    return true;
}

bool FileHandler::SaveAllData()
{
    bool success = true;
    success &= SaveTutors();
    success &= SaveStudents();
    success &= SaveSubjectRecords();
    success &= SaveSchedules();
    return success;
}

bool FileHandler::AppendTutorToFile(Tutor *tutor)
{
    ofstream file(TUTOR_FILE, ios::app);
    if (!file.is_open())
    {
        return false;
    }

    file << tutor->GetID() << endl;
    file << tutor->GetName() << endl;
    file << tutor->GetPassword() << endl;
    file << tutor->GetLocation() << endl;
    file << tutor->GetPhoneNumber() << endl;
    file << tutor->GetBalance() << endl;
    file << tutor->GetRating() << endl;
    file << 0 << endl; // current 0 rating
    file << 0 << endl; // current not approved
    file << "_______" << endl;

    file.close();
    return true;
}

bool FileHandler::AppendStudentToFile(Student *student)
{
    ofstream file(STUDENT_FILE, ios::app);
    if (!file.is_open())
    {
        return false;
    }

    file << student->GetID() << endl;
    file << student->GetName() << endl;
    file << student->GetPassword() << endl;
    file << student->GetLocation() << endl;
    file << student->GetPhoneNumber() << endl;
    file << student->GetBalance() << endl;
    file << student->GetGradeLevel() << endl;
    file << "_______" << endl;
    file.close();
    return true;
}

bool FileHandler::AppendSubjectRecordToFile(SubjectRecord *subjectRecord)
{
    ofstream file(SUBJECT_RECORD_FILE, ios::app);
    if (!file.is_open())
    {
        return false;
    }

    Subject *subject = subjectRecord->GetSubject();
    MyVector<Student *> &studentList = subjectRecord->GetStudentList();

    file << subjectRecord->GetID() << endl;
    file << subject->GetName() << endl;
    file << subject->GetCost() << endl;
    file << subjectRecord->GetTutor()->GetID() << endl;
    file << studentList.getSize() << endl;

    for (int k = 0; k < studentList.getSize(); ++k)
    {
        file << studentList[k]->GetID() << endl;
    }

    file << "_______" << endl;

    file.close();
    return true;
}
bool FileHandler::SaveSchedules() {
    Program d;
    MyVector<Schedule*> &schedules = d.getScheduleList();
    ofstream file(SCHEDULE_FILE, ios::trunc);
    
    if (!file.is_open()) {
        cout << "Loi: Khong the mo file " << SCHEDULE_FILE << " de ghi!" << endl;
        return false;
    }
    
    for (int i = 0; i < schedules.getSize(); ++i) {
        Schedule* schedule = schedules[i];
        if(schedule == nullptr) continue;
        file << schedule->GetID() << endl;
        file << schedule->GetDate() << endl;
        file << schedule->GetStartTime() << endl;
        file << schedule->GetEndTime() << endl;
        file << schedule->GetStatus() << endl;
        file << schedule->GetLocation() << endl;
        file << schedule->GetNotes() << endl;
        file << (schedule->GetStudent() ? schedule->GetStudent()->GetID() : "") << endl;
        file << (schedule->GetTutor() ? schedule->GetTutor()->GetID() : "") << endl;
        file << (schedule->GetSubjectRecord() ? schedule->GetSubjectRecord()->GetID() : "") << endl;
        file << (schedule->GetAttendance() ? "1" : "0") << endl;
        file << "_______" << endl;
    }
    
    file.close();
    return true;
}

bool FileHandler::AppendScheduleToFile(Schedule* schedule) {
    ofstream file(SCHEDULE_FILE, ios::app);
    if (!file.is_open()) {
        return false;
    }
    
    file << schedule->GetID() << endl;
    file << schedule->GetDate() << endl;
    file << schedule->GetStartTime() << endl;
    file << schedule->GetEndTime() << endl;
    file << schedule->GetStatus() << endl;
    file << schedule->GetLocation() << endl;
    file << schedule->GetNotes() << endl;
    file << (schedule->GetStudent() ? schedule->GetStudent()->GetID() : "") << endl;
    file << (schedule->GetTutor() ? schedule->GetTutor()->GetID() : "") << endl;
    file << (schedule->GetSubjectRecord() ? schedule->GetSubjectRecord()->GetID() : "") << endl;
    file << (schedule->GetAttendance() ? "1" : "0") << endl;
    file << "_______" << endl;
    
    file.close();
    return true;
}
bool FileHandler::ValidateFile(const string &filename)
{
    ifstream file(filename);
    return file.good();
}