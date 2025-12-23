#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#include <iostream>
#include <limits>
#include "Screen.h"
#include "FileHandler.h"
#include "Program.h"
#include "Student.h"
#include "Schedule.h"
#include "MyVector.h"
void ShowStudentMenu(Student *student)
{
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // Noi dung hien thi
    string title = "MENU HOC VIEN";
    string welcome = "Chao mung ban " + student->GetName() + " (ID: " + student->GetID() + ")";

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
    cout << "1. Hien thi thong tin ca nhan";
    gotoXY(rightX + 1, startY + 1);
    cout << "2. Dang ky buoi hoc moi";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    cout << "4. Nap tien";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "5. Hien thi danh sach gia su";
    gotoXY(rightX + 1, startY + 1);
    cout << "6. Xem lich hoc";

    startY += gapY;
    SetWordColor(9);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "7. Tim kiem va them gia su";
    gotoXY(rightX + 1, startY + 1);
    cout << "8. Danh gia gia su";

    // --- Ô Ðang Xuat ---
    int logoutX = 50;
    int logoutY = 23;
    SetWordColor(9);
    rectangle(logoutX, logoutY, 20, 3);
    SetWordColor(6);
    gotoXY(logoutX + 5, logoutY + 1);
    cout << "Dang Xuat" << endl;

    SetWordColor(14); // quay ve mau vang
}
void Screen_Student_2(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;      // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT THONG TIN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 5; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 28;  // Lề trái cho dữ liệu
    gotoXY(labelX, contentY - 1);
    cout << "(Nhap N/n o vi tri ban muon bo qua)";
    // gotoXY(labelX, contentY);
    // cout << "Nhap ma so hoc vien moi: ";
    // gotoXY(valueX, contentY);
    // string id;
    // getline(cin, id);
    // if (id != "N" && id != "n" && !id.empty())
    //     student->SetID(id);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap Ho va ten moi     : ";
    gotoXY(valueX, contentY + 1);
    string name;
    getline(cin, name);
    if (name != "N" && name != "n" && !name.empty())
        student->SetUserName(name);

    gotoXY(labelX, contentY + 2);
    cout << "Nhap Lop moi           : ";
    gotoXY(valueX, contentY + 2);
    string lop;
    getline(cin, lop);
    bool isvalid = 1;
    if (lop != "N" && lop != "n")
    {
        for (int i = 0; i < lop.size(); i++)
            if (!isdigit(lop[i]))
            {
                isvalid = 0;
                break;
            }
        int IntGrd = -1;
        if (!lop.empty())
            IntGrd = stoi(lop);

        if (IntGrd < 1 or IntGrd > 12)
            isvalid = 0;

        if (!isvalid)
        {
            SetWordColor(4);
            gotoXY(labelX, contentY + 3);
            cout << "Lop khong hop le!";
            gotoXY(labelX, contentY + 4);
            cout << "An phim bat ki de tiep tuc!";
            _getch();
            return;
        }
        student->SetGradeLevel(IntGrd);
    }

    gotoXY(labelX, contentY + 3);
    cout << "Dia chi moi            : ";
    gotoXY(valueX, contentY + 3);
    string location;
    getline(cin, location);
    if (location != "N" && location != "n")
        student->SetLocation(location);

    gotoXY(labelX, contentY + 4);
    cout << "Nhap mat khau moi      : ";
    gotoXY(valueX, contentY + 4);
    string password;
    getline(cin, password);
    if (password != "N" && password != "n" && !password.empty())
        student->SetPassword(password);
    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    FileHandler::SaveStudents();
    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void Screen_Student_one(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 60;       // Chiều rộng của khung
    int bodyHeight = 10;  // Chiều cao của phần thân
    int footerHeight = 4; // Chiều cao của phần chân trang
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = footerHeight + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    student->DisplayInfo();
    // In footer (căn giữa)
    string footer = "Nhan U de cap nhat thong tin... ";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 2);
    cout << "Nhan phim bat ky de quay lai...";

    char ch = getch();
    if (ch == 'U' || ch == 'u')
    {
        Screen_Student_2(student);
    }

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void ShowNapTienScreen_4(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 55; // Chiều rộng của khung

    // Tính toán chiều cao các phần
    int header_height = 3; // 1 dòng viền trên, 1 dòng chữ, 1 dòng viền dưới
    int body_height = 22;  // 1 viền, 10 dòng nội dung/padding, 1 viền
                           // int footer_height = 3; // 1 viền, 1 dòng chữ, 1 dòng viền dưới

    // Tổng chiều cao (trừ đi 2 vì các viền chia bị trùng)
    int total_height = header_height + body_height - 1; //+ footer_height - 2; // = 16

    char Border = 205;
    char LeftTee = 204;
    char RightTee = 185;

    // 2. Vẽ khung ngoài
    SetWordColor(14);
    rectangle(x, y, width, total_height);

    // 3. Vẽ các đường chia ngang

    int header_divider_y = y + header_height - 1;
    gotoXY(x, header_divider_y);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 4. In nội dung (Màu Vàng Cam)
    SetWordColor(6); // 6 = Vàng Cam

    // In Tiêu đề (Header)
    string title = "NAP TIEN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8

    gotoXY(contentX, contentY_start + 1);
    cout << "Nhap so tien can nap (VND):";

    gotoXY(contentX, contentY_start + 3);
    cout << "Chon phuong thuc thanh toan:";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 4, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 5);
    cout << "1. Chuyen khoan ngan hang         ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 7, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 8);
    cout << "2. Vi dien tu (Momo, ZaloPay)     ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 10, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 11);
    cout << "3. The tin dung (Visa/Mastercard) ";

    SetWordColor(9);
    rectangle(contentX + 2, contentY_start + 13, 37, 3);
    SetWordColor(6);
    gotoXY(contentX + 3, contentY_start + 14);
    cout << "0. Huy bo giao dich               ";

    int soTien;
    int luaChon;

    SetWordColor(15); // Trắng sáng để nhập liệu

    // Nhập số tiền
    gotoXY(contentX + 30, contentY_start + 1);
    if (!IntInput(soTien))
    {
        gotoXY(contentX, contentY_start + 17);
        SetWordColor(4);
        cout << "So tien da nhap khong hop le!";
        gotoXY(contentX, contentY_start + 18);
        SetWordColor(6);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    string PhuongThuc[] = {"tai khoan ngan hang", "vi dien tu", "the tin dung"};
    string final;
    gotoXY(0, 0);
    while (1)
    {
        Coord d = MouseCoord();
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 12 && d.SE <= 14)
        {
            final = PhuongThuc[0];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 15 && d.SE <= 17)
        {
            final = PhuongThuc[1];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 18 && d.SE <= 20)
        {
            final = PhuongThuc[2];
            break;
        }
        if (d.FI >= 15 && d.FI <= 51 && d.SE >= 21 && d.SE <= 23)
        {
            return;
        }
    }
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 17);
    cout << "Da nap thanh cong ";
    SetWordColor(15);
    cout << soTien;
    SetWordColor(10);
    cout << " bang " << final << "!";
    gotoXY(contentX, contentY_start + 18);
    cout << "So du moi: ";
    SetWordColor(15);
    cout << student->GetBalance() + soTien;
    student->Deposit(soTien);
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 19);
    cout << "An phim bat ki de tiep tuc!";
    SetWordColor(15);
    _getch();
}
void ShowDanhSachMonHoc_5(Student *student)
{
    MyVector<Subject *> &sbjlist = student->GetSubjectList();
    MyVector<Tutor *> &ttlist = student->GetTutorList();
    int currentPage = 0;
    int itemsPerPage = 10; // Số môn học mỗi trang
    int totalItems = sbjlist.getSize();
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
    while (1)
    {
        system("cls");
        int x = 10, y = 5;
        int width = 100; // Tăng chiều rộng để chứa 3 cột

        // Tính toán chiều cao các phần
        int header_height = 3;
        int body_height = 18;
        int footer_height = 3;

        int total_height = header_height + body_height + footer_height - 2;

        char Border = 205;
        char LeftTee = 204;
        char RightTee = 185;

        // Vẽ khung ngoài
        SetWordColor(14);
        rectangle(x, y, width, total_height);

        // Vẽ các đường chia ngang
        int header_divider_y = y + header_height - 1;
        gotoXY(x, header_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        int footer_divider_y = y + header_height + body_height - 2;
        gotoXY(x, footer_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        // Tiêu đề
        SetWordColor(6);
        string title = "DANH SACH MON HOC - Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Nội dung - 3 cột
        int contentX = x + 3;
        int contentY_start = y + header_height;

        // Tiêu đề các cột
        gotoXY(contentX + 2, contentY_start + 1);
        cout << "TEN MON HOC";
        gotoXY(contentX + 35, contentY_start + 1);
        cout << "GIANG VIEN";
        gotoXY(contentX + 65, contentY_start + 1); // Thêm cột SDT
        cout << "SDT";

        // Đường kẻ ngang dưới tiêu đề
        gotoXY(contentX, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";
        gotoXY(contentX + 35, contentY_start + 2);
        for (int i = 0; i < 28; i++)
            cout << "-";
        gotoXY(contentX + 65, contentY_start + 2); // Đường kẻ cho cột SDT
        for (int i = 0; i < 20; i++)
            cout << "-";

        // Hiển thị danh sách môn học
        int startIndex = currentPage * itemsPerPage;
        int endIndex = min(startIndex + itemsPerPage, totalItems);
        int currentY = contentY_start + 4;

        for (int i = startIndex; i < endIndex; i++)
        {
            // Cột tên môn học
            gotoXY(contentX + 2, currentY);
            cout << (i + 1) << ". " << sbjlist[i]->GetName();

            // Cột tên giảng viên
            gotoXY(contentX + 35, currentY);
            if (ttlist[i] != NULL)
                cout << ttlist[i]->GetName();
            else
                cout << "------";

            // Cột SDT giảng viên
            gotoXY(contentX + 65, currentY);
            if (ttlist[i] != NULL && !ttlist[i]->GetPhoneNumber().empty())
                cout << ttlist[i]->GetPhoneNumber();
            else
                cout << "------";

            currentY++;
        }

        // Thông tin phân trang
        string pageInfo = "Hien thi " + to_string(startIndex + 1) + "-" + to_string(endIndex) +
                          " tren tong " + to_string(totalItems) + " mon hoc";
        gotoXY(x + (width - pageInfo.length()) / 2, currentY + 1);
        cout << pageInfo;

        // Hướng dẫn điều hướng
        SetWordColor(6);
        string footer;
        if (totalPages > 1)
        {
            footer = "Quay lai                        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "                                            Quay lai";
        }
        gotoXY(x + 1, footer_divider_y + 1);
        cout << footer;
        // Di chuyển con trỏ ra khỏi khung
        gotoXY(0, y + total_height + 2);

        SetWordColor(7);
        Coord d = MouseCoord();
        if (totalPages > 1)
        {
            if (d.SE != 25)
                continue;
            if (d.FI >= 43 && d.SE <= 56)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 63 && d.FI <= 74)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
            }
            if (d.FI >= 11 && d.FI <= 18)
                break;
        }
        else
        {
            if (d.SE != 25)
                continue;
            if (d.FI <= 62 && d.FI >= 55)
            {
                break;
            }
        }
    }
}
void DisplayScheduleCard(Schedule *schedule, int x, int y, int width)
{
    // Vẽ khung card
    SetWordColor(7);
    rectangle(x, y, width, 5);

    // Màu theo trạng thái
    int color;
    if (schedule->GetStatus() == "completed")
        color = 14; // Vàng
    else if (schedule->GetStatus() == "cancelled")
        color = 12; // Đỏ
    else
        color = 10; // Xanh lá

    // Thông tin chính
    SetWordColor(color);
    gotoXY(x + 2, y + 1);
    cout << schedule->GetDate() << " | " << schedule->GetStartTime() << " - " << schedule->GetEndTime();

    // Môn học và gia sư
    gotoXY(x + 2, y + 2);
    if (schedule->GetSubjectRecord() && schedule->GetSubjectRecord()->GetSubject())
    {
        cout << "Mon: " << schedule->GetSubjectRecord()->GetSubject()->GetName();
    }

    gotoXY(x + width - 25, y + 2);
    if (schedule->GetTutor())
    {
        cout << "Gia su: " << schedule->GetTutor()->GetName();
    }

    // Địa điểm và trạng thái
    gotoXY(x + 2, y + 3);
    cout << "Dia diem: " << schedule->GetLocation();

    gotoXY(x + width - 20, y + 4);
    cout << schedule->GetDuration() << " phut";
}

void ShowLichHoc_6(Student *student)
{
    int currentPage = 0;
    int itemsPerPage = 3; // Số lịch học mỗi trang (mỗi card cao 6 dòng)

    while (true)
    {
        system("cls");

        int x = 5, y = 3;
        int width = 110;
        int total_height = 25; // Cố định chiều cao

        // Vẽ khung chính
        SetWordColor(11);
        rectangle(x, y, width, total_height);

        // Tiêu đề chính
        SetWordColor(14);
        string title = "LICH HOC TUAN CUA " + student->GetName();
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Kiểm tra nếu không có lịch học
        if (student->GetSchedules().getSize() == 0)
        {
            SetWordColor(12);
            gotoXY(x + (width - 20) / 2, y + 5);
            cout << "Chua co lich hoc nao!";
            gotoXY(x + (width - 30) / 2, y + 7);
            cout << "Nhan phim bat ky de quay lai...";
            SetWordColor(7);
            _getch();
            return;
        }

        // Phân loại và sắp xếp lịch học
        MyVector<Schedule *> upcomingSchedules;
        for (int i = 0; i < student->GetSchedules().getSize(); ++i)
        {
            Schedule *schedule = student->GetSchedules()[i];
            upcomingSchedules.push_back(schedule);
        }
        upcomingSchedules = SortSchedulesByTime(upcomingSchedules);

        // Tính toán phân trang
        int totalItems = upcomingSchedules.getSize();
        int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
        
        // Đảm bảo currentPage hợp lệ
        if (currentPage >= totalPages) currentPage = totalPages - 1;
        if (currentPage < 0) currentPage = 0;

        int startIndex = currentPage * itemsPerPage;
        int endIndex = min(startIndex + itemsPerPage, totalItems);

        int currentY = y + 3;

        // Hiển thị lịch sắp tới cho trang hiện tại
        if (upcomingSchedules.getSize() > 0)
        {
            SetWordColor(10);
            gotoXY(x + 3, currentY);
            cout << "=== LICH HOC SAP TOI ===";
            currentY++;

            // Hiển thị thông tin trang
            string pageInfo = "Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages) + 
                            " - Hien thi " + to_string(startIndex + 1) + "-" + to_string(endIndex) + 
                            " tren tong " + to_string(totalItems) + " lich hoc";
            gotoXY(x + (width - pageInfo.length()) / 2, currentY);
            cout << pageInfo;
            currentY += 2;

            for (int i = startIndex; i < endIndex; ++i)
            {
                DisplayScheduleCard(upcomingSchedules[i], x + 3, currentY, width - 6);
                currentY += 6; // Mỗi card cao 6 dòng
                if (currentY > y + total_height - 3)
                    break;
            }
            currentY += 2;
        }

        // Thống kê
        SetWordColor(15);
        gotoXY(x + 3, y + total_height - 2);
        cout << "Tong so: " << student->GetSchedules().getSize() << " lich hoc";
        gotoXY(x + width - 25, y + total_height - 2);
        cout << "Sap toi: " << upcomingSchedules.getSize();

        // Hướng dẫn điều hướng
        SetWordColor(8);
        string footer;
        if (totalPages > 1)
        {
            footer = "Quay lai        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "Quay lai";
        }
        gotoXY(x + (width - footer.length()) / 2, y + total_height + 1);
        cout << footer;

        SetWordColor(7);
        // Xử lý điều hướng trang
        Coord d = MouseCoord();
        if (totalPages > 1)
        {
            if (d.SE != 29)
                continue;
            if (d.FI >= 52 && d.FI <= 65) // Trang trước
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            else if (d.FI >= 72 && d.FI <= 83) // Trang sau
            {
                currentPage++;
                if (currentPage >= totalPages)
                    currentPage = totalPages - 1;
            }
            else if (d.FI >= 36 && d.FI <= 43) // Quay lại
            {
                break;
            }
        }
        else
        {
            if (d.SE != 29)
                continue;
            if (d.FI <= 63 && d.FI >= 56) // Quay lại
            {
                break;
            }
        }
    }
}
void Screen_Student_3(Student *student)
{
    system("cls");

    int x = 20;
    int y = 5;
    int width = 73; // 71 ky tu ben trong + 2 vien
    int height = 10;

    char Border = 205;   // ═ (Ban da cung cap)
    char LeftTee = 204;  // ╠ (Ky tu noi)
    char RightTee = 185; // ╣ (Ky tu noi)

    SetWordColor(11); // Mau xanh duong nhat
    rectangle(x, y, width, height);

    // 4. Ve cac duong chia ngang ben trong
    SetWordColor(11);

    // Duong chia 1 (duoi tieu de)
    gotoXY(x, y + 2);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // Duong chia 2 (truoc footer)
    gotoXY(x, y + 7);
    cout << LeftTee;
    for (int i = 0; i < width - 2; i++)
        cout << Border;
    cout << RightTee;

    // 5. In noi dung
    // Tieu de
    SetWordColor(15); // Trang sang
    gotoXY(x + 28, y + 1);
    cout << "[ 3. KIEM TRA SO DU ]";

    // Nhan
    SetWordColor(7); // Trang xam
    gotoXY(x + 4, y + 4);
    cout << "So du hien tai cua ban:";

    SetWordColor(10); // Set mau XANH LA (Bright Green)
    string balance = to_string(student->GetBalance());
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 5);
    cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Nap Tien, hoac phim bat ky de quay lai)";
    int footerX = x + (width - footer.length()) / 2; // Can giua
    gotoXY(footerX, y + 8);
    cout << footer;

    // Reset mau
    SetWordColor(7);
    while (true)
    {
        char key = getch();
        if (key == 'N' || key == 'n')
        {
            ShowNapTienScreen_4(student);
            break;
        }
        else
            break;
    }
}

