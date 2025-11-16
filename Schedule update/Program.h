#include "MyVector.h"
#include <unordered_map>
class Tutor;
class Student;
class User;
class Subject;
class SubjectRecord;
class Schedule;
struct RegisData
{
    string Role;
    string ID;
    string Name;
    string Password;
    string Location;
    int Balance;
    int subjectCount;
    MyVector<Subject *> Subjects;
    MyVector<string> TutorIDs;
    MyVector<string> SubjectIDs;
    int TutorCount;
    double Rating;
    int GradeLevel;
};

class Program
{
private:
    static MyVector<Tutor *> TutorList;
    static MyVector<Student *> StudentList;
    static MyVector<User *> UserList;
    static MyVector<SubjectRecord *> srList;
    static MyVector<Schedule *> ScheduleList;
    static bool DataLoaded;
    static unordered_map<string, Tutor *> ttid;
    static unordered_map<string, Student *> stdid;
    static unordered_map<string, SubjectRecord *> sbjid;

public:
    Program();
    ~Program();
    // getter
    MyVector<Tutor *> &getTutorList()
    {
        return TutorList;
    }
    MyVector<Student *> &getStudentList()
    {
        return StudentList;
    }
    MyVector<User *> &getUserList()
    {
        return UserList;
    }
    MyVector<SubjectRecord *> &getSrList()
    {
        return srList;
    }
    MyVector<Schedule *> &getScheduleList() 
    { 
        return ScheduleList; 
    }
    unordered_map<string, Tutor *> &getTutorId()
    {
        return this->ttid;
    }
    unordered_map<string, Student *> &getStdId()
    {
        return this->stdid;
    }
    unordered_map<string, SubjectRecord *> &getSbjId()
    {
        return this->sbjid;
    }
    //
    friend bool ValidateRegisData(RegisData &data);
    friend string GenID();
    string GenID();
    SubjectRecord *GetsrByID(const string &);
    Student *GetstdByID(const string &id);
    Tutor *GetTutorByID(const string &id);
    Schedule* GetScheduleByID(const string& id);
    void LoadData();
    void SaveAllData();
    bool RegisterNewUser();
    Tutor *LoginTutor(const string &id, const string &password);
    Student *LoginStudent(const string &id, const string &password);
    User *LoginUser(const string &id, const string &password);
    void DisplayTutors(MyVector<Tutor *>);
    void DisplaySubject();
    void FindTutor(Student *student);
    void CreateSchedule(Student* student, Tutor* tutor, SubjectRecord* subjectRecord); 
    void ViewStudentSchedule(const string& studentID); 
    void ViewTutorSchedule(const string& tutorID); 
    bool CheckScheduleConflict(const Schedule& newSchedule); 
    void MarkAttendance(Schedule* schedule, bool attended, const string& notes);  
};