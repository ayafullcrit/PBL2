#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "Screen.h"
#include "Program.h"
#include "Tutor.h"
#include "Student.h"
#include "FileHandler.h"
#include "Admin.h"
void RemoveUser(Admin *admin)
{
    system("cls");

    int x = 5, y = 3;
    int width = 110;
    int total_height = 10;

    // Vẽ khung chính
    SetWordColor(11); // Màu xanh dương
    rectangle(x, y, width, total_height);

    // Tiêu đề chính
    SetWordColor(14); // Màu vàng
    string title = "XOA NGUOI DUNG";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;
    Program prg;
    MyVector<Student *> studentList = prg.getStudentList();
    MyVector<Tutor *> tutorList = prg.getTutorList();

    int totalSize = prg.getTutorList().getSize() + prg.getStudentList().getSize();
    // Kiểm tra nếu không có lịch học
    if (tutorList.getSize() + studentList.getSize() == 0)
    {
        SetWordColor(12); // Màu đỏ
        gotoXY(x + (width - 20) / 2, y + 5);
        cout << "Chua co nguoi dung nao!";
        gotoXY(x + (width - 30) / 2, y + 7);
        cout << "Nhan phim bat ky de quay lai...";
        SetWordColor(7);
        _getch();
        return;
    }
    total_height = 10;
    // Phân loại lịch học
    int currentY = y + 3;
    x++;
    gotoXY(x, currentY);
    cout << "Nhap id nguoi dung ban muon xoa: ";
    string id;
    SetWordColor(15);
    cin >> id;
    if (!prg.GetUserByID(id))
    {
        gotoXY(x, currentY + 2);
        SetWordColor(4);
        cout << "Khong tim thay nguoi dung!";
        gotoXY(x, currentY + 3);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    admin->RemoveUser(id);
    gotoXY(x, currentY + 2);
    cout << "Xoa thanh cong nguoi dung voi ID " << id;
    gotoXY(x, currentY + 3);
    cout << "An phim bat ki de quay lai";
    SetWordColor(7);
    _getch();
}
void ShowAdminMenu()
{
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // Noi dung hien thi
    string title = "MENU ADMIN";
    string welcome = "Chao mung ADMIN!";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    // Màu khung
    SetWordColor(9); // xanh duong sáng

    // --- Dòng trên cùng ---
    cout << string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    cout << string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6); // vang
    cout << string(padTitle, ' ') << title;
    SetWordColor(9);
    cout << string(boxWidth - 2 - padTitle - title.size(), ' ') << UpBorder << "\n";

    // --- Dòng ngan cách ---
    cout << string(startX, ' ') << CrossLeft;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << CrossRight << "\n";

    // --- Dòng chào mung ---
    cout << string(startX, ' ') << UpBorder;
    int padWelcome = (boxWidth - 2 - welcome.size()) / 2;
    SetWordColor(6);
    cout << string(padWelcome, ' ') << welcome;
    SetWordColor(9);
    cout << string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    cout << string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightBottom << "\n";

    // ======= Các ô chuc nang =======
    int menuWidth = 34;
    int spaceBetween = 10;
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2;
    int leftX = startMenuX;                        // 21 khung trai
    int rightX = leftX + menuWidth + spaceBetween; // 65 khung bên phai

    int startY = 9;
    int gapY = 3;
    // moi khung co toa do x (21,55)
    // moi khung co toa do y (9,12)

    // --- Ct 1 & 2 ---
    SetWordColor(9); // màu khung xanh duong sáng
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);
    SetWordColor(6); // vang
    gotoXY(leftX + 1, startY + 1);
    cout << "1. Xoa nguoi dung";
    gotoXY(rightX + 1, startY + 1);
    cout << "2. Dat lai mat khau";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "3. Xet duyet gia su";
    gotoXY(rightX + 1, startY + 1);
    cout << "4. Xem danh sach nguoi dung";
    // --- Ô Ðang Xuat ---
    int logoutX = 50;
    int logoutY = 16;
    SetWordColor(9);
    rectangle(logoutX, logoutY, 20, 3);
    SetWordColor(6);
    gotoXY(logoutX + 5, logoutY + 1);
    cout << "Dang Xuat" << endl;

    SetWordColor(14); // quay ve mau vang
}
Admin *LoginAdmin()
{
    gotoXY(0,0);
    Program prg;
    system("cls");
    // toa do
    int x = 20;
    int y = 5;
    int width = 73; // Can chinh
    int height = 14;

    char Border = 205;   // -
    char LeftTee = 204;  // ¦
    char RightTee = 185; // ¦

    // ve khung
    SetWordColor(14); // Màu xanh lá cho khung
    rectangle(x, y, width, height);

    // ve duong chia ben trong
    gotoXY(x, y + 4);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    gotoXY(x, y + 11);
    cout << LeftTee; // ¦
    for (int i = 0; i < width - 2; i++)
        cout << Border; // -
    cout << RightTee;   // ¦

    SetWordColor(6);
    gotoXY(x + 27, y + 2);
    cout << "DANG NHAP - ADMIN";

    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9);
    cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12);
    cout << "(Nhan ENTER de xac nhan)";
    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;
    // gotoXY(inputX, y + 6);
    // cout << "___________________________________";
    // gotoXY(inputX, y + 8);
    // cout << "___________________________________";

    // 5.Nhap thông tin
    string id, password;

    SetWordColor(6); // Màu trang cho nhãn
    gotoXY(x + 4, y + 6);
    cout << "Nhap ID:";
    gotoXY(x + 4, y + 8);
    cout << "Mat Khau:";
    SetWordColor(15);
    gotoXY(inputX, y + 6);
    getline(cin, id);
    // SetWordColor(6);
    // gotoXY(x + 4, y + 8);
    // cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // 6. Xu lý sau khi dang nhap
    SetWordColor(6);           // Màu xanh duong sáng
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
                               // cout << id << "  " << password ;
    bool IsExist = 0, IsPassword = 0;
    Admin *admin = NULL;
    for (int i = 0; i < prg.getAdminList().getSize(); i++)
    {
        if (prg.getAdminList()[i]->GetID() == id)
        {
            IsExist = 1;
            if (prg.getAdminList()[i]->GetPassword() == password)
            {
                IsPassword = 1;
                admin = prg.getAdminList()[i];
            }
        }
    }
    if (!IsExist)
    {
        SetWordColor(4);
        cout << "Khong tim thay admin voi ID nay!";
        cout<<" Nhan phim bay ky de quay lai menu";
        getch();
        return NULL;
    }
    else if (!IsPassword)
    {
        SetWordColor(4);
        cout << "Mat khau khong dung!";
        cout<<"Nhan phim bat ky de quay lai menu";
        getch();
        return NULL;
    }
    else if (IsPassword ==1 && IsExist ==1){
    SetWordColor(10);
    cout << "Dang nhap thanh cong!";
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    }
    return admin;
}
void ResetPassword(Admin *admin)