bool ShowTutorAndSubjectSelection(Student *student, Tutor *&selectedTutor, Subject *&selectedSubject)
{
    system("cls");

    int x = 10, y = 3;
    int width = 80;
    int height = 20;

    // Vẽ khung chính
    SetWordColor(14);
    rectangle(x, y, width, height);

    // Tiêu đề
    SetWordColor(14);
    string title = "CHON GIA SU VA MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    int currentY = y + 3;

    // Hiển thị danh sách gia sư
    SetWordColor(11);
    gotoXY(x + 3, currentY);
    cout << "DANH SACH GIA SU:                   MON HOC:";
    currentY++;

    MyVector<Tutor *> &tutorList = student->GetTutorList();
    MyVector<Subject *> &sbjList = student->GetSubjectList();
    if (tutorList.getSize() == 0)
    {
        SetWordColor(12);
        gotoXY(x + 5, currentY);
        cout << "Ban chua co gia su nao! Vui long them gia su truoc.";
        currentY += 2;

        SetWordColor(8);
        gotoXY(x + (width - 30) / 2, y + height - 1);
        cout << "Nhan phim bat ky de quay lai...";

        SetWordColor(7);
        return false;
    }

    // Hiển thị danh sách gia sư
    for (int i = 0; i < tutorList.getSize(); i++)
    {
        SetWordColor(7);
        gotoXY(x + 5, currentY);
        cout << i + 1 << ". " << tutorList[i]->GetName();
        FOR(j, 0, 30 - tutorList[i]->GetName().length())
        cout << " ";
        cout << sbjList[i]->GetName();
        currentY++;
    }

    // Chọn gia sư
    currentY++;
    SetWordColor(10);
    gotoXY(x + 3, currentY);
    cout << "Chon gia su (nhap so thu tu 1-" << tutorList.getSize() << "): ";

    SetWordColor(15);
    int tutorIndex;
    if (!IntInput(tutorIndex))
        return false;

    if (tutorIndex < 1 || tutorIndex > tutorList.getSize())
    {
        cout << "So thu tu khong hop le!";
        return false;
    }

    selectedTutor = tutorList[tutorIndex - 1];
    selectedSubject = sbjList[tutorIndex - 1];
    return true;
}
void ShowSuccessMessage(Schedule *schedule)
{
    system("cls");

    int x = 15, y = 8;
    int width = 50;
    int height = 8;

    SetWordColor(10);
    rectangle(x, y, width, height);

    SetWordColor(10);
    gotoXY(x + (width - 20) / 2, y + 1);
    cout << "✅ TAO LICH THANH CONG";

    SetWordColor(7);
    gotoXY(x + 3, y + 3);
    cout << "Ma lich: " << schedule->GetID();

    gotoXY(x + 3, y + 4);
    cout << "Ngay: " << schedule->GetDate();

    gotoXY(x + 3, y + 5);
    cout << "Gio: " << schedule->GetStartTime() << " - " << schedule->GetEndTime();

    SetWordColor(12);
    gotoXY(x + (width - 40) / 2, y + 6);
    cout << "⚠  Lich hoc dang cho gia su xac nhan";

    SetWordColor(8);
    gotoXY(x + (width - 30) / 2, y + height - 1);
    cout << "Nhan phim bat ky de quay lai...";

    SetWordColor(7);
    _getch();
}
bool IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool DateValidate(string date)
{
    // Kiểm tra độ dài chuỗi
    if (date.length() != 10)
        return false;

    // Kiểm tra định dạng dd-mm-yyyy
    if (date[2] != '-' || date[5] != '-')
        return false;

    // Tách và chuyển đổi các phần
    for (int i = 0; i < date.length(); i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Kiểm tra phạm vi năm
    if (year < 1 || year > 9999)
        return false;

    // Kiểm tra phạm vi tháng
    if (month < 1 || month > 12)
        return false;

    // Kiểm tra số ngày trong tháng
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Điều chỉnh ngày tháng 2 cho năm nhuận
    if (month == 2 && IsLeapYear(year))
        daysInMonth[1] = 29;

    // Kiểm tra ngày hợp lệ
    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    return true;
}

bool TimeValidate(string time)
{
    if (time.size() != 5)
        return false;
    if (time[2] != ':')
        return false;
    for (int i = 0; i < time.length(); i++)
    {
        if (i == 2)
            continue;
        if (!isdigit(time[i]))
            return false;
    }
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return false;
    return true;
}
void ShowScheduleCreationForm(Student *student, Tutor *tutor, Subject *subjectRecord)
{
    system("cls");

    int x = 10, y = 3;
    int width = 70;
    int height = 22;

    // Vẽ khung chính
    SetWordColor(14);
    rectangle(x, y, width, height);

    // Tiêu đề
    SetWordColor(14);
    string title = "TAO LICH HOC MOI";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // Thông tin đã chọn
    SetWordColor(11);
    gotoXY(x + 3, y + 3);
    cout << "Thong tin da chon:";

    SetWordColor(7);
    gotoXY(x + 5, y + 4);
    cout << "Gia su: " << tutor->GetName();

    gotoXY(x + 5, y + 5);
    cout << "Mon hoc: " << subjectRecord->GetName();

    // Form nhập liệu
    int currentY = y + 7;
    string date, startTime, endTime, location, notes;
    SetWordColor(10);
    gotoXY(x + 3, currentY);
    cout << "Nhap ngay hoc (DD-MM-YYYY): ";
    SetWordColor(15);
    cin >> date;
    if (!DateValidate(date))
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Ngay khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }

    SetWordColor(10);
    gotoXY(x + 3, currentY + 1);
    cout << "Nhap gio bat dau (HH:MM): ";
    SetWordColor(15);
    cin >> startTime;
    bool validStartTime = TimeValidate(startTime);
    if (!validStartTime)
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Gio bat dau khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }
    SetWordColor(10);
    gotoXY(x + 3, currentY + 2);
    cout << "Nhap gio ket thuc (HH:MM): ";
    SetWordColor(15);
    cin >> endTime;
    bool validEndTime = TimeValidate(endTime) && (endTime > startTime);
    if (!validEndTime)
    {
        SetWordColor(12);
        gotoXY(x + 3, currentY + 10);
        cout << "Gio ket thuc khong hop le! Vui long nhap lai.";
        _getch();
        return;
    }

    cin.ignore();
    SetWordColor(10);
    gotoXY(x + 3, currentY + 3);
    cout << "Nhap dia diem hoc: ";
    SetWordColor(15);
    getline(cin, location);

    SetWordColor(10);
    gotoXY(x + 3, currentY + 4);
    cout << "Nhap ghi chu (neu co): ";
    SetWordColor(15);
    getline(cin, notes);

    Program prg;
    bool isExist = false;
    string scheduleID = "";
    srand(time(NULL));
    do
    {
        // Tạo lịch học
        isExist = false;
        scheduleID = "";
        FOR(i, 1, 6)
        scheduleID += to_string(rand() % 10);
        FOR(i, 0, prg.getScheduleList().getSize() - 1)
        {
            if (prg.getScheduleList()[i]->GetID() == scheduleID)
            {
                isExist = true;
                break;
            }
        }
    } while (isExist);
    SubjectRecord *sr = new SubjectRecord(subjectRecord);
    Schedule *newSchedule = new Schedule(scheduleID, date, startTime, endTime, "pending", sr, student, tutor, location, notes);
    // // Kiểm tra trùng lịch
    if (prg.CheckScheduleConflict(*newSchedule))
    {
        delete newSchedule;
        gotoXY(x + 3, currentY + 10);
        cout << "Lich hoc bi trung! Vui long chon thoi gian khac.";
        _getch();
        return;
    }
    // // Lưu lịch học
    prg.getScheduleList().push_back(newSchedule);
    student->AddSchedule(newSchedule);
    tutor->AddSchedule(newSchedule);
    FileHandler::AppendScheduleToFile(newSchedule);
    gotoXY(x + 3, currentY + 10);
    cout << "Them lich hoc thanh cong! Nhan phim bat ky de tiep tuc...";
    _getch();
}

