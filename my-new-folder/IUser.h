//Interface
#include<string>
using namespace std;
class IUser{
    public:
        virtual ~IUser() = default;
        virtual string GetRole() const = 0;
        virtual bool Authenticate(const string&) const = 0;
        virtual void DisplayInfo() const = 0;
        virtual void UpdateInfo() = 0;
};