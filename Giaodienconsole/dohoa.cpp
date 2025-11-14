// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <windows.h> // Can thiet cho SetConsoleOutputCP
// #include <string>
// using namespace std;

// void SetColor(int color) {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(hConsole, color);
// }

// void ShowFile(const string& fileName) {
//     ifstream file(fileName);
//     if (!file.is_open()) {
//         cerr << "Khong the mo file: " << fileName << endl;
//         return;
//     }

//     ostringstream oss;
//     string line;
//     while (getline(file, line)) {
//         oss << line << '\n';
//     }
//     file.close();

//     SetColor(14);
//     cout << oss.str();
//     SetColor(7);
// }

// int main() {
//     // --- BUOC QUAN TRONG ---
//     // Dat console sang che do UTF-8 de hien thi dung
//     // cac ky tu dac biet nhu █, ╚, ╗
//     SetConsoleOutputCP(65001); 

//     ShowFile("MenuTutor.txt");
//     cin.get();
//     return 0;
// }