void CreateSchedule(Student *student)
{
    Tutor *tutor = nullptr;
    Subject *subject = nullptr;
    ShowTutorAndSubjectSelection(student, tutor, subject);
    if (!student || !tutor || !subject)
    {
        // Hiển thị thông báo lỗi
        system("cls");
        int x = 20, y = 10;
        int width = 40, height = 5;

        SetWordColor(12);
        rectangle(x, y, width, height);

        gotoXY(x + (width - 20) / 2, y + 2);
        cout << "THONG TIN KHONG HOP LE!";

        gotoXY(x + (width - 30) / 2, y + 3);
        cout << "Nhan phim bat ky de quay lai...";

        SetWordColor(7);
        _getch();
        return;
    }
    // Hiển thị giao diện nhập thông tin lịch học
    ShowScheduleCreationForm(student, tutor, subject);
}
void ScreenDanhGiaTuTor_8(Student *student)
{
    MyVector<Tutor *> &temptutorList = student->GetTutorList();
    MyVector<Tutor*> tutorList;
    unordered_map<string,bool> exist;
    for(int i = 0; i < temptutorList.getSize(); i++ )
    {
        if(!exist[temptutorList[i]->GetID()])
        {
            exist[temptutorList[i]->GetID()] = 1;
            tutorList.push_back(temptutorList[i]);
        }
    }
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
    int height = 12 + tutorList.getSize();
    // Chọn gia sư từ danh sách gia sư của student
    Tutor *selectedTutor = nullptr;
    SetWordColor(14);
    rectangle(x, y, width, height);

    string title = "CHON GIA SU";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    int currentY = y + 3;
    SetWordColor(11);
    gotoXY(x + 3, currentY);
    cout << "Danh sach gia su cua ban:";
    currentY++;

    for (int i = 0; i < tutorList.getSize(); i++)
    {
        SetWordColor(7);
        gotoXY(x + 5, currentY);
        cout << i + 1 << ". " << tutorList[i]->GetName();
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
    gotoXY(x + 3, currentY + 2);
    SetWordColor(10);
    cout << "Nhap diem danh gia (1-5): ";
    double rating;
    SetWordColor(15);
    cin >> rating;
    if (rating < 1 || rating > 5)
    {
        SetWordColor(4);
        gotoXY(x + 3, currentY + 4);
        cout << "Diem danh gia khong hop le!";
        gotoXY(x + 3, currentY + 5);
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return;
    }
    student->Rating(selectedTutor, rating);
    gotoXY(x + 3, currentY + 4);
    SetWordColor(14);
    cout << "Da danh gia gia su " << selectedTutor->GetName() << " voi diem so: ";
    SetWordColor(15);
    cout << rating << "/5";
    gotoXY(x + 3, currentY + 5);
    cout << "Nhan phim bat ky de quay lai...";
    _getch();
    SetWordColor(7);
}
string ReadInput(int x, int y, int maxLength, string CurText)
{
    string password = CurText;
    char ch;
    gotoXY(x, y);
    cout << password;
    while ((ch = _getch()) != 13)
    { // ENTER
        if (ch == 8)
        { // BACKSPACE
            if (!password.empty())
            {
                password.pop_back();
                gotoXY(x + password.length(), y);
                cout << " ";
                gotoXY(x + password.length(), y);
            }
        }
        else if (isprint(ch) && password.length() < maxLength)
        {
            password += ch;
            cout << ch;
        }
    }
    return password;
}
void SubjectSelectionMenu(Student *student, MyVector<Tutor *> tutors, string Index)
{
    bool valid = !Index.empty();
    for (int i = 0; i < Index.size(); i++)
    {
        if (!isdigit(Index[i]))
        {
            valid = 0;
        }
    }
    int index;
    if (valid)
        index = stoi(Index);
    if (index < 1 or index > tutors.getSize())
        valid = 0;
    if (!valid)
    {
        gotoXY(7, 22);
        cout << "                                                   ";
        gotoXY(6, 22);
        cout << "                                                   ";
        gotoXY(8, 22);
        cout << "                                                   ";
        gotoXY(7, 22);
        cout << "So thu tu khong hop le! An phim bat ki de quay lai!";
        _getch();
        return;
    }
    Tutor *tutor = tutors[index - 1];
    MyVector<SubjectRecord *>& sbjlist = tutor->getSubjectList();
    // FOR(i, 1, 9)
    // sbjlist.push_back(new Subject("Van" + to_string(i)));
    // FOR(i, 1, 9)
    // ttlist.push_back(new Tutor("0001", "Gia su " + to_string(i)));
    int currentPage = 0;
    int itemsPerPage = 10; // Số môn học mỗi trang
    int totalItems = sbjlist.getSize();
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
    while (1)
    {
        system("cls");
        int x = 10, y = 5;
        int width = 70; // Tăng chiều rộng để chứa 2 cột

        // Tính toán chiều cao các phần
        int header_height = 3;
        int body_height = 18;
        int footer_height = 3;

        int total_height = header_height + body_height + footer_height - 2;

        char Border = 205;
        char LeftTee = 204;
        char RightTee = 185;

        // Vẽ khung ngoài
        SetWordColor(14);
        rectangle(x, y, width, total_height);

        // Vẽ các đường chia ngang
        int header_divider_y = y + header_height - 1;
        gotoXY(x, header_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        int footer_divider_y = y + header_height + body_height - 2;
        gotoXY(x, footer_divider_y);
        cout << LeftTee;
        for (int i = 0; i < width - 2; i++)
            cout << Border;
        cout << RightTee;

        // Tiêu đề
        SetWordColor(6);
        string title = "DANH SACH MON HOC - Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Nội dung - 2 cột
        int contentX = x + 3;
        int contentY_start = y + header_height;

        // Tiêu đề các cột
        gotoXY(contentX + 2, contentY_start + 1);
        cout << "TEN MON HOC";
        gotoXY(contentX + 35, contentY_start + 1);
        cout << "HOC PHI";

        // Đường kẻ ngang dưới tiêu đề
        gotoXY(contentX, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";
        gotoXY(contentX + 35, contentY_start + 2);
        for (int i = 0; i < 30; i++)
            cout << "-";

        // Hiển thị danh sách môn học
        int startIndex = currentPage * itemsPerPage;
        int endIndex = min(startIndex + itemsPerPage, totalItems);
        int currentY = contentY_start + 4;

        for (int i = startIndex; i < endIndex; i++)
        {
            // Cột tên môn học
            gotoXY(contentX + 2, currentY);
            cout << (i + 1) << ". " << sbjlist[i]->GetSubject()->GetName();

            // Cột tên giảng viên
            gotoXY(contentX + 35, currentY);
            cout << sbjlist[i]->GetSubject()->GetCost();

            currentY++;
        }

        // Hướng dẫn điều hướng
        SetWordColor(6);
        string footer;
        if (totalPages > 1)
        {
            footer = "Quay lai        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "                            Quay lai";
        }
        gotoXY(x + 1, footer_divider_y + 1);
        cout << footer;
        SetWordColor(15);
        gotoXY(x + 1, footer_divider_y - 2);
        cout << "Nhap so thu tu mon hoc ban muon them: ";
        // Di chuyển con trỏ ra khỏi khung

        SetWordColor(7);
        string SubjectIndex;
        Coord d = MouseCoord();
        if (d.second == 22)
        {
            if (d.first < 47 or d.second > 54)
                continue;

            SubjectIndex = ReadInput(49, 22, 3, "");
            if (SubjectIndex.empty())
                continue;
            for (int i = 0; i < SubjectIndex.size(); i++)
            {
                if (!isdigit(SubjectIndex[i]))
                {
                    valid = 0;
                }
            }
            int subjectindex;
            if (valid)
                subjectindex = stoi(SubjectIndex);
            if (subjectindex < 1 or subjectindex > tutor->getSubjectList().getSize())
                valid = 0;
            gotoXY(11, 22);
            cout << "                                                   ";
            gotoXY(11, 22);
            if (!valid)
            {
                cout << "So thu tu khong hop le! An phim bat ki de quay lai!";
                _getch();
                return;
            }
            Tutor *selectedTutor = tutor;
            SubjectRecord *selectedSubject = tutor->getSubjectList()[subjectindex - 1];
            bool ExistTutor = false, ExistSubject = false;
            MyVector<Tutor *> &studentTutors = student->GetTutorList();
            MyVector<Subject *> &studentSubject = student->GetSubjectList();
            for (int i = 0; i < studentTutors.getSize(); ++i)
            {
                if (studentTutors[i]->GetID() == selectedTutor->GetID())
                {
                    ExistTutor = true;
                    break;
                }
            }
            if (ExistTutor)
            {
                for (int i = 0; i < studentSubject.getSize(); i++)
                {
                    if (selectedSubject->GetID() == studentSubject[i]->GetID())
                    {
                        ExistSubject = true;
                        break;
                    }
                }
            }
            if (ExistSubject)
            {
                gotoXY(11, 22);
                cout << "Da co mon " << selectedSubject->GetSubject()->GetName() << " cua giao vien "
                     << selectedTutor->GetName() << "!" << endl;
                _getch();
                break;
            }
            if (student->GetBalance() < selectedSubject->GetSubject()->GetCost())
            {
                gotoXY(11, 22);
                cout << "So du cua ban khong du!";
                _getch();
                break;
            }
            student->Withdraw(selectedSubject->GetSubject()->GetCost());
            selectedTutor->Deposit(selectedSubject->GetSubject()->GetCost());
            selectedTutor->addStudentToSubject(student, selectedSubject->GetSubject()->GetID());
            FileHandler::SaveAllData();
            gotoXY(11, 22);
            cout << "Them gia su thanh cong, da tru hoc phi vao tai khoan!";
            _getch();
            break;
        }
        if (totalPages > 1)
        {
            if (d.SE != 25)
                continue;
            if (d.FI >= 27 && d.SE <= 40)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 47 && d.FI <= 58)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
            }
            if (d.FI >= 11 && d.FI <= 18)
                break;
        }
        else
        {
            if (d.SE != 25)
                continue;
            if (d.FI <= 48 && d.FI >= 40)
            {
                break;
            }
        }
    }
}
void DisplayTutors(MyVector<Tutor *> tutors, Student *student)
{
    int currentPage = 0;
    int tutorsPerPage = 10;
    int totalPages = (tutors.getSize() + tutorsPerPage - 1) / tutorsPerPage;
    bool printed = 0;
    while (true)
    {
        int x = 5, y = 3;
        int width = 95;
        int total_height = 22;

        int startIndex = currentPage * tutorsPerPage;
        int endIndex = min(startIndex + tutorsPerPage, tutors.getSize());
        int currentY = y + 3;
        if (!printed)
        {
            system("cls");
            // Vẽ khung chính
            SetWordColor(14); // Màu vàng
            rectangle(x, 22, width, 3);
            rectangle(x, y, width, total_height);

            // Tiêu đề
            SetWordColor(14);
            string title = "DANH SACH TAT CA GIA SU";
            gotoXY(x + (width - title.length()) / 2, y + 1);
            cout << title;

            // Hiển thị thông tin trang
            SetWordColor(11);
            string pageInfo = "Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
            gotoXY(x + width - pageInfo.length() - 3, y + 1);
            cout << pageInfo;

            // Kiểm tra nếu không có gia sư
            if (tutors.getSize() == 0)
            {
                SetWordColor(12);
                gotoXY(x + (width - 35) / 2, y + 5);
                cout << "Hien tai chua co gia su nao trong he thong!";

                SetWordColor(8);
                gotoXY(x + (width - 30) / 2, y + 7);
                cout << "Nhan phim bat ky de quay lai...";

                SetWordColor(7);
                _getch();
                return;
            }

            // Tiêu đề cột (đã bỏ cột học phí)
            SetWordColor(11);
            gotoXY(x + 2, currentY + 1);
            cout << "STT";
            gotoXY(x + 7, currentY + 1);
            cout << "TEN GIA SU";
            gotoXY(x + 30, currentY + 1);
            cout << "DIA CHI";
            gotoXY(x + 55, currentY + 1);
            cout << "DANH GIA";
            gotoXY(x + 75, currentY + 1);
            cout << "MON HOC";

            // Đường kẻ ngang dưới tiêu đề
            gotoXY(x + 2, currentY + 2);
            for (int i = 0; i < width - 4; i++)
                cout << "=";
            currentY += 3;

            // Hiển thị danh sách gia sư
            for (int i = startIndex; i < endIndex; i++)
            {
                Tutor *tutor = tutors[i];
                if (tutor == NULL)
                    continue;

                // Màu xen kẽ cho các dòng
                if ((i - startIndex) % 2 == 0)
                {
                    SetWordColor(7); // Màu trắng
                }
                else
                {
                    SetWordColor(8); // Màu xám
                }

                // Số thứ tự
                gotoXY(x + 3, currentY);
                cout << i + 1;

                // Tên gia sư
                gotoXY(x + 7, currentY);
                cout << tutor->GetName();

                // Địa chỉ (cắt ngắn nếu quá dài)
                string location = tutor->GetLocation();
                if (location.length() > 20)
                {
                    location = location.substr(0, 17) + "...";
                }
                gotoXY(x + 30, currentY);
                cout << location;

                // Đánh giá với màu sắc
                float rating = tutor->GetRating();
                int numRatings = tutor->GetNumOfRatings();

                SetWordColor(rating >= 4.0 ? 10 : (rating >= 3.0 ? 14 : 12));
                gotoXY(x + 55, currentY);
                cout << fixed << setprecision(1) << rating << "/5";

                SetWordColor(8);
                gotoXY(x + 63, currentY);
                cout << "(" << numRatings << " luot)";

                // Các môn học
                MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
                SetWordColor(7);
                gotoXY(x + 75, currentY);
                if (subjectList.getSize() > 0)
                {
                    string subjects = "";
                    for (int j = 0; j < min(3, subjectList.getSize()); j++)
                    {
                        if (j > 0)
                            subjects += ", ";
                        subjects += subjectList[j]->GetSubject()->GetName();
                    }
                    if (subjectList.getSize() > 3)
                    {
                        subjects += " ...";
                    }
                    if(subjects.size() > 18)
                    subjects = subjects.substr(0,15) + "...";
                    cout << subjects;
                }
                else
                {
                    cout << "--------";
                }

                currentY++;
            }
            gotoXY(7, 22);
            cout << "Nhap so thu tu gia su ban muon them: ";
            if (totalPages > 1)
            {
                gotoXY(6, 24);
                cout << "Quay lai";
                gotoXY(32, 24);
                cout << "<-Trang truoc";
                gotoXY(56, 24);
                cout << "Trang sau->";
            }
            else
            {
                gotoXY(45, 24);
                cout << "Quay lai";
            }
            printed = 1;
        }
        SetWordColor(7);
        Coord d = MouseCoord();
        if (d.SE == 22)
        {
            string Index = ReadInput(44, 22, 3, "");
            SubjectSelectionMenu(student, tutors, Index);
            system("cls");
            printed = 0;
        }
        if (totalPages > 1)
        {
            if (d.SE != 24)
                continue;
            if (d.FI >= 32 && d.SE <= 44)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
                else
                    printed = 0;
            }
            if (d.FI >= 56 && d.FI <= 66)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
                else
                    printed = 0;
            }
            if (d.FI >= 6 && d.FI <= 13)
                break;
        }
        else
        {
            if (d.SE != 24)
                continue;
            if (d.FI >= 45 && d.FI <= 52)
            {
                return;
            }
        }
    }
}

