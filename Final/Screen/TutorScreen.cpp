#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#include <iostream>
#include <limits>
#include "../Utility/Screen.h"
#include "../Utility/FileHandler.h"
#include "../Utility/Program.h"
#include "../Models/Tutor.h"
#include "../Models/Schedule.h"
#include "../Template/MyVector.h"
Tutor *LoginTutor()
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
    cout << "DANG NHAP - GIA SU";

    SetWordColor(8); // Màu xám
    gotoXY(x + 50, y + 9);
    cout << "(An mat khau bang '*')";
    gotoXY(x + 22, y + 12);
    cout << "(Nhan ENTER de xac nhan)";

    SetWordColor(8); // Màu xám cho ô
    int inputX = x + 22;
    int inputWidth = 35;

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
    Tutor *tutor = prg.LoginTutor(id, password);
    gotoXY(x, y + height + 2);
    SetWordColor(6);
    cout << "Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    return tutor;
}

void ShowTutorMenu(Tutor *tutor)
{
    system("cls");
    // Ký t? khung
    system("cls");
    char RightTop = 187, LeftTop = 201, LeftBottom = 200, RightBottom = 188;
    char Border = 205, UpBorder = 186, CrossLeft = 204, CrossRight = 185;

    int consoleWidth, consoleHeight;
    GetConsoleSize(consoleWidth, consoleHeight);

    // N?i dung hi?n th?
    string title = "MENU GIA SU";
    string welcome = "Chao mung gia su " + tutor->GetName() + " (ID: " + tutor->GetID() + ")";

    int boxWidth = 60;
    int startX = (consoleWidth - boxWidth) / 2;

    SetWordColor(14);

    // --- Dòng trên cùng ---
    cout << string(startX, ' ') << LeftTop;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightTop << "\n";

    // --- Dòng tiêu de ---
    cout << string(startX, ' ') << UpBorder;
    int padTitle = (boxWidth - 2 - title.size()) / 2;
    SetWordColor(6);
    cout << string(padTitle, ' ') << title;
    SetWordColor(14);
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
    SetWordColor(14);
    cout << string(boxWidth - 2 - padWelcome - welcome.size(), ' ') << UpBorder << "\n";

    // --- Dòng cuoi ---
    cout << string(startX, ' ') << LeftBottom;
    for (int i = 0; i < boxWidth - 2; i++)
        cout << Border;
    cout << RightBottom << "\n";

    // Các ô chuc nang
    int menuWidth = 34;    // tang chieu rong cac ô
    int spaceBetween = 10; // khoảng cách giữa 2 cột
    int totalMenuWidth = menuWidth * 2 + spaceBetween;

    int startMenuX = (consoleWidth - totalMenuWidth) / 2; // canh giua theo khung trên
    int leftX = startMenuX;
    int rightX = leftX + menuWidth + spaceBetween;

    int startY = 9; // dòng bat dau phía duoi khung
    int gapY = 3;   // khoang cach giua các hàng

    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "1. Hien thi thong tin ca nhan";
    gotoXY(rightX + 1, startY + 1);
    cout << "2. Cap nhat thong tin ca nhan";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "3. Kiem tra so du";
    gotoXY(rightX + 1, startY + 1);
    cout << "4. Hien thi danh sach mon hoc";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "5. Them mon hoc moi";
    gotoXY(rightX + 1, startY + 1);
    cout << "6. Cap nhat thong tin mon hoc";

    startY += gapY;
    SetWordColor(14);
    rectangle(leftX, startY, menuWidth, 3);
    rectangle(rightX, startY, menuWidth, 3);

    SetWordColor(6);
    gotoXY(leftX + 1, startY + 1);
    cout << "7. Xoa mon hoc";
    gotoXY(rightX + 1, startY + 1);
    cout << "8. Xem lich day";

    gotoXY(50, 23);
    SetWordColor(4);
    rectangle(50, 23, 20, 3);
    SetWordColor(6);
    gotoXY(55, 23 + 1);
    cout << "Dang Xuat" << endl;
    SetWordColor(7);
}

