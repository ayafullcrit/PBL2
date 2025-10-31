#include "Student.h"
#include "Tutor.h"
#include "Subject.h"
Student::Student(const string &id, const string &name, const string &location, const string &pass,
                 const int &balance, const double &grade, const int &sbjlist, const int &ttlist)
    : User(id, name, location, pass, balance), GradeLevel(grade), SubjectList(sbjlist),
      TutorList(ttlist) {
          // cout << "Tutor constructor is called!" << endl;
      };
Student::Student(const Student &other)
    : User(other)
{
    SubjectList = MyVector<Subject *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new Subject(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }
    TutorList = MyVector<Tutor *>(other.TutorList.getSize());
    for (int i = 0; i < other.TutorList.getSize(); ++i)
    {
        if (other.TutorList[i] != nullptr)
            TutorList.push_back(new Tutor(*other.TutorList[i]));
        else
            TutorList.push_back(nullptr);
    }
}
Student::~Student()
{
    for (int i = 0; i < SubjectList.getSize(); ++i)
    {
        Subject *subj = SubjectList[i];
        delete subj;
    }

    // Giải phóng từng Tutor* trong danh sách
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        Tutor *t = TutorList[i];
        delete t;
    }
}
void Student::DisplayInfo() const
{
    this->User::DisplayInfo();
    cout << "Lop: " << GradeLevel << endl;
}
void Student::AddSubject(Subject* NewSubject)
{
    cout << "Da them mon " << NewSubject->GetName() << " thanh cong!\n";
    this->SubjectList.push_back(NewSubject);
}
void Student::AddTutor(Tutor* NewTutor)
{
    cout << "Da them giao vien " << NewTutor->GetName() << endl;
    this->TutorList.push_back(NewTutor);
}
void Student::Show_SubjectList()
{
    cout << "Danh sach cac mon hoc dang theo hoc:\n";
    for (int i = 0; i < this->SubjectList.getSize(); i++)
    {
        cout << SubjectList[i]->GetName() << endl;
    }
}
void Student::Show_TutorList()
{
    cout << "Danh sach cac giao vien dang theo hoc:\n";
    for (int i = 0; i < this->TutorList.getSize(); i++)
    {
        cout << TutorList[i]->GetName() << endl;
    }
}
void Student::PayCost(Subject &sbj)
{
    if (this->UserBalance >= sbj.GetCost())
    {
        this->Withdraw(sbj.GetCost());
        cout << "Da thanh toan " << sbj.GetCost() << " cho mon " << sbj.GetName() << endl;
    }
    else
    {
        cout << "So du khong du de thanh toan mon " << sbj.GetName() << endl;
    }
}
Student &Student::operator=(const Student &other)
{
    if (this == &other)
        return *this;

    User::operator=(other); // Gọi toán tử gán của lớp cơ sở User

    GradeLevel = other.GradeLevel;

    // Giải phóng bộ nhớ hiện tại của SubjectList
    for (int i = 0; i < SubjectList.getSize(); ++i)
    {
        delete SubjectList[i];
    }
    SubjectList = MyVector<Subject *>(other.SubjectList.getSize());
    for (int i = 0; i < other.SubjectList.getSize(); ++i)
    {
        if (other.SubjectList[i] != nullptr)
            SubjectList.push_back(new Subject(*other.SubjectList[i]));
        else
            SubjectList.push_back(nullptr);
    }

    // Giải phóng bộ nhớ hiện tại của TutorList
    for (int i = 0; i < TutorList.getSize(); ++i)
    {
        delete TutorList[i];
    }
    TutorList = MyVector<Tutor *>(other.TutorList.getSize());
    for (int i = 0; i < other.TutorList.getSize(); ++i)
    {
        if (other.TutorList[i] != nullptr)
            TutorList.push_back(new Tutor(*other.TutorList[i]));
        else
            TutorList.push_back(nullptr);
    }

    return *this;
}
void Student::Rating(Tutor &tutor, const double &rating)
{
    if (rating < 0 || rating > 5) {
        cout << "Diem danh gia phai tu 0 den 5!" << endl;
        return;
    }
    
    // Tính điểm trung bình mới
    double currentTotal = tutor.GetRating() * tutor.GetNumOfRatings();
    double newTotal = currentTotal + rating;
    int newNumRatings = tutor.GetNumOfRatings() + 1;
    double newRating = newTotal / newNumRatings;
    
    // Cập nhật đánh giá
    tutor.SetRating(newRating);
    tutor.SetNumOfRatings(newNumRatings);
    
    cout << "Da danh gia gia su " << tutor.GetName() << " voi diem so: "
         << rating << "/5" << endl;
    cout << "Diem trung binh hien tai: " << newRating << "/5" << endl;
    cout << "Tong so luot danh gia: " << newNumRatings << endl;
}