void FilterResult(Student *student, string TutorName, string SubjectName, string Address, string LowerCost, string UpperCost)
{
    Program prg;
    MyVector<Tutor *> &FirstResult = prg.getTutorList();
    // Name filter
    MyVector<Tutor *> Result = FirstResult;
    if (!TutorName.empty())
    {
        MyVector<Tutor *> TempVector;
        for (int i = 0; i < Result.getSize(); ++i)
        {
            if (Result[i]->GetName().find(TutorName) != string::npos)
            {
                TempVector.push_back(Result[i]);
            }
        }
        Result = TempVector;
    }
    // subject filter
    if (!SubjectName.empty())
    {
        MyVector<Tutor *> TempVector;
        for (int i = 0; i < Result.getSize(); ++i)
        {
            Tutor *tutor = Result[i];
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetSubject()->GetName().find(SubjectName) != string::npos && subjectList[j]->GetSubject()->GetCost() >= stoi(LowerCost) && subjectList[j]->GetSubject()->GetCost() <= stoi(UpperCost) )
                {
                    TempVector.push_back(tutor);
                    break;
                }
            }
        }
        Result = TempVector;
    }
    // location filter
    if (!Address.empty())
    {
        MyVector<Tutor *> TempVector;
        for (int i = 0; i < Result.getSize(); ++i)
        {
            if (Result[i]->GetLocation().find(Address) != string::npos)
            {
                TempVector.push_back(Result[i]);
            }
        }
        Result = TempVector;
    }
    // LowerCost Filter
    if (!LowerCost.empty())
    {
        MyVector<Tutor *> TempVector;
        for (int i = 0; i < Result.getSize(); ++i)
        {
            Tutor *tutor = Result[i];
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetSubject()->GetCost() > stoi(LowerCost))
                {
                    TempVector.push_back(tutor);
                    break;
                }
            }
        }
        Result = TempVector;
    }
    if (!UpperCost.empty())
    {
        MyVector<Tutor *> TempVector;
        for (int i = 0; i < Result.getSize(); ++i)
        {
            Tutor *tutor = Result[i];
            MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();

            for (int j = 0; j < subjectList.getSize(); ++j)
            {
                if (subjectList[j]->GetSubject()->GetCost() < stoi(UpperCost))
                {
                    TempVector.push_back(tutor);
                    break;
                }
            }
        }
        Result = TempVector;
    }
    // while (Result.getSize() < 15)
    // {
    //     Result.push_back(Result[0]);
    // }
    DisplayTutors(Result, student);
}
void SearchMenu(Student *student)
{
    system("cls");
    int x = 10, y = 5;
    int width = 80;      // Chiều rộng của khung
    int bodyHeight = 16; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    // Ký tự phân cách (viền đôi)
    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung (Màu Vàng Sáng)
    SetWordColor(14); // 14 = Vàng Sáng
    rectangle(x, y, width, totalHeight);

    // Vẽ đường phân cách
    // Dải phân cách Header
    gotoXY(x, y + 2);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, y + 2);
    cout << MR;

    // Dải phân cách Footer
    int footerSeparatorY = y + 2 + bodyHeight + 1;
    gotoXY(x, footerSeparatorY);
    cout << ML;
    for (int i = 0; i < width - 2; i++)
        cout << HL;
    gotoXY(x + width - 1, footerSeparatorY);
    cout << MR;

    // In nội dung (Màu Vàng Cam)
    SetWordColor(6);

    // In tiêu đề (căn giữa)
    string title = "TIM KIEM GIA SU";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    int TopMargin = 7;
    SetWordColor(10);
    rectangle(30, TopMargin + 2, 50, 3);
    rectangle(30, TopMargin + 5, 50, 3);
    rectangle(30, TopMargin + 8, 50, 3);
    rectangle(30, TopMargin + 11, 13, 3);
    rectangle(30 + 18, TopMargin + 11, 13, 3);
    SetWordColor(11);
    gotoXY(15, TopMargin + 3);
    cout << "Ten gia su: ";
    gotoXY(15, TopMargin + 6);
    cout << "Ten moc hoc: ";
    gotoXY(15, TopMargin + 9);
    cout << "Dia chi: ";
    gotoXY(15, TopMargin + 12);
    cout << "Hoc phi: ";
    gotoXY(30 + 15, TopMargin + 12);
    cout << "-";

    rectangle(x + (width - 1) / 2 - 5, TopMargin + 14, 10, 3);
    SetConsoleOutputCP(65001);
    gotoXY(x + (width - 1) / 2 - 1, TopMargin + 15);
    cout << "🔍";
    gotoXY(x + (width - 1) / 2 - 4, TopMargin + 18);
    SetWordColor(6);
    cout << "Quay lai";
    gotoXY(0, 0);
    SetConsoleOutputCP(437);
    string TutorName, SubjectName, Address, UpperCost, LowerCost;
    SetWordColor(15);
    // while(1)
    // {
    //     Coord d = MouseCoord();
    //     cout << d.first << "," << d.second << "  "; //19 32 41 49 58
    // }
    while (1)
    {
        Coord d = MouseCoord();
        //  cout << d.FI << "," << d.SE << " ";
        if (d.FI >= 31 && d.SE <= 79)
        {
            if (d.SE == 10)
            {
                // gotoXY(32, d.SE);
                TutorName = ReadInput(32, d.SE, 45, TutorName);
                //  TutorName = ReadLine(32, d.SE, MaxLen);
            }
            if (d.SE == 13)
            {
                //  gotoXY(32, d.SE);
                SubjectName = ReadInput(32, d.SE, 45, SubjectName);
                // SubjectName = ReadLine(32, d.SE, MaxLen);
            }
            if (d.SE == 16)
            {
                //  gotoXY(32, d.SE);
                Address = ReadInput(32, d.SE, 45, Address);
            }
        }
        if (d.SE == 19)
        {
            if (d.FI >= 31 && d.FI <= 41)
            {
                LowerCost = ReadInput(32, d.SE, 9, LowerCost);
            }
            if (d.FI >= 48 && d.FI <= 58)
            {
                UpperCost = ReadInput(50, d.SE, 9, UpperCost);
            }
        }
        if (d.FI >= 44 && d.FI <= 53 && d.SE >= 21 && d.SE <= 23)
        {
            FilterResult(student, TutorName, SubjectName, Address, LowerCost, UpperCost);
            break;
        }
        if (d.FI >= 44 && d.FI <= 52 && d.SE == 25)
        {
            break;
        }
    }
    SetWordColor(7);
}