void ShowRutTienScreen(Tutor *tutor)
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
    string title = "RUT TIEN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In Nội dung (Body)
    int contentX = x + 3;
    int contentY_start = y + header_height; // y + 3 = 8

    gotoXY(contentX, contentY_start + 1);
    cout << "Nhap so tien can rut (VND):";

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
    if (soTien > tutor->GetBalance())
    {
        gotoXY(contentX, contentY_start + 17);
        SetWordColor(4);
        cout << "So tien trong tai khoan khong du de rut!";
    }
    else
    {
        SetWordColor(10);
        gotoXY(contentX, contentY_start + 17);
        cout << "Da rut thanh cong ";
        SetWordColor(15);
        cout << soTien;
        SetWordColor(10);
        cout << " bang " << final << "!";
        gotoXY(contentX, contentY_start + 18);
        cout << "So du moi: ";
        SetWordColor(15);
        cout << tutor->GetBalance() - soTien;
        tutor->Withdraw(soTien);
    }
    SetWordColor(10);
    gotoXY(contentX, contentY_start + 19);
    cout << "An phim bat ki de tiep tuc!";
    SetWordColor(15);
    _getch();
}

void Screen_Tutor_one(Tutor *tutor)
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
    SetWordColor(14); // Vàng Sáng
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
    SetWordColor(5);

    // In tiêu đề (căn giữa)
    string title = "THONG TIN CA NHAN";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    tutor->DisplayInfo();

    // In footer (căn giữa)
    SetWordColor(10);
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
void Screen_Tutor_2(Tutor *tutor)
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
    // cout << "Nhap ma so gia su moi:   ";
    // gotoXY(valueX, contentY);
    // string id;
    // getline(cin, id);
    // if (id != "N" && id != "n" && !id.empty())
    //     tutor->SetID(id);

    gotoXY(labelX, contentY + 1);
    cout << "Nhap Ho va ten moi     : ";
    gotoXY(valueX, contentY + 1);
    string name;
    getline(cin, name);
    if (name != "N" && name != "n" && !name.empty())
        tutor->SetUserName(name);

    gotoXY(labelX, contentY + 2);
    cout << "Dia chi moi            : ";
    gotoXY(valueX, contentY + 2);
    string location;
    getline(cin, location);
    if (location != "N" && location != "n")
        tutor->SetLocation(location);

    gotoXY(labelX, contentY + 3);
    cout << "Nhap mat khau moi      : ";
    gotoXY(valueX, contentY + 3);
    string password;
    getline(cin, password);
    if (password != "N" && password != "n" && !password.empty())
        tutor->SetPassword(password);
    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;
    FileHandler::SaveTutors();
    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_3(Tutor *tutor)
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
    string balance = to_string(tutor->GetBalance());
    int balanceX = x + (width - balance.length()) / 2; // Can giua
    gotoXY(balanceX, y + 5);
    cout << balance;

    // Footer
    SetWordColor(8); // Xam
    string footer = "(Nhan 'N' de Rut Tien, hoac phim bat ky de quay lai)";
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
            ShowRutTienScreen(tutor);
            break;
        }
        else
            break;
    }
}

void Screen_Tutor_4(Tutor *tutor)
{
    MyVector<SubjectRecord *> sbjlist = tutor->getSubjectList();
    MyVector<string> stdnames;
    MyVector<string> subnames;
    int currentPage = 0;
    int itemsPerPage = 10; // Số môn học mỗi trang
    int totalItems = sbjlist.getSize();

    // Build a list of subject names and a short list of student names per subject.
    for (int i = 0; i < sbjlist.getSize(); i++)
    {
        SubjectRecord *sr = sbjlist[i];
        subnames.push_back(sr->GetSubject() ? sr->GetSubject()->GetName() : string("-"));
        MyVector<Student *> sl = sr->GetStudentList();
        if (sl.getSize() == 0)
        {
            stdnames.push_back(string("-"));
        }
        else
        {
            string names = "";
            int limit = min(3, sl.getSize());
            for (int j = 0; j < limit; ++j)
            {
                if (j)
                    names += ", ";
                names += sl[j]->GetName();
            }
            if (sl.getSize() > limit)
                names += ", ...";
            stdnames.push_back(names);
        }
    }

    int totalPages = totalItems == 0 ? 1 : (totalItems + itemsPerPage - 1) / itemsPerPage;
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
        string title = "DANH SACH HOC VIEN - Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages);
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // Nếu không có môn học nào, hiện thông báo rõ ràng và chờ người dùng
        if (totalItems == 0)
        {
            SetWordColor(12);
            string msg = "Ban chua co mon hoc!";
            gotoXY(x + (width - msg.length()) / 2, y + header_height + 2);
            cout << msg;
            SetWordColor(7);
            _getch();
            return;
        }

        // Nội dung - 2 cột
        int contentX = x + 3;
        int contentY_start = y + header_height;

        // Tiêu đề các cột
        gotoXY(contentX + 2, contentY_start + 1);
        cout << "TEN MON HOC";
        gotoXY(contentX + 35, contentY_start + 1);
        cout << " HOC VIEN";

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
            cout << (i + 1) << ". " << subnames[i];

            // Cột tên học viên
            gotoXY(contentX + 35, currentY);
            cout << stdnames[i];
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
            footer = "Quay lai        <- Trang truoc      -> Trang sau";
        }
        else
        {
            footer = "                            Quay lai";
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
            if (d.FI >= 27 && d.FI <= 40)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 47 && d.FI <= 58)
            {
                currentPage++;
                int lastPage = totalPages - 1;
                if (currentPage > lastPage)
                    currentPage = lastPage;
            }
            if (d.FI >= 11 && d.FI <= 18)
                break;
        }
        else
        {
            if (d.SE != 25)
                continue;
            if (d.FI >= 40 && d.FI <= 48)
            {
                break;
            }
        }
    }
}

