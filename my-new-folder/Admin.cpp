#include "Admin.h"
#include "Tutor.h"
#include "SubjectRecord.h"
#include "time.h"
#include <fstream>
#include <sstream>
string TutorDB = "Tutor.txt";
string StudentDB = "Student.txt";
string SubjectRecordDB = "SubjectRecord.txt";
MyVector<Tutor *> Admin::TutorList;
MyVector<Student *> Admin::StudentList;
MyVector<User *> Admin::UserList;
MyVector<SubjectRecord *> Admin::srList;
bool Admin::DataLoaded = 0;
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
template <typename T>
string GenID(MyVector<T> vec)
{
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
void Admin::RegisterNewUser()
{
    RegisData data;
    cout << "----- Dang ky tai khoan moi -----" << endl;
    data.ID = GenID(Admin::UserList);
    cout << "ID: " << data.ID << endl;
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
        cin >> data.GradeLevel;
        cin.ignore();
    }
    else if (data.Role == "Tutor")
    {
        cout << "Nhap so mon hoc day: ";
        cin >> data.subjectCount;
        cin.ignore();
        for (int i = 0; i < data.subjectCount; ++i)
        {
            string subject;
            string ID = GenID(Admin::srList);
            int cost;
            cout << "-Nhap ten mon hoc thu " << (i + 1) << ": ";
            getline(cin, subject);
            normalize_string(subject);
            cout << "-Nhap hoc phi cho mon " << subject << " : ";
            cin >> cost;
            data.Subjects.push_back(Subject(subject, cost, ID));
            cin.ignore();
        }
    }
    if (!ValidateRegisData(data))
        return;
    // Student* tempstd;
    // Tutor* temptt;
    if (data.Role == "Student")
    {
        Student *newStudent = new Student(data.ID, data.Name, data.Password, data.Location, data.Balance, data.GradeLevel);
        //  tempstd = tempstd;
        StudentList.push_back(newStudent);
        UserList.push_back(static_cast<User *>(newStudent));
    }
    else if (data.Role == "Tutor")
    {
        Tutor *newTutor = new Tutor(data.ID, data.Name, data.Password, data.Location, data.Balance, data.subjectCount);
        //  temptt = newTutor;
        for (int i = 0; i < data.Subjects.getSize(); ++i)
        {
            newTutor->AddSubject(data.Subjects[i]);
        }
        TutorList.push_back(newTutor);
        UserList.push_back(static_cast<User *>(newTutor));
    }
    cout << "Dang ky tai khoan thanh cong!" << endl;

    // write to file//

    string filename;
    if (data.Role == "Student")
        filename = "Student.txt";
    else
        filename = "Tutor.txt";
    // common info
    ofstream outfile(filename, ios::app);
    outfile << data.ID << endl
            << data.Name << endl
            << data.Password << endl
            << data.Location << endl
            << data.Balance << endl;

    // specific info
    if (data.Role == "Tutor")
    {
        outfile << "0" << endl // default rating
                << data.subjectCount << endl;
        ofstream outfile2("SubjectRecord.txt", ios::app); // Subject's data file
        for (int i = 0; i < data.Subjects.getSize(); i++)
        {
            outfile << data.Subjects[i].GetID() << endl;
            outfile2 << data.Subjects[i].GetID() << endl
                     << data.Subjects[i].GetName() << endl
                     << data.Subjects[i].GetCost() << endl
                     << 0 << endl          // default student count
                     << "_______" << endl; // end of a subject record
        }
        outfile2.close();
    }
    if (data.Role == "Student")
    {
        outfile << data.GradeLevel << endl;
        outfile << 0 << endl; // default tutor count
        outfile << 0 << endl; // default subject count
    }
    outfile << "_______" << endl; // end of a user record
    outfile.close();
}
Admin::Admin()
{
    if (!DataLoaded)
    {
        LoadData();
        DataLoaded = 1;
    }
}
SubjectRecord *Admin::GetsrByID(const string &id)
{
    for (int i = 0; i < srList.getSize(); ++i)
    {
        if (srList[i]->GetID() == id)
            return srList[i];
    }
    return nullptr;
}
Student *Admin::GetstdByID(const string &id)
{
    for (int i = 0; i < StudentList.getSize(); ++i)
    {
        if (StudentList[i]->GetID() == id)
            return StudentList[i];
    }
    return nullptr;
}
Tutor *Admin::GetTutorByID(const string &id)
{
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        if (TutorList[i]->GetID() == id)
            return TutorList[i];
    }
    return nullptr;
}
void Reset(RegisData &data)
{
    data.ID = "";
    data.Name = "";
    data.Password = "";
    data.Location = "";
    data.Balance = 0;
    data.Role = "";
    data.GradeLevel = 0;
    data.Subjects = MyVector<Subject>();
}
void Admin::LoadData()
{
    // Load Student data
    ifstream stdfile(StudentDB);
    string line;

    while (getline(stdfile, line))
    {
        if (line.empty() || line == "_______")
            continue;

        RegisData data;
        data.Role = "Student";
        data.ID = line; // UserID

        getline(stdfile, data.Name);     // UserName
        getline(stdfile, data.Password); // UserPassword
        getline(stdfile, data.Location); // UserLocation

        getline(stdfile, line);
        data.Balance = stoi(line); // UserBalance

        getline(stdfile, line);
        data.GradeLevel = stoi(line); // UserGrade

        getline(stdfile, line);
        data.TutorCount = stoi(line); // NumberofTutor

        // Load Tutor IDs
        for (int i = 0; i < data.TutorCount; ++i)
        {
            getline(stdfile, line);
            data.TutorIDs.push_back(line);
        }

        getline(stdfile, line);
        data.subjectCount = stoi(line); // NumberofSubject

        // Load Subject IDs
        for (int i = 0; i < data.subjectCount; ++i)
        {
            getline(stdfile, line);
            data.SubjectIDs.push_back(line);
        }

        // Create Student object
        Student *newStudent = new Student(data.ID, data.Name, data.Location,
                                          data.Password, data.Balance, data.GradeLevel);
        StudentList.push_back(newStudent);
        UserList.push_back(static_cast<User *>(newStudent));

        // Bỏ qua dòng phân cách
        getline(stdfile, line);
    }
    stdfile.close();

    // Load Tutor data
    ifstream ttfile(TutorDB);

    while (getline(ttfile, line))
    {
        if (line.empty() || line == "_______")
            continue;

        RegisData data;
        data.Role = "Tutor";
        data.ID = line; // UserID

        getline(ttfile, data.Name);     // UserName
        getline(ttfile, data.Password); // UserPassword
        getline(ttfile, data.Location); // UserLocation

        getline(ttfile, line);
        data.Balance = stoi(line); // UserBalance

        getline(ttfile, line);
        data.Rating = stod(line); // UserRating

        getline(ttfile, line);
        data.subjectCount = stoi(line); // NumberofSubjectRecord

        // Create Tutor object
        Tutor *newTutor = new Tutor(data.ID, data.Name, data.Location,
                                    data.Password, data.Balance, data.subjectCount, data.Rating);

        // Load SubjectRecord IDs và thêm vào Tutor
        for (int i = 0; i < data.subjectCount; ++i)
        {
            getline(ttfile, line);
            // Tạo SubjectRecord tạm thời
            Subject *subject = new Subject("Temp Subject", 0, line);
            SubjectRecord *sr = new SubjectRecord(subject);
            newTutor->getSubjectList().push_back(sr);
        }

        TutorList.push_back(newTutor);
        UserList.push_back(static_cast<User *>(newTutor));

        // Bỏ qua dòng phân cách
        getline(ttfile, line);
    }
    ttfile.close();

    // Load SubjectRecord data
    ifstream srfile(SubjectRecordDB);
    string subjectID, subjectName, costStr, studentCountStr;

    while (getline(srfile, subjectID))
    {
        if (subjectID.empty() || subjectID == "_______")
            continue;

        getline(srfile, subjectName);
        getline(srfile, costStr);
        getline(srfile, studentCountStr);

        int cost = stoi(costStr);
        int studentCount = stoi(studentCountStr);

        // Tìm và cập nhật SubjectRecord trong các Tutor
        for (int i = 0; i < TutorList.getSize(); ++i)
        {
            Tutor *tutor = TutorList[i];
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetID() == subjectID)
                {
                    // Update Subject info
                    delete subjectList[j]->GetSubject();
                    Subject *subject = new Subject(subjectName, cost, subjectID);

                    delete subjectList[j];
                    subjectList[j] = new SubjectRecord(subject);
                    break;
                }
            }
        }

        // Load Student IDs and add to SubjectRecord
        for (int i = 0; i < studentCount; ++i)
        {
            getline(srfile, line);
            Student *student = GetstdByID(line);
            if (student != nullptr)
            {
                // Find the SubjectRecord and add Student
                for (int i = 0; i < TutorList.getSize(); ++i)
                {
                    Tutor *tutor = TutorList[i];
                    MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
                    for (int j = 0; j < subjectList.getSize(); ++j)
                    {
                        if (subjectList[j]->GetID() == subjectID)
                        {
                            subjectList[j]->AddStudent(student);
                            // Đồng thời thêm Tutor vào danh sách Tutor của Student
                            student->GetTutorList().push_back(tutor);
                            break;
                        }
                    }
                }
            }
        }
        // skip separator line
        getline(srfile, line);
    }
    srfile.close();
}
Tutor *Admin::LoginTutor(const string &id, const string &password)
{
    Tutor *tutor = GetTutorByID(id);
    cout << tutor->GetPassword() << ' ' << password << endl;
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
    cout << "Khong tim thay gia su voi ID nay!" << endl;
    return nullptr;
}
Student *Admin::LoginStudent(const string &id, const string &password)
{
    Student *student = GetstdByID(id);
    if (student != nullptr)
        if (student->Authenticate(password))
        {
            cout << "Dang nhap thanh cong! Chao mung Hoc sinh " << student->GetName() << endl;
            cout << "ID: " << student->GetID() << endl;
            return student;
        }
        else
        {
            cout << "Mat khau khong dung!" << endl;
            return nullptr;
        }
    cout << "Khong tim thay hoc sinh voi ID nay!" << endl;
    return nullptr;
}
User *Admin::LoginUser(const string &id, const string &password)
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

    cout << "ID hoac mat khau khong dung!" << endl;
    return nullptr;
}
MyVector<Tutor *> Admin::TutorsFilter(const string &name, const string &subject,
                                      const string &location, double minRating)
{
    MyVector<Tutor *> results;
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        Tutor *tutor = TutorList[i];
        bool matches = true;

        // check name
        if (!name.empty() && tutor->GetName().find(name) == string::npos)
            matches = false;
        // check location
        if (matches && !location.empty() && tutor->GetLocation().find(location) == string::npos)
            matches = false;
        // check subject
        if (matches && !subject.empty())
        {
            bool foundSubject = false;
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetSubject()->GetName().find(subject) != string::npos)
                {
                    foundSubject = true;
                    break;
                }
            }
            matches = foundSubject;
        }

        // check min rating
        if (matches && minRating > 0 && tutor->GetRating() < minRating)
            matches = false;
        if (matches)
            results.push_back(tutor);
    }
    return results;
}
void Admin::DisplayAllTutors()
{
    cout << "\n===== DANH SACH TAT CA GIA SU =====" << endl;
    if (TutorList.getSize() == 0)
    {
        cout << "Hien tai chua co gia su nao trong he thong!" << endl;
        return;
    }

    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        Tutor *tutor = TutorList[i];
        cout << "\n--- Gia su " << i + 1 << " ---" << endl;
        cout << "ID: " << tutor->GetID() << endl;
        cout << "Ten: " << tutor->GetName() << endl;
        cout << "Dia chi: " << tutor->GetLocation() << endl;
        cout << "Danh gia: " << tutor->GetRating() << "/5" << endl;
        cout << "So luot danh gia: " << tutor->GetNumOfRatings() << endl;
        cout << "So du: " << tutor->GetBalance() << " VND" << endl;

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
void Admin::FindTutor(Student *student)
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
        cin >> choice;
        cin.ignore();

        MyVector<Tutor *> searchResults;

        switch (choice)
        {
        case 1:
        {
            // Hiển thị tất cả gia sư
            DisplayAllTutors();
            searchResults = TutorList;
            break;
        }
        case 2:
        {
            cout << "Nhap ten gia su can tim: ";
            string name;
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
            for (int i = 0; i < searchResults.getSize(); ++i)
            {
                cout << "\n--- Gia su " << i + 1 << " ---" << endl;
                cout << "ID: " << searchResults[i]->GetID() << endl;
                cout << "Ten: " << searchResults[i]->GetName() << endl;
                cout << "Dia chi: " << searchResults[i]->GetLocation() << endl;
                cout << "Danh gia: " << searchResults[i]->GetRating() << "/5" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Nhap ten mon hoc can tim: ";
            string subject;
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
            for (int i = 0; i < searchResults.getSize(); ++i)
            {
                cout << "\n--- Gia su " << i + 1 << " ---" << endl;
                cout << "ID: " << searchResults[i]->GetID() << endl;
                cout << "Ten: " << searchResults[i]->GetName() << endl;
                cout << "Dia chi: " << searchResults[i]->GetLocation() << endl;
                cout << "Danh gia: " << searchResults[i]->GetRating() << "/5" << endl;
            }
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
            char addChoice;
            cin >> addChoice;
            cin.ignore();

            if (addChoice == 'y' || addChoice == 'Y')
            {
                cout << "Chon gia su theo so thu tu (1-" << searchResults.getSize() << "): ";
                int tutorChoice;
                cin >> tutorChoice;
                cin.ignore();

                if (tutorChoice >= 1 && tutorChoice <= searchResults.getSize())
                {
                    Tutor *selectedTutor = searchResults[tutorChoice - 1];

                    // Kiểm tra xem học sinh đã có gia sư này chưa
                    bool alreadyExists = false;
                    MyVector<Tutor *> &studentTutors = student->GetTutorList();
                    for (int i = 0; i < studentTutors.getSize(); ++i)
                    {
                        if (studentTutors[i]->GetID() == selectedTutor->GetID())
                        {
                            alreadyExists = true;
                            break;
                        }
                    }

                    if (!alreadyExists)
                    {
                        student->AddTutor(*selectedTutor);
                        cout << "Da them gia su " << selectedTutor->GetName() << " vao danh sach!" << endl;
                    }
                    else
                    {
                        cout << "Ban da co gia su nay trong danh sach!" << endl;
                    }
                }
                else
                {
                    cout << "Lua chon khong hop le!" << endl;
                }
            }
        }

        if (choice != 5)
        {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }
    } while (choice != 5);
}