Student *LoginStudent()
{
    gotoXY(0, 0);
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
    cout << "DANG NHAP - HOC VIEN";

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
    getline(cin >> ws, id);
    // SetWordColor(6);
    // gotoXY(x + 4, y + 8);
    // cout << "Mat Khau:";
    SetWordColor(15);
    password = getPassword(inputX, y + 8, inputWidth);

    // 6. Xu lý sau khi dang nhap
    SetWordColor(6);           // Màu xanh duong sáng
    gotoXY(x, y + height + 1); // Di chuyen xuong duoi khung
    Student *student = prg.LoginStudent(id, password);
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    return student;
}
void HandleStudentMenu(Student *student)
{
    ShowStudentMenu(student); // 1. Ve menu sinh vien lan dau tien.

    while (true)
    {                               // 2. Bat dau vong lap su kien cho menu sinh vien.
        Coord click = MouseCoord(); // 3. Cho mot CLICK MOI tu nguoi dung.
        if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
        {
            SearchMenu(student);
            ShowStudentMenu(student);
        }
        else if (click.FI >= 21 && click.FI <= 54 && click.SE >= 9 && click.SE <= 11)
        {
            Screen_Student_one(student);
            // man hinh hien thi thong tin ca nhan
            ShowStudentMenu(student);
            // quay ve menu
        }
        else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98)
        {
            CreateSchedule(student);
            // Screen_Student_2(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Student_3(student);
            ShowStudentMenu(student);
        }

        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 65 && click.FI <= 98)
        {
            ShowNapTienScreen_4(student);
            ShowStudentMenu(student);
        }

        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 21 && click.FI <= 54)
        {
            ShowDanhSachMonHoc_5(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 65 && click.FI <= 98)
        {
            ShowLichHoc_6(student);
            ShowStudentMenu(student);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 65 && click.FI <= 98)
        {
            ScreenDanhGiaTuTor_8(student);
            ShowStudentMenu(student);
        }

        // nut dang xuat
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
        {
            break; // 4. Thoat khoi vong lap while(true) nay
        }
    }
    // 5. Sau khi 'break', ham nay ket thuc va quay tro lai ham main
}