void Screen_Tutor_5(Tutor *tutor)
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
    string title = "THEM MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // In thông tin (căn lề)
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    int valueX = x + 32;  // Lề trái cho dữ liệu

    gotoXY(labelX, contentY);
    cout << "Nhap ten mon hoc moi    :";
    gotoXY(valueX, contentY);
    string mon;
    SetWordColor(15);
    getline(cin >> ws, mon);
    SetWordColor(14);
    gotoXY(labelX, contentY + 1);
    cout << "Nhap hoc phi cho mon hoc:";
    gotoXY(valueX, contentY + 1);
    int hp;
    SetWordColor(15);
    if (!IntInput(hp))
    {
        gotoXY(labelX, contentY + 2);
        SetWordColor(4);
        cout << "Hoc phi da nhap khong hop le!";
        gotoXY(labelX, contentY + 3);
        SetWordColor(6);
        cout << "An phim bat ki de quay lai!";
        _getch();
        return;
    }
    SetWordColor(14);
    gotoXY(labelX, contentY + 6);
    cout << "Da them mon hoc ";
    SetWordColor(15);
    cout << mon;
    gotoXY(labelX, contentY + 7);
    SetWordColor(14);
    cout << "va hoc phi la ";
    SetWordColor(15);
    cout << hp;

    Subject *newsubject = new Subject(mon, hp);
    SubjectRecord *sr = new SubjectRecord(newsubject, tutor);
    tutor->getSubjectList().push_back(sr);
    FileHandler::AppendSubjectRecordToFile(sr);
    // tutor->AddSubject(newsubject);

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_6(Tutor *tutor)
{
    system("cls");
    int x = 30, y = 5;
    int width = 60;      // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung
    SetWordColor(14);
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
    SetWordColor(10);

    // In tiêu đề (căn giữa)
    string title = "CAP NHAT MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // Hiển thị danh sách môn học
    MyVector<SubjectRecord *> &subjectList = tutor->getSubjectList();
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    SetWordColor(10);
    gotoXY(labelX, contentY);
    cout << "Danh sach mon hoc:";

    int index = 1;
    for (int i = 0; i < subjectList.getSize(); i++)
    {
        Subject *subject = subjectList[i]->GetSubject();
        gotoXY(labelX, contentY + index);
        SetWordColor(10);
        cout << index << ". " << left << setw(20) << subject->GetName() << " - Hoc phi: " << right << setw(10);
        SetWordColor(15);
        cout << subject->GetCost();
        index++;
    }
    SetWordColor(10);
    // Nhập số thứ tự môn học cần chỉnh sửa
    int selectedIndex;
    gotoXY(labelX, contentY + index + 1);
    cout << "Nhap so thu tu mon hoc can chinh sua: ";
    SetWordColor(15);
    cin >> selectedIndex;
    SetWordColor(10);

    if (selectedIndex < 1 || selectedIndex > subjectList.getSize())
    {
        gotoXY(labelX, contentY + index + 2);
        SetWordColor(4);
        cout << "So thu tu khong hop le!";
        gotoXY(labelX, contentY + index + 3);
        SetWordColor(4);
        cout << "An phim bat ky de quay lai menu!";
        _getch();
        return;
    }

    // Nhập học phí mới
    int newFee;
    gotoXY(labelX, contentY + index + 2);
    cout << "Nhap hoc phi moi: ";
    SetWordColor(15);
    cin >> newFee;
    SetWordColor(10);

    if (newFee <= 0)
    {
        gotoXY(labelX, contentY + index + 3);
        SetWordColor(4);
        cout << "Hoc phi khong hop le!";
        gotoXY(labelX, contentY + index + 4);
        SetWordColor(4);
        cout << "An phim bat ky de quay lai menu!";
        _getch();
        return;
    }

    // Cập nhật học phí
    subjectList[selectedIndex - 1]->GetSubject()->SetCost(newFee);
    FileHandler::SaveSubjectRecords();

    gotoXY(labelX, contentY + index + 3);
    SetWordColor(6);
    cout << "Hoc phi da duoc cap nhat thanh cong!";

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai menu...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}