{
    system("cls");

    int x = 5, y = 3;
    int width = 110;
    int total_height = 10;

    // Vẽ khung chính
    SetWordColor(11); // Màu xanh dương
    rectangle(x, y, width, total_height);

    // Tiêu đề chính
    SetWordColor(14); // Màu vàng
    string title = "RESET PASSWORD";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;
    Program prg;
    MyVector<Student *> studentList = prg.getStudentList();
    MyVector<Tutor *> tutorList = prg.getTutorList();

    int totalSize = prg.getTutorList().getSize() + prg.getStudentList().getSize();

    if (tutorList.getSize() + studentList.getSize() == 0)
    {
        SetWordColor(12); // Màu đỏ
        gotoXY(x + (width - 20) / 2, y + 5);
        cout << "Chua co nguoi dung nao!";
        gotoXY(x + (width - 30) / 2, y + 7);
        cout << "Nhan phim bat ky de quay lai...";
        SetWordColor(7);
        _getch();
        return;
    }
    total_height = 10;
    // Phân loại lịch học
    int currentY = y + 3;
    x++;
    gotoXY(x, currentY);
    cout << "Nhap id nguoi dung ban muon dat lai mat khau: ";
    string id;
    SetWordColor(15);
    cin >> id;
    if (prg.GetUserByID(id) == NULL)
    {
        gotoXY(x, currentY + 2);
        SetWordColor(4);
        cout << "Khong tim thay nguoi dung!";
        gotoXY(x, currentY + 3);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    admin->ResetPassword(id);
    gotoXY(x, currentY + 2);
    SetWordColor(10);
    cout << "Dat lai mat khau thanh cong (123456)";
    gotoXY(x, currentY + 3);
    SetWordColor(14);
    cout << "An phim bat ki de quay lai";
    SetWordColor(7);
    _getch();
}
void ApproveTutor(Admin *admin)
{
    Program prg;
    MyVector<Tutor *> &firsttutorList = prg.getTutorList();
    MyVector<Tutor* > tutorList;
    for(int i = 0; i < firsttutorList.getSize(); i++)
    if(firsttutorList[i]->IsApproved() == 0) tutorList.push_back(firsttutorList[i]);
    system("cls");
    if (tutorList.getSize() == 0)
    {
        // Hiển thị thông báo không có gia sư
        system("cls");
        int x = 20, y = 10;
        int width = 40, height = 5;
        SetWordColor(12);
        rectangle(x, y, width, height);
        gotoXY(x + (width - 30) / 2, y + 2);
        cout << "Ban chua co gia su nao!";
        gotoXY(x + (width - 30) / 2, y + 3);
        cout << "Nhan phim bat ky de quay lai...";
        SetWordColor(7);
        _getch();
        return;
    }
    int x = 10, y = 3;
    int width = 60;
    int height = 13 + tutorList.getSize();
    // Chọn gia sư từ danh sách gia sư của student
    Tutor *selectedTutor = nullptr;
    SetWordColor(14);
    rectangle(x, y, width, height);

    string title = "XET DUYET TAI KHOAN GIA SU";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    int currentY = y + 3;
    SetWordColor(11);
    gotoXY(x + 3, currentY);
    cout << "Danh sach gia su:";
    currentY++;

    for (int i = 0; i < tutorList.getSize(); i++)
    {
        SetWordColor(7);
        gotoXY(x + 5, currentY);
        cout << i + 1 << ". ID: " << tutorList[i]->GetID() << "  Ten: " << tutorList[i]->GetName();
        currentY++;
    }

    SetWordColor(10);
    gotoXY(x + 3, currentY);
    cout << "Chon gia su (nhap so thu tu): ";
    int choice;
    SetWordColor(15);
    if (!IntInput(choice))
    {
        SetWordColor(4);
        gotoXY(x + 3, currentY + 2);
        cout << "Vui long nhap so hop le!";
        gotoXY(x + 3, currentY + 3);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }

    if (choice < 1 || choice > tutorList.getSize())
    {
        SetWordColor(4);
        gotoXY(x + 3, currentY + 2);
        cout << "So thu tu khong hop le!";
        gotoXY(x + 3, currentY + 3);
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    selectedTutor = tutorList[choice - 1];

    if (!selectedTutor)
    {
        SetWordColor(4);
        gotoXY(x + 3, currentY + 2);
        cout << "Khong co gia su duoc chon!";
        gotoXY(x + 3, currentY + 3);
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return;
    }
    admin->ApproveTutor(selectedTutor);
    gotoXY(x + 3, currentY + 3);
    cout << "Duyet gia su thanh cong!";
    gotoXY(x + 3, currentY + 4);
    cout << "Nhan phim bat ky de quay lai...";
    _getch();
    SetWordColor(7);
}
void DisplayUserList()
{
    Program prg;
    MyVector<User *> userList = prg.getUserList();

    system("cls");
    if (userList.getSize() == 0)
    {
        cout << "Danh sach user rong!" << endl;
        cout << "Nhan phim bat ky de quay lai...";
        getch();
        return;
    }

    int total = userList.getSize();
    int itemsPerPage = 10;
    int currentPage = 0;
    int totalPages = (total + itemsPerPage - 1) / itemsPerPage;
    bool IsPrinted = 0;
    while (true)
    {
        if (!IsPrinted)
        {
            system("cls");
            int x = 3, y = 2;
            int width = 110;
            int header_height = 3;
            int body_height = 15;
            int footer_height = 3;
            int total_height = header_height + body_height + footer_height;

            SetWordColor(14);
            rectangle(x, y, width, total_height);

            // header divider
            gotoXY(x, y + 2);
            cout << (char)204;
            for (int i = 0; i < width - 2; ++i)
                cout << (char)205;
            cout << (char)185;

            // title
            SetWordColor(6);
            string title = "DANH SACH TAT CA USER - TONG CONG: " + to_string(total);
            gotoXY(x + (width - title.length()) / 2, y + 1);
            cout << title;

            // columns header
            SetWordColor(11);
            int contentX = x + 2;
            int contentY = y + 3;
            gotoXY(contentX, contentY);
            cout << "STT  ID        TEN USER           SO DIEN THOAI     DIA CHI                   SO DU (VND)    LOAI USER";
            gotoXY(contentX, contentY + 1);
            for (int i = 0; i < width - 4; ++i)
                cout << "-";

            int start = currentPage * itemsPerPage;
            int end = min(start + itemsPerPage, total);
            int line = contentY + 3;

            for (int i = start; i < end; ++i)
            {
                User *user = userList[i];
                string id = user ? user->GetID() : string("-");
                string name = user ? user->GetName() : string("-");
                string phone = user ? user->GetPhoneNumber() : string("-");
                string location = user ? user->GetLocation() : string("-");
                int balance = user ? user->GetBalance() : 0;
                string role = user ? user->GetRole() : string("-");

                // Đổi màu theo loại user
                if (role == "Gia su")
                    SetWordColor(10); // Xanh lá cho gia sư
                else if (role == "Hoc sinh")
                    SetWordColor(11); // Xanh nhạt cho học sinh
                else
                    SetWordColor(7); // Màu mặc định

                gotoXY(contentX, line);
                cout << setw(3) << left << (i + 1) << "  "
                     << setw(9) << left << id << "  "
                     << setw(18) << left << (name.length() > 17 ? name.substr(0, 15) + ".." : name) << "  "
                     << setw(16) << left << phone << "  "
                     << setw(25) << left << (location.length() > 24 ? location.substr(0, 22) + ".." : location) << "  "
                     << setw(13) << left << balance << "  "
                     << role;
                line++;
            }

            // Thống kê
            SetWordColor(7);
            gotoXY(contentX, contentY + 14);
            cout << "THONG KE:";
            gotoXY(contentX, contentY + 15);

            int tutors = 0, students = 0, totalBalance = 0;
            for (int i = 0; i < total; ++i)
            {
                User *user = userList[i];
                if (user)
                {
                    if (user->GetRole() == "Gia su")
                        tutors++;
                    else if (user->GetRole() == "Hoc sinh")
                        students++;
                    totalBalance += user->GetBalance();
                }
            }

            cout << "Tong user: " << total << " | Gia su: " << tutors
                 << " | Hoc sinh: " << students << " | Tong so du: " << totalBalance << " VND";

            // footer
            SetWordColor(10);
            if (totalPages > 1)
            {
                gotoXY(x + 2, y + total_height - 1);
                SetWordColor(15);
                cout << "Quay lai"; // 5 12
                SetWordColor(14);
                for (int i = 0; i < 22; i++)
                    cout << char(205);
                SetWordColor(15);
                cout << "<- Trang truoc"; // 35 48
                SetWordColor(14);
                for (int i = 0; i < 10; i++)
                    cout << char(205);
                SetWordColor(15);
                cout << "Trang sau ->"; // 59 67
            }
            else
            {
                gotoXY(x + width / 2 - 7, y + total_height - 1);
                SetWordColor(15);
                cout << "Quay lai"; // 51 58
            }
            IsPrinted = 1;
        }
        SetWordColor(7);
        // keyboard navigation
        Coord d = MouseCoord();
        if (totalPages > 1)
        {
            if (d.SE != 22)
                continue;
            if (d.FI >= 35 && d.SE <= 48)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
                else
                    IsPrinted = 0;
            }
            if (d.FI >= 59 && d.FI <= 67)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
                else
                    IsPrinted = 0;
            }
            if (d.FI >= 5 && d.FI <= 12)
                break;
        }
        else
        {
            if (d.SE == 22 && d.FI >= 51 && d.FI <= 58)
                break;
        }
    }
}
void HandleAdminMenu(Admin *admin)
{
    ShowAdminMenu(); // 1. Ve menu sinh vien lan dau tien.
    while (true)
    {                               // 2. Bat dau vong lap su kien cho menu sinh vien.
        Coord click = MouseCoord(); // 3. Cho mot CLICK MOI tu nguoi dung.

        if (click.FI >= 21 && click.FI <= 54 && click.SE >= 9 && click.SE <= 11)
        {
            RemoveUser(admin);
            // man hinh hien thi thong tin ca nhan
            ShowAdminMenu();
            // quay ve menu
        }
        else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98)
        {
            ResetPassword(admin);
            ShowAdminMenu();
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54)
        {
            ApproveTutor(admin);
            ShowAdminMenu();
        }

        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 65 && click.FI <= 98)
        {
            DisplayUserList();
            ShowAdminMenu();
        }

        // nut dang xuat
        else if (click.SE >= 16 && click.SE <= 18 && click.FI >= 50 && click.FI <= 69)
        {
            break; // 4. Thoat khoi vong lap while(true) nay
        }
    }
}
