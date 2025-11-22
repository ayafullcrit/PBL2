// // Hàm kiểm tra xem click có trong vùng không
// #define NOMINMAX
// #define WIN32_LEAN_AND_MEAN
// #include "Screen.h"
// #include <iostream>

// bool isClickInArea(int clickX, int clickY, int areaX, int areaY, int width, int height) {
//     return (clickX >= areaX && clickX <= areaX + width && 
//             clickY >= areaY && clickY <= areaY + height);
// }

// void ShowNapTienScreen_4()
// {
//     system("cls");
//     int x = 10, y = 5;
//     int width = 55; // Chiều rộng của khung

//     // Tính toán chiều cao các phần
//     int header_height = 3; // 1 dòng viền trên, 1 dòng chữ, 1 dòng viền dưới
//     int body_height = 19;  // 1 viền, 10 dòng nội dung/padding, 1 viền
//                            // int footer_height = 3; // 1 viền, 1 dòng chữ, 1 dòng viền dưới

//     // Tổng chiều cao (trừ đi 2 vì các viền chia bị trùng)
//     int total_height = header_height + body_height - 1; //+ footer_height - 2; // = 16

//     char Border = 205;
//     char LeftTee = 204;
//     char RightTee = 185;

//     // 2. Vẽ khung ngoài
//     SetWordColor(14);
//     rectangle(x, y, width, total_height);

//     // 3. Vẽ các đường chia ngang

//     int header_divider_y = y + header_height - 1;
//     gotoXY(x, header_divider_y);
//     cout << LeftTee;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTee;

//     // Đường chia Body / Footer
//     int footer_divider_y = y + header_height + body_height - 2;
//     gotoXY(x, footer_divider_y);
//     cout << LeftTee;
//     for (int i = 0; i < width - 2; i++)
//         cout << Border;
//     cout << RightTee;

//     // 4. In nội dung (Màu Vàng Cam)
//     SetWordColor(6); // 6 = Vàng Cam

//     // In Tiêu đề (Header)
//     string title = "NAP TIEN";
//     gotoXY(x + (width - title.length()) / 2, y + 1);
//     cout << title;

//     // In Nội dung (Body)
//     int contentX = x + 3;
//     int contentY_start = y + header_height; // y + 3 = 8

//     gotoXY(contentX, contentY_start + 1);
//     cout << "Nhap so tien can nap (VND):";

//     gotoXY(contentX, contentY_start + 3);
//     cout << "Chon phuong thuc thanh toan:";

//     SetWordColor(9);
//     rectangle(contentX + 2, contentY_start + 4, 37, 3);
//     SetWordColor(6);
//     gotoXY(contentX + 3, contentY_start + 5);
//     cout << "1. Chuyen khoan ngan hang         ";

//     SetWordColor(9);
//     rectangle(contentX + 2, contentY_start + 7, 37, 3);
//     SetWordColor(6);
//     gotoXY(contentX + 3, contentY_start + 8);
//     cout << "2. Vi dien tu (Momo, ZaloPay)     ";

//     SetWordColor(9);
//     rectangle(contentX + 2, contentY_start + 10, 37, 3);
//     SetWordColor(6);
//     gotoXY(contentX + 3, contentY_start + 11);
//     cout << "3. The tin dung (Visa/Mastercard) ";

//     SetWordColor(9);
//     rectangle(contentX + 2, contentY_start + 13, 37, 3);
//     SetWordColor(6);
//     gotoXY(contentX + 3, contentY_start + 14);
//     cout << "0. Huy bo giao dich               ";
// }
// int main()
// {
//     SetConsoleOutputCP(437);
//     ShowNapTienScreen_4();
//     Coord a = MouseCoord();
//     cout << a.first << ' ' << a.second << endl;
//     _getch();
//     /*
//     15 12 51 14
//     15 15 51 17
//     15 18 51 20
//     15 21 51 23
//     */
// }