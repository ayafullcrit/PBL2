#include "FileHandler.h"
#include "Admin.h"
const string FileHandler::TUTOR_FILE = "Tutor.txt";
const string FileHandler::STUDENT_FILE = "Student.txt";
const string FileHandler::SUBJECT_RECORD_FILE = "SubjectRecord.txt";

bool FileHandler::LoadTutors()
{
    Admin a;
    ifstream file(TUTOR_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << TUTOR_FILE << endl;
        return false;
    }
    if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "File " << TUTOR_FILE << " rong." << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location;
        int balance, numrating;
        double rating;

        getline(file, name);
        getline(file, password);
        getline(file, location);
        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        rating = stod(line);

        getline(file, line);
        numrating = stod(line);

        // getline(file, line);
        // subjectCount = stoi(line);

        // Create Tutor object
        Tutor *tutor = new Tutor(id, name, location, password, balance, 0, rating);

        // Load SubjectRecord IDs
        // for (int i = 0; i < subjectCount; ++i)
        // {
        //     getline(file, line);
        //     // Create temporary SubjectRecord
        //     Subject *subject = new Subject("Temp Subject", 0, line);
        //     SubjectRecord *sr = new SubjectRecord(subject);
        //     tutor->getSubjectList().push_back(sr);
        // }

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
        cout << "File " << STUDENT_FILE << " rong." << endl;
        return false;
    }
    // Admin a;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location;
        int balance, gradeLevel; //, tutorCount, subjectCount;

        getline(file, name);
        getline(file, password);
        getline(file, location);

        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        gradeLevel = stoi(line);

        // getline(file, line);
        // tutorCount = stoi(line);
        // Create Student object
        Student *student = new Student(id, name, location, password, balance, gradeLevel);
        // cout << tutorCount << endl;
        // Load Tutor IDs
        // for (int i = 0; i < tutorCount; ++i)
        // {
        //     getline(file, line);
        //     Store for later linking
        //     string tutorId = line;
        //     // find tutor in provided tutors list and link
        //     for (int t = 0; t < tutors.getSize(); ++t)
        //     {
        //         if (tutors[t]->GetID() == tutorId)
        //         {
        //             student->GetTutorList().push_back(tutors[t]);
        //             break;
        //         }
        //     }
        // }

        // getline(file, line);
        // subjectCount = stoi(line);

        // // Load Subject IDs
        // for (int i = 0; i < subjectCount; ++i)
        // {
        //     getline(file, line);
        //     // Store for later linking
        // }
        Admin a;
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
    Admin a;
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
        a.getSrList().push_back(newSr);
        getline(file, line); // Skip separator
    }
    // cout << "Before closing file" << endl;
    file.close();
    // cout << "After closing file" << endl;
    return true;
}

bool FileHandler::SaveTutors()
{
    Admin d;
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
        file << tutor->GetID() << endl;
        file << tutor->GetName() << endl;
        file << tutor->GetPassword() << endl;
        file << tutor->GetLocation() << endl;
        file << tutor->GetBalance() << endl;
        file << tutor->GetRating() << endl;
        file << tutor->GetNumOfRatings() << endl;
        // MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
        // file << subjectList.getSize() << endl;

        // for (int j = 0; j < subjectList.getSize(); ++j)
        // {
        //     file << subjectList[j]->GetID() << endl;
        // }

        file << "_______" << endl;
    }

    file.close();
    // cout << "Da luu " << tutors.getSize() << " gia su vao file." << endl;
    return true;
}

bool FileHandler::SaveStudents()
{
    Admin d;
    MyVector<Student *> &students = d.getStudentList();
    ofstream file(STUDENT_FILE, ios::trunc);
    if (!file.is_open())
    {
        cout << "Loi: Khong the mo file " << STUDENT_FILE << " de ghi!" << endl;
        return false;
    }

    for (int i = 0; i < students.getSize(); ++i)
    {
        Student *student = students[i];
        file << student->GetID() << endl;
        file << student->GetName() << endl;
        file << student->GetPassword() << endl;
        file << student->GetLocation() << endl;
        file << student->GetBalance() << endl;
        file << student->GetGradeLevel() << endl;

        // MyVector<Tutor *> &tutorList = student->GetTutorList();
        // file << tutorList.getSize() << endl;

        // for (int j = 0; j < tutorList.getSize(); ++j)
        // {
        //     file << tutorList[j]->GetID() << endl;
        // }

        // MyVector<Subject *> &subjectList = student->GetSubjectList();
        // file << subjectList.getSize() << endl;

        // for (int j = 0; j < subjectList.getSize(); ++j)
        // {
        //     file << subjectList[j]->GetID() << endl;
        // }
        file << "_______" << endl;
    }

    file.close();
    // cout << "Da luu " << students.getSize() << " hoc sinh vao file." << endl;
    return true;
}

bool FileHandler::SaveSubjectRecords()
{
    Admin d;
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
    // int totalRecords = 0;
    // for (int i = 0; i < tutors.getSize(); ++i)
    // {
    //     Tutor *tutor = tutors[i];
    //     MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

    //     for (int j = 0; j < subjectList.getSize(); ++j)
    //     {
    //         SubjectRecord *sr = subjectList[j];
    //         Subject *subject = sr->GetSubject();
    //         MyVector<Student *> &studentList = sr->GetStudentList();

    //         file << sr->GetID() << endl;
    //         file << subject->GetName() << endl;
    //         file << subject->GetCost() << endl;
    //         file << studentList.getSize() << endl;

    //         for (int k = 0; k < studentList.getSize(); ++k)
    //         {
    //             file << studentList[k]->GetID() << endl;
    //         }

    //         totalRecords++;
    //     }
    // }

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
    file << tutor->GetBalance() << endl;
    file << tutor->GetRating() << endl;
    file << 0 << endl; // current 0 rating

    // MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
    // file << subjectList.getSize() << endl;

    // for (int j = 0; j < subjectList.getSize(); ++j)
    // {
    //     file << subjectList[j]->GetID() << endl;
    //     FileHandler::AppendSubjectRecordToFile(subjectList[j]);
    // }

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
    file << student->GetBalance() << endl;
    file << student->GetGradeLevel() << endl;
    file << "0" << endl; // Tutor count
                         //  file << "0" << endl;
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

bool FileHandler::BackupData()
{
    // Implementation for backup
    return true;
}

bool FileHandler::ValidateFile(const string &filename)
{
    ifstream file(filename);
    return file.good();
}