#include "FileHandler.h"

const string FileHandler::TUTOR_FILE = "Tutor.txt";
const string FileHandler::STUDENT_FILE = "Student.txt";
const string FileHandler::SUBJECT_RECORD_FILE = "SubjectRecord.txt";

bool FileHandler::LoadTutors(MyVector<Tutor *> &tutors, MyVector<User *> &users)
{
    ifstream file(TUTOR_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << TUTOR_FILE << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location;
        int balance, subjectCount;
        double rating;

        getline(file, name);
        getline(file, password);
        getline(file, location);

        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        rating = stod(line);

        getline(file, line);
        subjectCount = stoi(line);

        // Create Tutor object
        Tutor *tutor = new Tutor(id, name, location, password, balance, subjectCount, rating);

        // Load SubjectRecord IDs
        for (int i = 0; i < subjectCount; ++i)
        {
            getline(file, line);
            // Create temporary SubjectRecord
            Subject *subject = new Subject("Temp Subject", 0, line);
            SubjectRecord *sr = new SubjectRecord(subject);
            tutor->getSubjectList().push_back(sr);
        }

        tutors.push_back(tutor);
        users.push_back(static_cast<User *>(tutor));

        getline(file, line); // Skip separator
    }

    file.close();
    cout << "Da tai " << tutors.getSize() << " gia su tu file." << endl;
    return true;
}

bool FileHandler::LoadStudents(MyVector<Student *> &students, MyVector<User *> &users)
{
    ifstream file(STUDENT_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << STUDENT_FILE << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        string id = line;
        string name, password, location;
        int balance, gradeLevel, tutorCount, subjectCount;

        getline(file, name);
        getline(file, password);
        getline(file, location);

        getline(file, line);
        balance = stoi(line);

        getline(file, line);
        gradeLevel = stoi(line);

        getline(file, line);
        tutorCount = stoi(line);

        // Create Student object
        Student *student = new Student(id, name, location, password, balance, gradeLevel);

        // Load Tutor IDs
        for (int i = 0; i < tutorCount; ++i)
        {
            getline(file, line);
            // Store for later linking
        }

        getline(file, line);
        subjectCount = stoi(line);

        // Load Subject IDs
        for (int i = 0; i < subjectCount; ++i)
        {
            getline(file, line);
            // Store for later linking
        }

        students.push_back(student);
        users.push_back(static_cast<User *>(student));

        getline(file, line); // Skip separator
    }

    file.close();
    cout << "Da tai " << students.getSize() << " hoc sinh tu file." << endl;
    return true;
}

bool FileHandler::LoadSubjectRecords(MyVector<SubjectRecord *> &subjectRecords,
                                     MyVector<Tutor *> &tutors, MyVector<Student *> &students)
{
    ifstream file(SUBJECT_RECORD_FILE);
    if (!file.is_open())
    {
        cout << "Khong the mo file " << SUBJECT_RECORD_FILE << endl;
        return false;
    }

    string line;
    string subjectID, subjectName, costStr, studentCountStr;

    while (getline(file, line))
    {
        if (line.empty() || line == "_______")
            continue;

        subjectID = line;
        getline(file, subjectName);
        getline(file, costStr);
        getline(file, studentCountStr);

        int cost = stoi(costStr);
        int studentCount = stoi(studentCountStr);

        // Update SubjectRecord in tutors
        for (int i = 0; i < tutors.getSize(); ++i)
        {
            Tutor *tutor = tutors[i];
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetID() == subjectID)
                {
                    // Update subject information
                    delete subjectList[j]->GetSubject();
                    Subject *subject = new Subject(subjectName, cost, subjectID);
                    delete subjectList[j];
                    subjectList[j] = new SubjectRecord(subject);

                    // Load students for this subject
                    for (int k = 0; k < studentCount; ++k)
                    {
                        getline(file, line);
                        // Find student and add to subject record
                        for (int l = 0; l < students.getSize(); ++l)
                        {
                            if (students[l]->GetID() == line)
                            {
                                subjectList[j]->AddStudent(students[l]);
                                students[l]->GetTutorList().push_back(tutor);
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }

        getline(file, line); // Skip separator
    }

    file.close();
    return true;
}

bool FileHandler::SaveTutors(MyVector<Tutor *> &tutors)
{
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

        MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
        file << subjectList.getSize() << endl;

        for (int j = 0; j < subjectList.getSize(); ++j)
        {
            file << subjectList[j]->GetID() << endl;
        }

        file << "_______" << endl;
    }

    file.close();
    cout << "Da luu " << tutors.getSize() << " gia su vao file." << endl;
    return true;
}

bool FileHandler::SaveStudents(MyVector<Student *> &students)
{
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

        MyVector<Tutor *> &tutorList = student->GetTutorList();
        file << tutorList.getSize() << endl;

        for (int j = 0; j < tutorList.getSize(); ++j)
        {
            file << tutorList[j]->GetID() << endl;
        }

        file << "0" << endl; // Subject count - currently not used
        file << "_______" << endl;
    }

    file.close();
    cout << "Da luu " << students.getSize() << " hoc sinh vao file." << endl;
    return true;
}

bool FileHandler::SaveSubjectRecords(MyVector<Tutor *> &tutors)
{
    ofstream file(SUBJECT_RECORD_FILE, ios::trunc);
    if (!file.is_open())
    {
        cout << "Loi: Khong the mo file " << SUBJECT_RECORD_FILE << " de ghi!" << endl;
        return false;
    }

    int totalRecords = 0;
    for (int i = 0; i < tutors.getSize(); ++i)
    {
        Tutor *tutor = tutors[i];
        MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

        for (int j = 0; j < subjectList.getSize(); ++j)
        {
            SubjectRecord *sr = subjectList[j];
            Subject *subject = sr->GetSubject();
            MyVector<Student *> &studentList = sr->GetStudentList();

            file << sr->GetID() << endl;
            file << subject->GetName() << endl;
            file << subject->GetCost() << endl;
            file << studentList.getSize() << endl;

            for (int k = 0; k < studentList.getSize(); ++k)
            {
                file << studentList[k]->GetID() << endl;
            }

            file << "_______" << endl;
            totalRecords++;
        }
    }

    file.close();
    cout << "Da luu " << totalRecords << " mon hoc vao file." << endl;
    return true;
}

bool FileHandler::SaveAllData(MyVector<Tutor *> &tutors, MyVector<Student *> &students)
{
    bool success = true;
    success &= SaveTutors(tutors);
    success &= SaveStudents(students);
    success &= SaveSubjectRecords(tutors);
    return success;
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