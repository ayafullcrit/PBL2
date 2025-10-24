#include "MyVector.h"
class Tutor;
class Student;
class User;
class Subject;
class SubjectRecord;
struct RegisData
{
    string Role;
    string ID;
    string Name;
    string Password;
    string Location;
    int Balance;
    int subjectCount;
    MyVector<Subject> Subjects;
    MyVector<string> TutorIDs;
    MyVector<string> SubjectIDs;
    int TutorCount;
    double Rating;
    int GradeLevel;
};

class Admin
{
private:
    static MyVector<Tutor *> TutorList;
    static MyVector<Student *> StudentList;
    static MyVector<User *> UserList;
    static MyVector<SubjectRecord *> srList;
    static bool DataLoaded;

public:
    Admin();
    ~Admin() = default;
    // getter
    MyVector<Tutor *> &getTutorList()
    {
        return TutorList;
    }
    MyVector<Student *> &getStudentList()
    {
        return StudentList;
    }

    //
    friend bool ValidateRegisData(RegisData &data);
    friend string GenID();
    Tutor *LastRegisteredTutor()
    {
        return TutorList[TutorList.getSize() - 1];
    }
    Student *LastRegisteredStudent()
    {
        return StudentList[StudentList.getSize() - 1];
    }
    SubjectRecord *GetsrByID(const string &);
    Student *GetstdByID(const string &id);
    Tutor *GetTutorByID(const string &id);
    friend void UserLoad();
    void LoadData();
    void RegisterNewUser();
    Tutor *LoginTutor(const string &id, const string &password);
    Student *LoginStudent(const string &id, const string &password);
    User *LoginUser(const string &id, const string &password);
    void DisplayAllTutors();
    void FindTutor(Student* student);
    MyVector<Tutor *> TutorsFilter(const string &name = "", const string &subject = "",
                                   const string &location = "", double minRating = 0);
};