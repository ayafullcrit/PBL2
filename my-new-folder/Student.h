#include "User.h"
#include "MyVector.h"
class Tutor;
class Subject;

class Student : public User
{
private:
    int GradeLevel;
    MyVector<Subject*> SubjectList;
    MyVector<Tutor*> TutorList;

public:
    // con/destructor
    Student(const string & = "000000", const string & = "DefaultName",
            const string & = "Viet Nam", const string & = "12345",
            const int & = 0,const double& = 1, const int & = 10,
            const int & = 10);
    Student(const Student&);
    ~Student();
    // override funcion
    string GetRole() const override { return "Hoc sinh"; };
    void DisplayInfo() const override;
    // bool Authenticate
    //  class's method
    void AddSubject(const Subject &);
    //
};