void Screen_Tutor_7(Tutor *tutor)
{
    system("cls");
    int x = 30, y = 5;
    int width = 60;      // Chiều rộng của khung
    int bodyHeight = 10; // Chiều cao của phần thân
    // 3 dòng cho Header, 3 dòng cho Footer
    int totalHeight = 3 + bodyHeight + 3;

    char HL = 205; // ═
    char ML = 204; // ╠
    char MR = 185; // ╣

    // Vẽ khung
    SetWordColor(14);
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
    SetWordColor(10);

    // In tiêu đề (căn giữa)
    string title = "XOA MON HOC";
    gotoXY(x + (width - title.length()) / 2, y + 1);
    cout << title;

    // Hiển thị danh sách môn học
    int contentY = y + 4; // Bắt đầu in từ dòng y + 4
    int labelX = x + 3;   // Lề trái cho nhãn
    SetWordColor(10);
    gotoXY(labelX, contentY);
    cout << "Danh sach mon hoc:";

    int index = 1;
    for (int i = 0; i < tutor->getSubjectList().getSize(); i++)
    {
        Subject *subject = tutor->getSubjectList()[i]->GetSubject();
        gotoXY(labelX, contentY + index);
        cout << index << ". " << left << setw(20) << subject->GetName() << " - Hoc phi: " << right << setw(10) << subject->GetCost();
        index++;
    }

    // Nhập số thứ tự môn học cần chỉnh sửa
    int selectedIndex;
    gotoXY(labelX, contentY + index + 1);
    cout << "Nhap so thu tu mon hoc can xoa: ";
    bool valid = IntInput(selectedIndex);
    if (selectedIndex < 1 || selectedIndex > tutor->getSubjectList().getSize() || !valid)
    {
        gotoXY(labelX, contentY + index + 2);
        SetWordColor(4);
        cout << "So thu tu khong hop le!";
        gotoXY(labelX, contentY + index + 3);
        SetWordColor(4);
        cout << "An phim bat ky de quay lai menu!";
        _getch();
        return;
    }

    SubjectRecord *sr = tutor->getSubjectList()[selectedIndex - 1];
    MyVector<Student *> &studentList = sr->GetStudentList();
    for (int i = 0; i < studentList.getSize(); i++)
    {
        for (int j = 0; j < studentList[i]->GetSubjectList().getSize(); j++)
        {
            if (studentList[i]->GetSubjectList()[j]->GetID() == sr->GetID())
            {
                studentList[i]->GetSubjectList().removeAt(j);
                studentList[i]->GetTutorList().removeAt(j);
                break;
            }
        }
    }
    // 1) Xóa tất cả lịch liên quan tới SubjectRecord (trong danh sách global, tutor và students)
    Program prg;
    for (int i = 0; i < prg.getScheduleList().getSize();)
    {
        Schedule *sch = prg.getScheduleList()[i];
        if (sch && sch->GetSubjectRecord() && sch->GetSubjectRecord()->GetID() == sr->GetID())
        {
            // Xóa khỏi tutor của lịch
            Tutor *t = sch->GetTutor();
            if (t)
            {
                for (int k = 0; k < t->GetSchedules().getSize(); ++k)
                {
                    if (t->GetSchedules()[k] && t->GetSchedules()[k]->GetID() == sch->GetID())
                    {
                        t->GetSchedules().removeAt(k);
                        break;
                    }
                }
            }
            // Xóa khỏi student của lịch
            Student *s = sch->GetStudent();
            if (s)
            {
                for (int k = 0; k < s->GetSchedules().getSize(); ++k)
                {
                    if (s->GetSchedules()[k] && s->GetSchedules()[k]->GetID() == sch->GetID())
                    {
                        s->GetSchedules().removeAt(k);
                        break;
                    }
                }
            }
            // Xóa khỏi danh sách global và giải phóng bộ nhớ
            prg.getScheduleList().removeAt(i);
            delete sch;
            // không tăng i vì đã rút ngắn mảng
        }
        else
        {
            ++i;
        }
    }

    // 2) Xóa SubjectRecord khỏi danh sách SubjectRecord global
    for (int i = 0; i < prg.getSrList().getSize(); i++)
    {
        if (prg.getSrList()[i]->GetID() == sr->GetID())
        {
            prg.getSrList().removeAt(i);
            break;
        }
    }

    // 3) Xóa SubjectRecord khỏi danh sách của tutor
    tutor->getSubjectList().removeAt(selectedIndex - 1);

    // 4) Lưu các file thay đổi
    FileHandler::SaveSchedules();
    FileHandler::SaveSubjectRecords();

    // In footer (căn giữa)
    string footer = "Nhan phim bat ky de quay lai menu...";
    gotoXY(x + (width - footer.length()) / 2, footerSeparatorY + 1);
    cout << footer;

    // 5. Reset màu về mặc định
    SetWordColor(7);
    _getch();
}
// Hàm so sánh để sắp xếp theo thời gian tăng dần
void Screen_Tutor_8(Tutor *tutor)
{
    system("cls");
    if (!tutor)
    {
        return;
    }

    MyVector<Schedule *> schedules = tutor->GetSchedules();
    int total = schedules.getSize();
    int itemsPerPage = 8;
    int currentPage = 0;
    int totalPages = (total + itemsPerPage - 1) / itemsPerPage;

    while (true)
    {
        system("cls");
        int x = 6, y = 4;
        int width = 87; // Giảm width do đã xóa cột trạng thái
        int header_height = 3;
        int body_height = 18;
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
        string title = "LICH DAY - " + tutor->GetName();
        gotoXY(x + (width - title.length()) / 2, y + 1);
        cout << title;

        // columns
        SetWordColor(7);
        int contentX = x + 2;
        int contentY = y + 3;
        gotoXY(contentX, contentY);
        cout << "STT    NGAY         GIO         MON HOC                      HOC SINH";
        gotoXY(contentX, contentY + 1);
        for (int i = 0; i < width - 4; ++i)
            cout << "-";

        int start = currentPage * itemsPerPage;
        int end = min(start + itemsPerPage, total);
        int line = contentY + 3;
        schedules = SortSchedulesByTime(schedules);
        for (int i = start; i < end; ++i)
        {
            Schedule *s = schedules[i];
            string date = s ? s->GetDate() : string("-");
            string time = s ? (s->GetStartTime() + "-" + s->GetEndTime()) : string("-");
            string subj = "-";
            if (s && s->GetSubjectRecord() && s->GetSubjectRecord()->GetSubject())
                subj = s->GetSubjectRecord()->GetSubject()->GetName();
            string student = s && s->GetStudent() ? s->GetStudent()->GetName() : string("-");

            gotoXY(contentX, line);
            cout << setw(3) << left << (i + 1) << "   " << setw(10) << left << date << "   " << setw(9) << left
                 << time << "  " << setw(28) << left << subj << " " << setw(23) << left << student;
            line++;
        }

        // footer với điều hướng chuột
        SetWordColor(10);
        if (totalPages > 1)
        {
            gotoXY(x + 1, 27);
            cout << "Quay lai";
            gotoXY(x + 27, 27);
            cout << "<-Trang truoc";
            gotoXY(x + 51, 27);
            cout << "Trang sau->";
        }
        else
        {
            gotoXY(45, 27);
            cout << "Quay lai";
        }
        // Di chuyển con trỏ ra khỏi khung
        gotoXY(0, y + total_height + 2);

        SetWordColor(7);
        Coord d = MouseCoord();

        if (totalPages > 1)
        {
            if (d.SE != 27)
                continue;
            if (d.FI >= 33 && d.SE <= 45)
            {
                currentPage--;
                if (currentPage < 0)
                    currentPage = 0;
            }
            if (d.FI >= 57 && d.FI <= 67)
            {
                currentPage++;
                if (currentPage > totalPages)
                    currentPage = totalPages;
            }
            if (d.FI >= 7 && d.FI <= 14)
                break;
        }
        else
        {
            if (d.SE != 27)
                continue;
            if (d.FI <= 52 && d.FI >= 45)
            {
                break;
            }
        }
    }
}

void HandleTutorMenu(Tutor *tutor)
{
    ShowTutorMenu(tutor);
    while (true)
    {
        Coord click = MouseCoord();
        if (click.SE >= 9 && click.SE <= 11 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_one(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 9 && click.SE <= 11 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_2(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_3(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 12 && click.SE <= 14 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_4(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_5(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 15 && click.SE <= 17 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_6(tutor); // update subject
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 21 && click.FI <= 54)
        {
            Screen_Tutor_7(tutor); // xac nhan lich day
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 18 && click.SE <= 20 && click.FI >= 65 && click.FI <= 98)
        {
            Screen_Tutor_8(tutor);
            ShowTutorMenu(tutor);
        }
        else if (click.SE >= 23 && click.SE <= 25 && click.FI >= 50 && click.FI <= 69)
        {
            break;
        }
    }
}